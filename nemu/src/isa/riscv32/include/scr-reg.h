// the translate logic was defined in
// nemu/src/isa/riscv32/local-include/reg.h
// remember to update the display func in
// nemu/src/isa/riscv32/reg.c

#include <stdint.h>
#define csr_gen(name, vaddr)  static const uint32_t NEMU_CSR_V_##name=vaddr;
#define csr_lo_gen(name, paddr)  static const uint32_t NEMU_CSR_##name=paddr;
#define gen(name, vaddr, paddr)  csr_gen(name, vaddr); csr_lo_gen(name, paddr);

gen(MTVEC, 0x305, 0x0);
gen(MCAUSE, 0x342, 0x1);
gen(MSTATUS, 0x300, 0x2);
gen(MEPC, 0x341, 0x3);
gen(MVENDROID, 0xF11, 0x4);
gen(MARCHID, 0xF12, 0x5);
gen(SATP, 0x180, 0x6);
gen(MSCRATCH,0x340,0x7)
