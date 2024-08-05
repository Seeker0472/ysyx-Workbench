#include "trap.h"
uint16_t *data = (uint16_t *)0xa0000000L;

void __attribute__((optimize("O0"))) set_u8() {
  data[4] = 0xff;
  // for (volatile int i = 0; i < 1000; i++)
  //   ;
  uint16_t temp = data[4];
  // for (volatile int i = 0; i < 1000; i++)
  //   ;
  check(temp==0xff);
  // data[10] = temp;
}

int main() {
  set_u8();
  return 0;
}