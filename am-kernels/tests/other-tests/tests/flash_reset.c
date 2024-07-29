#include "am.h"
#include "trap.h"
// #include "soc.h"


static inline uint32_t inl(uintptr_t addr) { return *(volatile uint32_t *)addr; }


#define SPI_MASTER 0x10001000L
void init_bit_rev(){
    outl(SPI_MASTER +0x14,0x01);//divider
}
// void send_data(){
// }
uint32_t flash_read(uint32_t addr){
    outl(SPI_MASTER + 0x18,0x01);//ss reg
    outl(SPI_MASTER + 4,addr);
    outl(SPI_MASTER + 0x10,0x910);//start
    while ((inl(SPI_MASTER + 0x10)&0x100 == 0x100));

    
}
// void wait_data(){
//     uint32_t x=inl(SPI_MASTER + 0x10);
//         x=inl(SPI_MASTER + 0x10);
//     int i = inl(SPI_MASTER)>>8;
//     assert(i==0x88);
// }
int main(){
    init_bit_rev();
    send_data();
    wait_data();
    return 0;
}