#include "trap.h"
uint8_t *data = (uint8_t *)0xa0000000L;

void __attribute__((optimize("O0"))) set_u8() {
  data[1] = 0xff;
  // for (volatile int i = 0; i < 1000; i++)
  //   ;
  uint8_t temp = data[1];
  // for (volatile int i = 0; i < 1000; i++)
  //   ;
  data[10] = temp;
}

int main() {
  set_u8();
  return 0;
}