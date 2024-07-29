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
    outl(SPI_MASTER + 4,addr);//send_addr
    outl(SPI_MASTER + 0x18,0x01);//ss reg
    outl(SPI_MASTER + 0x10,0x910);//start
    while (((inl(SPI_MASTER + 0x10)&0x100) == 0x100));//等待
    uint32_t result = inl(SPI_MASTER);
    return result;
}

void check_flash(){
    for(int i=0;i<1000;i++)
        check(flash_read((uint32_t)(data+i))==i);
}

int main(){
    init_bit_rev();
     check_flash();
    return 0;
}