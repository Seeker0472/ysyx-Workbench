#include "am.h"
#include "trap.h"
// #include "soc.h"

static inline uint8_t  inb(uintptr_t addr) { return *(volatile uint8_t  *)addr; }
static inline uint16_t inw(uintptr_t addr) { return *(volatile uint16_t *)addr; }
static inline uint32_t inl(uintptr_t addr) { return *(volatile uint32_t *)addr; }

static inline void outb(uintptr_t addr, uint8_t  data) { *(volatile uint8_t  *)addr = data; }
static inline void outw(uintptr_t addr, uint16_t data) { *(volatile uint16_t *)addr = data; }
static inline void outl(uintptr_t addr, uint32_t data) { *(volatile uint32_t *)addr = data; }


#define SPI_MASTER 0x10001000L

void init_bit_rev(){
    outl(SPI_MASTER +0x14,0x02);
}
void send_data(){
    outl(SPI_MASTER + 0x18,0x7);//ss reg
    // outl(SPI_MASTER + 0x10,0x140f);//ctrl reg
    outl(SPI_MASTER + 0x10,0x148f);//start
    outl(SPI_MASTER,0x7);
    outl(SPI_MASTER + 0x10,0x140f);//ctrl reg

}
void wait_data(){
    while((inl(SPI_MASTER+0x10)&0x80)==1)
        continue;
    inl(SPI_MASTER);
}
int main(){
    init_bit_rev();
    send_data();
    wait_data();
    return 0;
}