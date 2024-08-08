#include "am.h"
#include "trap.h"
#include <stdint.h>

static inline void outw(uintptr_t addr, uint16_t data) {
  *(volatile uint16_t *)addr = data;
}

int main() {
  uint16_t num=0;
  while (1) {
    // putch(0);
    outw(0x10002000L, num++);
  }
}