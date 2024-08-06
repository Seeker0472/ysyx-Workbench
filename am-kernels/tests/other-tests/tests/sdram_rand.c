#include "trap.h"

uint8_t *memory = (uint8_t *)0xa0001000;
uint8_t *memory1 = (uint8_t *)0xa0021100;

// #define SIZE 4 * 1024
#define SIZE 100

void set_u8() {
  for (int i = 0; i < SIZE; i++) {
    memory[i] = (uint8_t)((uint32_t)(memory + i) & 0xff);
    memory1[i] = (uint8_t)((uint32_t)(memory1 + i) & 0xff);
  }
}

void check_values_u8() {
  for (int i = 0; i < SIZE; i++) {
    check((memory)[i] == (uint8_t)((uint32_t)(memory + i) & 0xff));
    check((memory1)[i] == (uint8_t)((uint32_t)(memory1 + i) & 0xff));
  }
}

void set_u16() {
  for (int i = 0; i < SIZE / 2; i++) {
    ((uint16_t *)memory)[i] = (uint16_t)((uint32_t)(memory + i) & 0xffff);
    ((uint16_t *)memory1)[i] = (uint16_t)((uint32_t)(memory1 + i) & 0xffff);
  }
}

void check_values_u16() {
  for (int i = 0; i < SIZE / 2; i++) {
    check(((uint16_t *)memory)[i] ==
          (uint16_t)((uint32_t)(memory + i) & 0xffff));
    check(((uint16_t *)memory1)[i] ==
          (uint16_t)((uint32_t)(memory1 + i) & 0xffff));
  }
}
void set_u32() {
  for (int i = 0; i < SIZE / 4; i++) {
    ((uint32_t *)memory)[i] = (uint32_t)(memory + i);
    ((uint32_t *)memory1)[i] = (uint32_t)(memory1 + i);
  }
}
void check_values_u32() {
  for (int i = 0; i < SIZE / 4; i++) {
    check(((uint32_t *)memory)[i] == (uint32_t)(memory + i));
    check(((uint32_t *)memory1)[i] == (uint32_t)(memory1 + i));
  }
}

int main() {
  set_u8();
  check_values_u8();
  set_u16();
  check_values_u16();
  set_u32();
  check_values_u32(); 
  return 0;
}