#include "trap.h"
uint8_t *data = (uint8_t *)0x80000000L;

void __attribute__((optimize("O0"))) set_u8() {
  data[0] = 0xff;
  // for (volatile int i = 0; i < 1000; i++)
  //   ;
  uint8_t temp = data[0];
  // for (volatile int i = 0; i < 1000; i++)
  //   ;
  data[10] = temp;
}

int main() {
  set_u8();
  return 0;
}