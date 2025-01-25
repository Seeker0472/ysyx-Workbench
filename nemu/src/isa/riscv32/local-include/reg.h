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

#include <common.h>
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
  case NEMU_CSR_V_##name:                                                      \
    idx = NEMU_CSR_##name;                                                     \
    break;
    CSR_LIST
#undef GenCSR
  default:
    Log("WARRNING:Unsupported CSR NO:(0x%x)", idx);
  }
  return idx;
}

#define gpr(idx) (cpu.gpr[check_reg_idx(idx)])

static uint32_t dummy = 0;

static inline bool check_defined(uint32_t idx) {
  bool okey = false;
  switch (idx) {
#define GenCSR(name, paddr)                                                    \
  case paddr:                                                                  \
    okey = true;                                                               \
    break;
    CSR_LIST
#undef GenCSR
  default:
    Log("WARRNING:Unsupported CSR NO:(0x%x)", idx);
  }
  return okey;
}

#define CSR_READONLY_MASK 0b110000000000
#define CSR_PRIV_MASK 0b001100000000

static inline bool check_write(uint32_t idx) { 
  if((idx&CSR_READONLY_MASK)==CSR_READONLY_MASK){
    // TODO:raise exception!
    return false;
  }else
    return check_defined(idx); 
}
static inline bool check_read(uint32_t idx) { return check_defined(idx); }

// 统一读写宏（返回可赋值的左值）
#define csr(idx)                                                               \
  (*({                                                                         \
    uint32_t *__ptr = check_write(idx) ? &(cpu.csr[(idx)]) : &dummy;           \
    (check_read(idx) ? (void)0 : (dummy = 0)); /* 读失败时返回0 */             \
    __ptr;                                                                     \
  }))

// #define csr(idx) (cpu.csr[get_csr_reg(idx)])

static inline const char *reg_name(int idx) {
  extern const char *regs[];
  return regs[check_reg_idx(idx)];
}

#endif
