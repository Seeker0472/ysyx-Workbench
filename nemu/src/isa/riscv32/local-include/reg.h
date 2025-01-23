/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#ifndef __RISCV_REG_H__
#define __RISCV_REG_H__

#include "debug.h"
#include <common.h>

static inline int check_reg_idx(int idx) {
  IFDEF(CONFIG_RT_CHECK, assert(idx >= 0 && idx < MUXDEF(CONFIG_RVE, 16, 32)));
  return idx;
}

static inline int get_csr_reg(int idx) {
  IFDEF(CONFIG_RT_CHECK, assert(idx >= 0 && idx < 4096));
  switch (idx) {
#define GenCSR(name, paddr) \
  case NEMU_CSR_V_##name:     \
    idx = NEMU_CSR_##name;    \
    break;
CSR_LIST
#undef X
  default:
    Log("WARRNING:Unsupported CSR NO:(0x%x)",idx);
}
  return idx;
}

#define gpr(idx) (cpu.gpr[check_reg_idx(idx)])

#define csr(idx) (cpu.csr[get_csr_reg(idx)])

static inline const char* reg_name(int idx) {
  extern const char* regs[];
  return regs[check_reg_idx(idx)];
}

#endif
