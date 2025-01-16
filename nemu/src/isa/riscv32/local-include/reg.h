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

#include <common.h>

static inline int check_reg_idx(int idx) {
  IFDEF(CONFIG_RT_CHECK, assert(idx >= 0 && idx < MUXDEF(CONFIG_RVE, 16, 32)));
  return idx;
}

static inline int get_csr_reg(int idx) {
  IFDEF(CONFIG_RT_CHECK, assert(idx >= 0 && idx < 4096));
  switch (idx) {
  case NEMU_CSR_V_MTVEC: // mtvec
    idx = NEMU_CSR_MTVEC;
    break;
  case NEMU_CSR_V_MCAUSE: // mcause
    idx = NEMU_CSR_MCAUSE;
    break;
  case NEMU_CSR_V_MSTATUS: // mstatus
    idx = NEMU_CSR_MSTATUS;
    break;
  case NEMU_CSR_V_MEPC: // mepc
    idx = NEMU_CSR_MEPC;
    break;
  case NEMU_CSR_V_MVENDROID: // mvendorid
    idx = NEMU_CSR_MVENDROID;
    break;
  case NEMU_CSR_V_MARCHID: // marchid
    idx = NEMU_CSR_MARCHID;
    break;
  case NEMU_CSR_V_SATP: // satp
    idx = NEMU_CSR_SATP;
    break;
  case NEMU_CSR_V_MSCRATCH:
    idx = NEMU_CSR_MSCRATCH;
    break;
  case NEMU_CSR_V_TDATA1:
    idx = NEMU_CSR_TDATA1;
    break;
  default:
    idx = -1;
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
