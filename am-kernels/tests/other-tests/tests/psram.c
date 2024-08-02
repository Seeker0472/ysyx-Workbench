#include "trap.h"

uint8_t *data = (uint8_t *)0x80000000L;

void __attribute__((optimize("O0"))) set() {
  for (volatile int i = 0; i < 10; i++) {
    data[i] = (uint8_t)((uint32_t)(&(data[i])) & 0xff);
    // data[i] = i;
    // data[i] = 0x12345678;
  }
}

void __attribute__((optimize("O0"))) check_values() {
  for (volatile int i = 0; i < 10; i++) {
    check(data[i] == (uint8_t)((uint32_t)(&(data[i])) & 0xff));
    // check(data[i] == i);
  }
  // check(data[1]==1);
}

int main() {
  set();
  check_values();
}