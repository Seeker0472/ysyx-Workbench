// #define CSR_MTVEC 0x305
// #define CSR_MCAUSE 0x342
// #define CSR_MSTATUS 0x300
// #define ()

#include <stdint.h>
#define csr_gen(name, vaddr)  static const uint32_t CSR_##name=vaddr;
#define csr_lo_gen(name, paddr)  static const uint32_t CSR_LOCAL_##name=paddr;
#define gen(name, paddr, vaddr)  csr_gen(name, vaddr); csr_lo_gen(name, paddr);

gen(MTVEC,0x0,0x0);
