#include "am.h"
#include "trap.h"
// #include "soc.h"


static inline uint32_t inl(uintptr_t addr) { return *(volatile uint32_t *)addr; }
static inline void outl(uintptr_t addr, uint32_t data) { *(volatile uint32_t *)addr = data; }


uint32_t * data = (uint32_t *)0x30000000L;

#define SPI_MASTER 0x10001000L
void init_bit_rev(){
    outl(SPI_MASTER +0x14,0x11);//divider
}
uint32_t flash_read(uint32_t addr){
    outl(SPI_MASTER + 0x10,0x240);//start'
    outl(SPI_MASTER + 0x18,0x01);//ss reg
    outl(SPI_MASTER + 4 ,(addr&0x00ffffff)|0x03000000);//send_addr
    outl(SPI_MASTER + 0x10,0x340);//start'

    while (((inl(SPI_MASTER + 0x10)&0x100) == 0x100));//等待
    uint32_t result = inl(SPI_MASTER);
    outl(SPI_MASTER + 0x18,0x00);
    return result;
}
void check_flash(){
    for(int i=0;i<1;i++)
        putch(flash_read((uint32_t)(data+i)));
        // check(flash_read((uint32_t)(data+i))==i);

}

int main(){
    init_bit_rev();
     check_flash();
    return 0;
}