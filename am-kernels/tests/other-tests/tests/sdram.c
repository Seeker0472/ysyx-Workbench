#include "trap.h"

uint8_t *memory = (uint8_t *)0xa0000000;

#define SIZE 4 * 1024
// #define SIZE 4*1024*1024

void set_u8() {
  for (int i = 0; i < SIZE; i++) {
    memory[i] = (uint8_t)((uint32_t)(memory + i) & 0xff);
  }
}

void check_values_u8() {
  for (int i = 0; i < SIZE; i++) {
    check((memory)[i] == (uint8_t)((uint32_t)(memory + i) & 0xff));
  }
}

void set_u16() {
  for (int i = 0; i < SIZE / 2; i++) {
    ((uint16_t *)memory)[i] = (uint16_t)((uint32_t)(memory + i) & 0xffff);
  }
}

void check_values_u16() {
  for (int i = 0; i < SIZE / 2; i++) {
    check(((uint16_t *)memory)[i] ==
          (uint16_t)((uint32_t)(memory + i) & 0xffff));
  }
}
void set_u32() {
  for (int i = 0; i < SIZE / 4; i++) {
    ((uint32_t *)memory)[i] = (uint32_t)(memory + i);
  }
}
void check_values_u32() {
  for (int i = 0; i < SIZE / 4; i++) {
    check(((uint32_t *)memory)[i] == (uint32_t)(memory + i));
  }
}
  
int main() {
  printf("Testing mem_area[%x---%x]\n", memory, memory + SIZE);
  printf("setting Uint8\n");
  set_u8();
  printf("checking Uint8\n");
  check_values_u8();
  printf("setting Uint16\n");
  set_u16();
  printf("checking Uint16\n");
  check_values_u16();
  printf("setting Uint32\n");
  set_u32();
  printf("checking Uint32\n");
  check_values_u32();
  printf("mem-check OKEY!\n");
  return 0;
}