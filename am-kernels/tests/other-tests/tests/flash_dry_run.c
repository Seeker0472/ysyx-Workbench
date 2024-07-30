#include "trap.h"
#define SPI_MASTER 0x10001000L
uint32_t * flash_addr = (uint32_t *)0x30000000L;


static inline uint32_t inl(uintptr_t addr) { return *(volatile uint32_t *)addr; }
static inline void outl(uintptr_t addr, uint32_t data) { *(volatile uint32_t *)addr = data; }


int main(){
    void (*flash)(void) = (void (*)(void))flash_addr;
    flash();
    return 0;
}