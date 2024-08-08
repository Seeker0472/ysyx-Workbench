#include "am.h"
#include "trap.h"

static inline void outw(uintptr_t addr, uint16_t data) {
  *(volatile uint16_t *)addr = data;
}

int main() {
  while (1) {
    
  }
}