// the translate logic was defined in
// nemu/src/isa/riscv32/local-include/reg.h
// remember to update the display func in
// nemu/src/isa/riscv32/reg.c

#include <stdint.h>

#define DualCSR1(name1,name2,number,paddr_base) GenCSR(name1##number##name2,paddr_base)
#define DualCSR2(name1,name2,number,paddr_base) DualCSR1(name1,name2,number,paddr_base) DualCSR1(name1,name2,(number+1),(paddr_base+1))
#define DualCSR4(name1,name2,number,paddr_base) DualCSR2(name1,name2,number,paddr_base) DualCSR2(name1,name2,(number)+2,(paddr_base)+2)
#define DualCSR8(name1,name2,number,paddr_base) DualCSR4(name1,name2,number,paddr_base) DualCSR4(name1,name2,(number)+4,(paddr_base)+4)
#define DualCSR16(name1,name2,number,paddr_base) DualCSR8(name1,name2,number,paddr_base) DualCSR8(name1,name2,number+8,paddr_base+8)
#define DualCSR32(name1,name2,number,paddr_base) DualCSR16(name1,name2,number,paddr_base) DualCSR16(name1,name2,number+16,paddr_base+16)
#define DualCSR64(name1,name2,number,paddr_base) DualCSR32(name1,name2,number,paddr_base) DualCSR32(name1,name2,number+32,paddr_base+32)

#define CSR_LIST \
  GenCSR(MTVEC, 0x305) \
  GenCSR(MCAUSE, 0x342) \
  GenCSR(MSTATUS, 0x300) \
  GenCSR(MEPC, 0x341) \
  GenCSR(MVENDROID, 0xF11) \
  GenCSR(MARCHID, 0xF12) \
  GenCSR(SATP, 0x180) \
  GenCSR(MSCRATCH, 0x340) \
  GenCSR(DSCRATCH0, 0x140) \
  GenCSR(SSTATUS, 0x100) \
  GenCSR(MSTATUSH, 0x310) \
  GenCSR(MIE, 0x304) \
  GenCSR(MHARTID, 0xf14) \
  GenCSR(MISA, 0x301) \
  GenCSR(MIP, 0x344) \
  DualCSR1(PMPCFG,,0,0x3A0) \



// 生成静态常量定义
#define GenCSR(name, paddr) \
  static const uint32_t NEMU_CSR_V_##name = paddr; \
  static const uint32_t NEMU_CSR_##name = paddr;
CSR_LIST
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
