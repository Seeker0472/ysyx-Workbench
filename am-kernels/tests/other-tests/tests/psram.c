#include "trap.h"

uint32_t * data = (uint32_t *)0x80000000L;

void __attribute__((optimize("O0"))) set() {
  for (volatile int i = 0; i < 100; i++) {
    // data[i] = (uint8_t)((uint32_t)(&(data[i])) & 0xff);
    data[i] = 0x12345678;
  }
}

void __attribute__((optimize("O0"))) check_values() {
  for (volatile int i = 0; i < 100; i++) {
    check(data[i] == (uint8_t)((uint32_t)(&(data[i])) & 0xff));
  }
}

int main() {
  set();
  check_values();
}