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
    // outl(SPI_MASTER + 0x10,0x240);//start'
    outl(SPI_MASTER + 0x18,0x01);//ss reg
    outl(SPI_MASTER + 4 ,(addr&0x00ffffff)|0x03000000);//send_addr
    outl(SPI_MASTER + 0x10,0x540);//start'

    while (((inl(SPI_MASTER + 0x10)&0x100) == 0x100));//等待
    uint32_t result = inl(SPI_MASTER);
    uint32_t val = ((result&0xff)<<24)|((result&0xff00)<<8)|((result&0xff0000)>>8)|((result&0xff000000)>>24);
    outl(SPI_MASTER + 0x18,0x00);
    return val;
}
void check_flash(){
    // for(int i=0;i<1000;i++)
    //     check(flash_read((uint32_t)(data+i))==i);
    for(int i=1;i<100;i++)
        printf("%x\n",data[i]);
}

int main(){
    init_bit_rev();
     check_flash();
    return 0;
}