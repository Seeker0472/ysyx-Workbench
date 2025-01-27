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

#include "common.h"
#include <isa.h>
#include <stdint.h>
#include <stdio.h>
#define MIE 0x8
#define MPIE 0x80

// ecall 调用
word_t isa_raise_intr(word_t NO, vaddr_t epc) {
  /* TODO: Trigger an interrupt/exception with ``NO''.
   * Then return the address of the interrupt/exception vector.
   */
  //设置状态寄存器=> trap.S
  //mepc寄存器 - 存放触发异常的PC
  //mstatus寄存器 - 存放处理器的状态
  //mcause寄存器 - 存放触发异常的原因
// void set_nemu_state(int state, vaddr_t pc, int halt_ret);
//   set_nemu_state(NEMU_END, epc, NO);
  // assert(0);
  IFDEF(CONFIG_ETRACE,Log("Trigged Exception!, No=%x Epc=%x",NO,epc););

  cpu.csr[NEMU_CSR_MCAUSE]=NO;//mcause
  // cpu.csr[2]=0x1800;//mstatus

  cpu.csr[NEMU_CSR_MEPC] = epc; // mepc
  // 让处理器进入关中断状态
  // mstatus.MIE->mstatus.MPIE;mstatus.MIE=0;
  uint32_t mpie = (cpu.csr[NEMU_CSR_MSTATUS] & MIE) << 4;
  cpu.csr[NEMU_CSR_MSTATUS] = ((cpu.csr[NEMU_CSR_MSTATUS] & (~MPIE)) | mpie)&(~MIE);
  return cpu.csr[NEMU_CSR_MTVEC];//mtvec
}

paddr_t isa_call_mret() {
//mstatus.MPIE->mstatus.MIE;mstatus.MPIE=1
  uint32_t mie = (cpu.csr[NEMU_CSR_MSTATUS] & MPIE) >> 4;
  cpu.csr[NEMU_CSR_MSTATUS] = (cpu.csr[NEMU_CSR_MSTATUS] & (~MIE)) | mie | MPIE;
  cpu.PRIV = (cpu.csr[NEMU_CSR_MSTATUS] & 0x1800)>>11;
  cpu.csr[NEMU_CSR_MSTATUS] &= ~0x1800;
  return cpu.csr[NEMU_CSR_MEPC];
}

word_t isa_query_intr() {
  if (((cpu.csr[NEMU_CSR_MSTATUS] & MIE)) && cpu.INTR) {
    // printf("INTR!!\n");
    cpu.INTR = false;
    return IRQ_TIMER;
  }
  return INTR_EMPTY;
}
