#include "am.h"
#include "trap.h"
#include <stdint.h>
#include <stdio.h>

#define GPIO_BASE 0x10002000L

static inline void outw(uintptr_t addr, uint16_t data) {
  *(volatile uint16_t *)addr = data;
}
static inline uint32_t inl(uintptr_t addr) {
  return *(volatile uint32_t *)addr;
}
int main() {
  uint16_t num=1;
  while (1) {
    // putch(0);
    outw(GPIO_BASE, num);
    num = (num << 1) | (num >> (15));
    for (volatile int i = 0; i < 1000; i++)
      ;
    printf("%x\n", inl(GPIO_BASE+4));
  }
}