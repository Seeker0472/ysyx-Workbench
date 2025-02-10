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
/*
#define MIE 0x8
#define SIE 0x2
#define SPIE 0x20
#define MPIE 0x80
#define SPP 0x100
*/

uint32_t stval_nextvalue = 0;

paddr_t riscv_intr_gotos (word_t NO,vaddr_t epc){
  Log("Handle this exception on S_Mod");
  cpu.csr[NEMU_CSR_SCAUSE]=NO;
  cpu.csr[NEMU_CSR_SEPC] = epc;
  // 关中断状态
  // sstatus.MIE->sstatus.MPIE;sstatus.MIE=0;
  /*
  uint32_t spie = (cpu.csr[NEMU_CSR_SSTATUS] & SIE) << 4;
  cpu.csr[NEMU_CSR_SSTATUS] = ((cpu.csr[NEMU_CSR_SSTATUS] & (~SPIE)) | spie)&(~SIE);
  cpu.csr[NEMU_CSR_MSTATUS] = ((cpu.csr[NEMU_CSR_MSTATUS] & (~SPIE)) | spie)&(~SIE);
  */
  bool sie = NEMU_sstatus->bits.SIE;
  NEMU_sstatus->bits.SPIE = sie;
  NEMU_mstatus->bits.SPIE = sie;
  NEMU_sstatus->bits.SIE = 0;
  NEMU_mstatus->bits.SIE = 0;
  // set previous privilege
  /*
  uint32_t spp = cpu.PRIV==NEMU_PRIV_HS?S:0;
  cpu.csr[NEMU_CSR_SSTATUS]|=spp;
  cpu.csr[NEMU_CSR_MSTATUS]|=spp;
  */
  NEMU_mstatus->bits.SPP=cpu.PRIV==NEMU_PRIV_HS?1:0;
  NEMU_sstatus->bits.SPP=cpu.PRIV==NEMU_PRIV_HS?1:0;
  cpu.csr[NEMU_CSR_STVAL] = stval_nextvalue;
  cpu.PRIV=NEMU_PRIV_HS;
  return cpu.csr[NEMU_CSR_STVEC];
}

paddr_t riscv_intr_gotom (word_t NO,vaddr_t epc){
  cpu.csr[NEMU_CSR_MCAUSE]=NO;
  cpu.csr[NEMU_CSR_MEPC] = epc; 
  // 关中断状态
  // mstatus.MIE->mstatus.MPIE;mstatus.MIE=0;

  /*
  uint32_t mpie = (cpu.csr[NEMU_CSR_MSTATUS] & MIE) << 4;
  cpu.csr[NEMU_CSR_MSTATUS] = ((cpu.csr[NEMU_CSR_MSTATUS] & (~MPIE)) | mpie)&(~MIE);
  // set previous privilege
  cpu.csr[NEMU_CSR_MSTATUS]|=cpu.PRIV<<11;
  */
  NEMU_mstatus->bits.MPIE = NEMU_mstatus->bits.MIE;
  NEMU_mstatus->bits.MIE = 0;
  printf("CPU>PRV=%x\n",cpu.PRIV);
  NEMU_mstatus->bits.MPP = cpu.PRIV;
  cpu.PRIV=NEMU_PRIV_M;
  return cpu.csr[NEMU_CSR_MTVEC];
}

word_t isa_raise_intr(word_t NO, vaddr_t epc) {
  //mepc寄存器 - 存放触发异常的PC
  //mstatus寄存器 - 存放处理器的状态
  //mcause寄存器 - 存放触发异常的原因
  IFDEF(CONFIG_ETRACE,Log("Trigged Exception!, No=%x Epc=%x",NO,epc););
  //medeleg bit of this interrupt was set!
  if(cpu.PRIV!=NEMU_PRIV_M&&(cpu.csr[NEMU_CSR_MEDELEG]>>(NO)&0x1)){
    return riscv_intr_gotos(NO,epc);
  }else{
    return riscv_intr_gotom(NO,epc);
  }
}

word_t riscv_do_ecall(word_t NO, vaddr_t epc) {
  if(cpu.PRIV==NEMU_PRIV_M||cpu.PRIV==NEMU_PRIV_HS) {
    return riscv_intr_gotom(NO, epc);
  }else{
    return riscv_intr_gotos(NO,epc);
  }
}


paddr_t isa_call_mret() {
//mstatus.MPIE->mstatus.MIE;mstatus.MPIE=1

/*
  uint32_t mie = (cpu.csr[NEMU_CSR_MSTATUS] & MPIE) >> 4;
  cpu.csr[NEMU_CSR_MSTATUS] = (cpu.csr[NEMU_CSR_MSTATUS] & (~MIE)) | mie | MPIE;
  cpu.PRIV = (cpu.csr[NEMU_CSR_MSTATUS] & 0x1800)>>11;
  cpu.csr[NEMU_CSR_MSTATUS] &= ~0x1800; 
*/
  NEMU_mstatus->bits.MIE = NEMU_mstatus->bits.MPIE;
  NEMU_mstatus->bits.MPP = 0;
  NEMU_mstatus->bits.MPIE=1;
  return cpu.csr[NEMU_CSR_MEPC];
}

paddr_t isa_call_sret() {
//sstatus.SPIE->mstatus.MIE;sstatus.SPIE=1
/*
  uint32_t sie = (cpu.csr[NEMU_CSR_SSTATUS] & SPIE) >> 4;
  cpu.csr[NEMU_CSR_SSTATUS] = (cpu.csr[NEMU_CSR_SSTATUS] & (~SIE)) | sie | SPIE;
  cpu.csr[NEMU_CSR_MSTATUS] = (cpu.csr[NEMU_CSR_MSTATUS] & (~SIE)) | sie | SPIE;
  cpu.PRIV = (cpu.csr[NEMU_CSR_SSTATUS] & 0x100)>>8;
  cpu.csr[NEMU_CSR_SSTATUS] &= ~0x100;
  cpu.csr[NEMU_CSR_MSTATUS] &= ~0x100;
*/
  NEMU_sstatus->bits.SIE = NEMU_sstatus->bits.SPIE;
  NEMU_sstatus->bits.SPIE = 1;
  NEMU_mstatus->bits.MIE = NEMU_mstatus->bits.MPIE;
  NEMU_mstatus->bits.MPIE = 1;
  NEMU_sstatus->bits.SPP = 0;
  NEMU_mstatus->bits.SPP = 0;
  cpu.PRIV = NEMU_sstatus->bits.SPP;
  return cpu.csr[NEMU_CSR_SEPC];
}

void difftest_raise(uint64_t NO);
word_t isa_query_intr() {
  if (NEMU_mstatus->bits.MIE && cpu.INTR) {
    //Log("INTR_TAKE");
  IFDEF(CONFIG_DIFFTEST,difftest_raise(IRQ_TIMER););
    cpu.INTR = false;
    return IRQ_TIMER;
  }
  return INTR_EMPTY;
}
