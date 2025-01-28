/***************************************************************************************
 * Copyright (c) 2014-2022 Zihao Yu, Nanjing University
 *
 * NEMU is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan
 *PSL v2. You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY
 *KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 *NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 *
 * See the Mulan PSL v2 for more details.
 ***************************************************************************************/

#ifndef __RISCV_REG_H__
#define __RISCV_REG_H__

#include "isa.h"
#include "macro.h"
//#include "csr-reg.h"
#include <common.h>
#include <cpu/decode.h>
#include <stdint.h>

#pragma GCC diagnostic ignored "-Wunused-variable"

static inline int check_reg_idx(int idx) {
  IFDEF(CONFIG_RT_CHECK, assert(idx >= 0 && idx < MUXDEF(CONFIG_RVE, 16, 32)));
  return idx;
}

static inline int get_csr_reg(int idx) {
  IFDEF(CONFIG_RT_CHECK, assert(idx >= 0 && idx < 4096));
  switch (idx) {
#define GenCSR(name, paddr)                                                    \
  case NEMU_CSR_V_##name :                                                      \
    idx = NEMU_CSR_##name;                                                     \
    break;
    CSR_LIST
#undef GenCSR
  default:
    Log("WARRNING:Unsupported CSR NO:(0x%x)", idx);
  }
  return idx;
}

void difftest_csr_notexist();

#define gpr(idx) (cpu.gpr[check_reg_idx(idx)])

static uint32_t dummy = 0;

static inline bool check_defined(uint32_t idx, Decode *s) {
  bool okey = false;
#ifdef CLOSEBLOCK
  switch (idx) {
#define GenCSR(name, paddr)                                                    \
  case NEMU_CSR_V_##name :
    CSR_U_LIST
#undef GenCSR
      return false;
  }

#endif
  switch (idx) {
#define GenCSR(name, paddr)                                                    \
  case NEMU_CSR_V_##name:                                                      \
    okey = true;                                                               \
    break;
    CSR_LIST
#undef GenCSR
  default:
    s->dnpc = isa_raise_intr(2, s->pc);
    cpu.csr[NEMU_CSR_V_MTVAL]=s->isa.inst.val;
    IFDEF(CONFIG_DIFFTEST,difftest_csr_notexist());
    Log("WARRNING:Unsupported CSR NO:(0x%x)", idx);
  }
  return okey;
}

#define CSR_READONLY_MASK 0b110000000000
#define CSR_PRIV_MASK 0b001100000000

static inline bool check_write(uint32_t idx, Decode *s) {
  if ((idx & CSR_READONLY_MASK) == CSR_READONLY_MASK) {
    // TODO:raise exception!
    s->dnpc = isa_raise_intr(2, s->pc);
    return false;
  } else
    return check_defined(idx, s);
}

static inline void update_mstatus(){
#define MSTATUS_FS_MASK  0x00006000  // FS 位于 bit [14:13]
#define MSTATUS_FS_SHIFT 13
#define MSTATUS_VS_MASK  0x00000600  // VS 位于 bit [10:9]
#define MSTATUS_VS_SHIFT 9
#define MSTATUS_XS_MASK  0x00018000  // XS 位于 bit [16:15]
#define MSTATUS_XS_SHIFT 15
#define MSTATUS_SD_MASK  0x80000000  // SD 位于 bit 31 (RV32)
uint32_t mstatus = cpu.csr[NEMU_CSR_V_MSTATUS]; // 当前 mstatus 的值

// 提取字段值（结果为 0-3）
uint8_t fs = (mstatus & MSTATUS_FS_MASK) >> MSTATUS_FS_SHIFT;
uint8_t vs = (mstatus & MSTATUS_VS_MASK) >> MSTATUS_VS_SHIFT;
uint8_t xs = (mstatus & MSTATUS_XS_MASK) >> MSTATUS_XS_SHIFT;


// 判断是否处于 Dirty 状态
uint8_t is_fs_dirty = (fs == 3);
uint8_t is_vs_dirty = (vs == 3);
uint8_t is_xs_dirty = (xs == 3);

// 计算 SD 位（逻辑或操作）
uint8_t sd = is_fs_dirty || is_vs_dirty || is_xs_dirty;

// 清除旧的 SD 位
mstatus &= ~MSTATUS_SD_MASK;

// 设置新的 SD 位
mstatus |= (sd << 31);
  cpu.csr[NEMU_CSR_V_MSTATUS]=mstatus;
}

static inline bool check_read(uint32_t idx, Decode *s) {
  switch(idx){
    case NEMU_CSR_V_MSTATUS:
     update_mstatus();
    break;
  }
  return check_defined(idx, s);
}

/*
// 统一读写宏（返回可赋值的左值）
#define csr(idx,s) \
  (*({                                                                         \
    uint32_t *__ptr = check_write(idx,s) ? &(cpu.csr[(idx)]) : &dummy; \
    (check_read(idx,s) ? (void)0 : (dummy = 0));              \
    __ptr;                                                                     \
  }))
*/
#define csrw(idx, s)                                                           \
  (*({                                                                         \
    uint32_t *__ptr = check_write(idx, s) ? &(cpu.csr[(idx)]) : &dummy;        \
    __ptr;                                                                     \
  }))

#define csrr(idx, s)                                                           \
  (*({                                                                         \
    uint32_t *__ptr = check_read(idx, s) ? &(cpu.csr[(idx)]) : &dummy;         \
    (dummy = 0);                                                               \
    __ptr;                                                                     \
  }))
// #define csr(idx) (cpu.csr[get_csr_reg(idx)])

static inline const char *reg_name(int idx) {
  extern const char *regs[];
  return regs[check_reg_idx(idx)];
}

#endif
