#include "am.h"
#include "trap.h"
// #include "soc.h"


static inline uint32_t inl(uintptr_t addr) { return *(volatile uint32_t *)addr; }


#define SPI_MASTER 0x10001000L
// void init_bit_rev(){
//     outl(SPI_MASTER +0x14,0x01);
// }
// void send_data(){
//     outl(SPI_MASTER + 0x18,0x01);//ss reg
//     outl(SPI_MASTER + 0x10,0x810);//start
//     outl(SPI_MASTER,0x11);
//     outl(SPI_MASTER + 0x10,0x910);//start
// }

// void wait_data(){
//     uint32_t x=inl(SPI_MASTER + 0x10);
//     while ((((uint32_t)x) == 0x000000910))
//         x=inl(SPI_MASTER + 0x10);
//     int i = inl(SPI_MASTER)>>8;
//     assert(i==0x88);
// }
// int main(){
//     init_bit_rev();
//     send_data();
//     wait_data();
//     return 0;
// }