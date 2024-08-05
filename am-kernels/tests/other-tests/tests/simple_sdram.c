#include "trap.h"
uint32_t *data = (uint32_t *)0xa0000000L;

void __attribute__((optimize("O0"))) set_u8() {
  data[0] = 0x1234;
  data[1] = 0x9876;
  // for (volatile int i = 0; i < 1000; i++)
  //   ;
  uint32_t temp = data[1];
  // for (volatile int i = 0; i < 1000; i++)
  //   ;
  check(temp==0x9876);
  // data[10] = temp;
}

int main() {
  set_u8();
  return 0;
}