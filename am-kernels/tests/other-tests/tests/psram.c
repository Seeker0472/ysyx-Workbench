#include "trap.h"
// #include <cstdint>

uint8_t *data = (uint8_t *)0x80000000L;

// #define SIZE 4*1024
#define SIZE 4

void __attribute__((optimize("O0"))) set_u8() {
  // for (volatile int i = 0; i < 4*1024; i++) {
  for (volatile int i = 0; i < SIZE; i++) {
    data[i] = (uint8_t)((uint32_t)(&(data[i])) & 0xff);
    // data[i] = 0x12345678;
    // data[i] = 0x12345678;
  }
}

void __attribute__((optimize("O0"))) check_values_u8() {
  for (volatile int i = 0; i < SIZE; i++) {
    check((data)[i] == (uint8_t)((uint32_t)(&(data[i])) & 0xff));
  }
}

void __attribute__((optimize("O0"))) set_u16() {
  for (volatile int i = 0; i < SIZE/2; i++) {
    ((uint16_t *)data)[i] = (uint16_t)((uint32_t)(&(data[i])) & 0xffff);
  }
}

void __attribute__((optimize("O0"))) check_values_u16() {
  for (volatile int i = 0; i < SIZE/2; i++) {
    check(((uint16_t *)data)[i] == (uint16_t)((uint32_t)(&(data[i])) & 0xffff));
  }
}
void __attribute__((optimize("O0"))) set_u32() {
  for (volatile int i = 0; i < SIZE/4; i++) {
    ((uint32_t *)data)[i] = (uint32_t)(&(data[i]));
  }
}
void __attribute__((optimize("O0"))) check_values_u32() {
  for (volatile int i = 0; i < SIZE/4; i++) {
    check(((uint32_t *)data)[i] == (uint32_t)(&(data[i])));
  }
}

int main() {
  set_u8();
  check_values_u8();
  set_u16();
  check_values_u16();
  set_u32();
  check_values_u32();
}