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

  cpu.csr[1]=NO;//mcause
  // cpu.csr[2]=0x1800;//mstatus

  cpu.csr[3] = epc; // mepc
  // 让处理器进入关中断状态
  // mstatus.MIE->mstatus.MPIE;mstatus.MIE=0;
  printf("MEPC:%x",cpu.csr[0]);
  uint32_t mpie = (cpu.csr[2] & MIE) << 4;
  cpu.csr[2] = (cpu.csr[2] & (~MPIE)) | mpie | MIE;
  
  return cpu.csr[0];//mtvec
}

paddr_t isa_call_mret() {
  uint32_t mie = (cpu.csr[2] & MPIE) >> 4;
  cpu.csr[2] = (cpu.csr[2] & (~MIE))|mie|MPIE;
  return cpu.csr[3];
}

word_t isa_query_intr() {
  // printf("%x\n",(cpu.csr[2] & MIE));
  if (((cpu.csr[2] & MIE)) && cpu.INTR) {
    printf("INTR!!\n");
    cpu.INTR = false;
    return IRQ_TIMER;
  }
  return INTR_EMPTY;
}
