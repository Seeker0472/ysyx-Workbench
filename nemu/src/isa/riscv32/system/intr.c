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
#define SPP 0x100

// ecall 调用
word_t isa_raise_intr(word_t NO, vaddr_t epc) {
  //mepc寄存器 - 存放触发异常的PC
  //mstatus寄存器 - 存放处理器的状态
  //mcause寄存器 - 存放触发异常的原因
  IFDEF(CONFIG_ETRACE,Log("Trigged Exception!, No=%x Epc=%x",NO,epc););
  //medeleg bit of this interrupt was set!
  if(cpu.PRIV!=NEMU_PRIV_M&&(cpu.csr[NEMU_CSR_MEDELEG]>>(NO)&0x1)){
    Log("Handle this exception on S_Mod");
    cpu.csr[NEMU_CSR_SCAUSE]=NO;
    cpu.csr[NEMU_CSR_SEPC] = epc;
    // 关中断状态
    // sstatus.MIE->sstatus.MPIE;sstatus.MIE=0;
    uint32_t spie = (cpu.csr[NEMU_CSR_SSTATUS] & MIE) << 4;
    cpu.csr[NEMU_CSR_SSTATUS] = ((cpu.csr[NEMU_CSR_SSTATUS] & (~MPIE)) | spie)&(~MIE);
    // set previous privilege
    uint32_t spp = cpu.PRIV==NEMU_PRIV_HS?SPP:0;
    cpu.csr[NEMU_CSR_SSTATUS]|=(cpu.PRIV<<11)|spp;
    cpu.csr[NEMU_CSR_MSTATUS]|=(cpu.PRIV<<11)|spp;
    cpu.csr[NEMU_CSR_STVAL] = cpu.pc;
    return cpu.csr[NEMU_CSR_STVEC];
  }else{
    cpu.csr[NEMU_CSR_MCAUSE]=NO;
    cpu.csr[NEMU_CSR_MEPC] = epc; 
    // 关中断状态
    // mstatus.MIE->mstatus.MPIE;mstatus.MIE=0;
    uint32_t mpie = (cpu.csr[NEMU_CSR_MSTATUS] & MIE) << 4;
    cpu.csr[NEMU_CSR_MSTATUS] = ((cpu.csr[NEMU_CSR_MSTATUS] & (~MPIE)) | mpie)&(~MIE);
    // set previous privilege
    cpu.csr[NEMU_CSR_MSTATUS]|=cpu.PRIV<<11;
    return cpu.csr[NEMU_CSR_MTVEC];
  }

}

paddr_t isa_call_mret() {
//mstatus.MPIE->mstatus.MIE;mstatus.MPIE=1
  uint32_t mie = (cpu.csr[NEMU_CSR_MSTATUS] & MPIE) >> 4;
  cpu.csr[NEMU_CSR_MSTATUS] = (cpu.csr[NEMU_CSR_MSTATUS] & (~MIE)) | mie | MPIE;
  cpu.PRIV = (cpu.csr[NEMU_CSR_MSTATUS] & 0x1800)>>11;
  cpu.csr[NEMU_CSR_MSTATUS] &= ~0x1800;
  return cpu.csr[NEMU_CSR_MEPC];
}

void difftest_raise(uint64_t NO);
word_t isa_query_intr() {
  if (((cpu.csr[NEMU_CSR_MSTATUS] & MIE)) && cpu.INTR) {
    //Log("INTR_TAKE");
  difftest_raise(IRQ_TIMER);
    cpu.INTR = false;
    return IRQ_TIMER;
  }
  return INTR_EMPTY;
}
