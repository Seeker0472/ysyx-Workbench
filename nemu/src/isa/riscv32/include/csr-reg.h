// the translate logic was defined in
// nemu/src/isa/riscv32/local-include/reg.h
// remember to update the display func in
// nemu/src/isa/riscv32/reg.c

#include <stdint.h>
#define CONCAT_IMPL(a, b) a##b
#define CONCAT(a, b) CONCAT_IMPL(a, b)

#define DualCSR0(name1,name2,paddr_base)  GenCSR(name1##0##name2,paddr_base)
#define DualCSR1(name1,name2,paddr_base)  DualCSR0(name1,name2,paddr_base)   GenCSR(name1##1##name2,(paddr_base+1))
#define DualCSR2(name1,name2,paddr_base)  DualCSR1(name1,name2,paddr_base)   GenCSR(name1##2##name2,(paddr_base+2))
#define DualCSR3(name1,name2,paddr_base)  DualCSR2(name1,name2,paddr_base)   GenCSR(name1##3##name2,(paddr_base+3))
#define DualCSR4(name1,name2,paddr_base)  DualCSR3(name1,name2,paddr_base)   GenCSR(name1##4##name2,(paddr_base+4))
#define DualCSR5(name1,name2,paddr_base)  DualCSR4(name1,name2,paddr_base)   GenCSR(name1##5##name2,(paddr_base+5))
#define DualCSR6(name1,name2,paddr_base)  DualCSR5(name1,name2,paddr_base)   GenCSR(name1##6##name2,(paddr_base+6))
#define DualCSR7(name1,name2,paddr_base)  DualCSR6(name1,name2,paddr_base)   GenCSR(name1##7##name2,(paddr_base+7))
#define DualCSR8(name1,name2,paddr_base)  DualCSR7(name1,name2,paddr_base)   GenCSR(name1##8##name2,(paddr_base+8))
#define DualCSR9(name1,name2,paddr_base)  DualCSR8(name1,name2,paddr_base)   GenCSR(name1##9##name2,(paddr_base+9))
#define DualCSR10(name1,name2,paddr_base) DualCSR9(name1,name2,paddr_base)  GenCSR(name1##10##name2,(paddr_base+10))
#define DualCSR11(name1,name2,paddr_base) DualCSR10(name1,name2,paddr_base) GenCSR(name1##11##name2,(paddr_base+11))
#define DualCSR12(name1,name2,paddr_base) DualCSR11(name1,name2,paddr_base) GenCSR(name1##12##name2,(paddr_base+12))
#define DualCSR13(name1,name2,paddr_base) DualCSR12(name1,name2,paddr_base) GenCSR(name1##13##name2,(paddr_base+13))
#define DualCSR14(name1,name2,paddr_base) DualCSR13(name1,name2,paddr_base) GenCSR(name1##14##name2,(paddr_base+14))
#define DualCSR15(name1,name2,paddr_base) DualCSR14(name1,name2,paddr_base) GenCSR(name1##15##name2,(paddr_base+15))

#define CSR_LIST \
  GenCSR(MVENDROID, 0xF11) \
  GenCSR(MARCHID, 0xF12) \
GenCSR(MHARTID, 0xf14) \
  GenCSR(MSTATUS, 0x300) \
  GenCSR(MISA, 0x301) \
  GenCSR(MEDELEG, 0x302) \
  GenCSR(MIDELEG, 0x303) \
  GenCSR(MTVEC, 0x305) \
  GenCSR(MCAUSE, 0x342) \
  GenCSR(MINSTRET, 0xB02) \
  GenCSR(MEPC, 0x341) \
  GenCSR(SATP, 0x180) \
  GenCSR(MSCRATCH, 0x340) \
  GenCSR(DSCRATCH0, 0x140) \
  GenCSR(SSTATUS, 0x100) \
  GenCSR(MSTATUSH, 0x310) \
  GenCSR(MIE, 0x304) \
  GenCSR(MIP, 0x344) \
  GenCSR(MCOUNTEREN, 0x306) \
  GenCSR(MCOUNTINHIBIT, 0x320) \
  GenCSR(MTVAL, 0x343) \
  GenCSR(SCOUNTEREN, 0x106) \
  GenCSR(MCYCLE, 0xB00) \
  GenCSR(MNSTATUS, 0x744) \
  GenCSR(MNEPC, 0x741) \
  GenCSR(SEPC, 0x141) \
  GenCSR(STVAL, 0x143) \
  GenCSR(STVEC, 0x105) \
  GenCSR(SCAUSE, 0x142) \
  GenCSR(SIE, 0x104) \
  DualCSR4(PMPCFG,,0x3A0) \
  DualCSR15(PMPADDR,,0x3B0) \

#define CSR_U_LIST \
  //GenCSR(SCOUNTOVF, 0xDA0)
  //GenCSR(TIME, 0xC01) 
  //GenCSR(MTOBI, 0xFB0)

// 生成静态常量定义
#define GenCSR(name, paddr) \
  static const uint32_t NEMU_CSR_V_##name = paddr; \
  static const uint32_t NEMU_CSR_##name = paddr;
CSR_LIST
CSR_U_LIST
#undef GenCSR





//Old Def

//#define csr_gen(name, vaddr)  static const uint32_t NEMU_CSR_V_##name=vaddr;
//#define csr_lo_gen(name, paddr)  static const uint32_t NEMU_CSR_##name=paddr;
//#define gen(name, vaddr, paddr)  csr_gen(name, vaddr); csr_lo_gen(name, paddr);
//
//gen(MTVEC, 0x305, 0x0);
//gen(MCAUSE, 0x342, 0x1);
//gen(MSTATUS, 0x300, 0x2);
//gen(MEPC, 0x341, 0x3);
//gen(MVENDROID, 0xF11, 0x4);
//gen(MARCHID, 0xF12, 0x5);
//gen(SATP, 0x180, 0x6);
//gen(MSCRATCH,0x340,0x7)
//gen(DSCRATCH0,0x140,0x8)
//gen(SSTATUS,0x100,0x9)
//gen(MSTATUSH,0x310,0x10)
//gen(MIE,0x304,0x11)
//gen(MHARTID,0xf14,0x12)
//gen(MISA,0x301,0x13)
//gen(MIP,0x344,0x14)
//gen(PMPCFG0,0x3A0,0x15)
//gen(PMPADDR0,0x3B0,0x16)
//gen(PMPADDR1,0x3B1,0x17)
//gen(PMPADDR2,0x3B2,0x18)
//
