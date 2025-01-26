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
#define DualCSR16(name1,name2,paddr_base) DualCSR15(name1,name2,paddr_base) GenCSR(name1##16##name2,(paddr_base+16))
#define DualCSR17(name1,name2,paddr_base) DualCSR16(name1,name2,paddr_base) GenCSR(name1##17##name2,(paddr_base+17))
#define DualCSR18(name1,name2,paddr_base) DualCSR17(name1,name2,paddr_base) GenCSR(name1##18##name2,(paddr_base+18))
#define DualCSR19(name1,name2,paddr_base) DualCSR18(name1,name2,paddr_base) GenCSR(name1##19##name2,(paddr_base+19))
#define DualCSR20(name1,name2,paddr_base) DualCSR19(name1,name2,paddr_base) GenCSR(name1##20##name2,(paddr_base+20))
#define DualCSR21(name1,name2,paddr_base) DualCSR20(name1,name2,paddr_base) GenCSR(name1##21##name2,(paddr_base+21))
#define DualCSR22(name1,name2,paddr_base) DualCSR21(name1,name2,paddr_base) GenCSR(name1##22##name2,(paddr_base+22))
#define DualCSR23(name1,name2,paddr_base) DualCSR22(name1,name2,paddr_base) GenCSR(name1##23##name2,(paddr_base+23))
#define DualCSR24(name1,name2,paddr_base) DualCSR23(name1,name2,paddr_base) GenCSR(name1##24##name2,(paddr_base+24))
#define DualCSR25(name1,name2,paddr_base) DualCSR24(name1,name2,paddr_base) GenCSR(name1##25##name2,(paddr_base+25))
#define DualCSR26(name1,name2,paddr_base) DualCSR25(name1,name2,paddr_base) GenCSR(name1##26##name2,(paddr_base+26))
#define DualCSR27(name1,name2,paddr_base) DualCSR26(name1,name2,paddr_base) GenCSR(name1##27##name2,(paddr_base+27))
#define DualCSR28(name1,name2,paddr_base) DualCSR27(name1,name2,paddr_base) GenCSR(name1##28##name2,(paddr_base+28))
#define DualCSR29(name1,name2,paddr_base) DualCSR28(name1,name2,paddr_base) GenCSR(name1##29##name2,(paddr_base+29))
#define DualCSR30(name1,name2,paddr_base) DualCSR29(name1,name2,paddr_base) GenCSR(name1##30##name2,(paddr_base+30))
#define DualCSR31(name1,name2,paddr_base) DualCSR30(name1,name2,paddr_base) GenCSR(name1##31##name2,(paddr_base+31))
#define DualCSR32(name1,name2,paddr_base) DualCSR31(name1,name2,paddr_base) GenCSR(name1##32##name2,(paddr_base+32))
#define DualCSR33(name1,name2,paddr_base) DualCSR32(name1,name2,paddr_base) GenCSR(name1##33##name2,(paddr_base+33))
#define DualCSR34(name1,name2,paddr_base) DualCSR33(name1,name2,paddr_base) GenCSR(name1##34##name2,(paddr_base+34))
#define DualCSR35(name1,name2,paddr_base) DualCSR34(name1,name2,paddr_base) GenCSR(name1##35##name2,(paddr_base+35))
#define DualCSR36(name1,name2,paddr_base) DualCSR35(name1,name2,paddr_base) GenCSR(name1##36##name2,(paddr_base+36))
#define DualCSR37(name1,name2,paddr_base) DualCSR36(name1,name2,paddr_base) GenCSR(name1##37##name2,(paddr_base+37))
#define DualCSR38(name1,name2,paddr_base) DualCSR37(name1,name2,paddr_base) GenCSR(name1##38##name2,(paddr_base+38))
#define DualCSR39(name1,name2,paddr_base) DualCSR38(name1,name2,paddr_base) GenCSR(name1##39##name2,(paddr_base+39))
#define DualCSR40(name1,name2,paddr_base) DualCSR39(name1,name2,paddr_base) GenCSR(name1##40##name2,(paddr_base+40))
#define DualCSR41(name1,name2,paddr_base) DualCSR40(name1,name2,paddr_base) GenCSR(name1##41##name2,(paddr_base+41))
#define DualCSR42(name1,name2,paddr_base) DualCSR41(name1,name2,paddr_base) GenCSR(name1##42##name2,(paddr_base+42))
#define DualCSR43(name1,name2,paddr_base) DualCSR42(name1,name2,paddr_base) GenCSR(name1##43##name2,(paddr_base+43))
#define DualCSR44(name1,name2,paddr_base) DualCSR43(name1,name2,paddr_base) GenCSR(name1##44##name2,(paddr_base+44))
#define DualCSR45(name1,name2,paddr_base) DualCSR44(name1,name2,paddr_base) GenCSR(name1##45##name2,(paddr_base+45))
#define DualCSR46(name1,name2,paddr_base) DualCSR45(name1,name2,paddr_base) GenCSR(name1##46##name2,(paddr_base+46))
#define DualCSR47(name1,name2,paddr_base) DualCSR46(name1,name2,paddr_base) GenCSR(name1##47##name2,(paddr_base+47))
#define DualCSR48(name1,name2,paddr_base) DualCSR47(name1,name2,paddr_base) GenCSR(name1##48##name2,(paddr_base+48))
#define DualCSR49(name1,name2,paddr_base) DualCSR48(name1,name2,paddr_base) GenCSR(name1##49##name2,(paddr_base+49))
#define DualCSR50(name1,name2,paddr_base) DualCSR49(name1,name2,paddr_base) GenCSR(name1##50##name2,(paddr_base+50))
#define DualCSR51(name1,name2,paddr_base) DualCSR50(name1,name2,paddr_base) GenCSR(name1##51##name2,(paddr_base+51))
#define DualCSR52(name1,name2,paddr_base) DualCSR51(name1,name2,paddr_base) GenCSR(name1##52##name2,(paddr_base+52))
#define DualCSR53(name1,name2,paddr_base) DualCSR52(name1,name2,paddr_base) GenCSR(name1##53##name2,(paddr_base+53))
#define DualCSR54(name1,name2,paddr_base) DualCSR53(name1,name2,paddr_base) GenCSR(name1##54##name2,(paddr_base+54))
#define DualCSR55(name1,name2,paddr_base) DualCSR54(name1,name2,paddr_base) GenCSR(name1##55##name2,(paddr_base+55))
#define DualCSR56(name1,name2,paddr_base) DualCSR55(name1,name2,paddr_base) GenCSR(name1##56##name2,(paddr_base+56))
#define DualCSR57(name1,name2,paddr_base) DualCSR56(name1,name2,paddr_base) GenCSR(name1##57##name2,(paddr_base+57))
#define DualCSR58(name1,name2,paddr_base) DualCSR57(name1,name2,paddr_base) GenCSR(name1##58##name2,(paddr_base+58))
#define DualCSR59(name1,name2,paddr_base) DualCSR58(name1,name2,paddr_base) GenCSR(name1##59##name2,(paddr_base+59))
#define DualCSR60(name1,name2,paddr_base) DualCSR59(name1,name2,paddr_base) GenCSR(name1##60##name2,(paddr_base+60))
#define DualCSR61(name1,name2,paddr_base) DualCSR60(name1,name2,paddr_base) GenCSR(name1##61##name2,(paddr_base+61))
#define DualCSR62(name1,name2,paddr_base) DualCSR61(name1,name2,paddr_base) GenCSR(name1##62##name2,(paddr_base+62))
#define DualCSR63(name1,name2,paddr_base) DualCSR62(name1,name2,paddr_base) GenCSR(name1##63##name2,(paddr_base+63))
#define DualCSR64(name1,name2,paddr_base) DualCSR63(name1,name2,paddr_base) GenCSR(name1##64##name2,(paddr_base+64))

#define CSR_LIST \
  GenCSR(MVENDROID, 0xF11) \
  GenCSR(MARCHID, 0xF12) \
  GenCSR(MHARTID, 0xf14) \
  GenCSR(MSTATUS, 0x300) \
  GenCSR(MISA, 0x301) \
  GenCSR(MIDELEG, 0x303) \
  GenCSR(MIE, 0x304) \
  GenCSR(MTVEC, 0x305) \
  GenCSR(MSTATUSH, 0x310) \
  GenCSR(MCAUSE, 0x342) \
  GenCSR(MEPC, 0x341) \
  GenCSR(MSCRATCH, 0x340) \
  GenCSR(MIP, 0x344) \
  GenCSR(MTVAL, 0x343) \
  GenCSR(MNEPC, 0x741) \
  GenCSR(SEPC, 0x141) \
  GenCSR(STVAL, 0x143) \
  GenCSR(STVEC, 0x105) \
  GenCSR(SCAUSE, 0x142) \
  GenCSR(SIE, 0x104) \
  GenCSR(SATP, 0x180) \
  GenCSR(SSTATUS, 0x100) \
  GenCSR(DSCRATCH0, 0x140) \
  DualCSR15(PMPCFG,,0x3A0) \
  DualCSR15(PMPADDR,,0x3B0) \

#define CSR_U_LIST \
  GenCSR(PMPADDR16_, 0x3c0) \
  DualCSR28(MHPCOUNTER3_,, 0xb03) \
  DualCSR28(MHPCOUNTER3H_,, 0xb83) \

// 生成静态常量定义
#define GenCSR(name, paddr) \
  static const uint32_t NEMU_CSR_V_##name = paddr; \
  static const uint32_t NEMU_CSR_##name = paddr;
CSR_LIST
//CSR_U_LIST
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
