#include "trap.h"

volatile uint8_t *memory = (uint8_t *)0xc0000000;

#define SIZE 4 * 1024
// #define SIZE 4

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
  for (int i = 0; i < SIZE / 4; i++) {{
      ((uint32_t *)memory)[i] = (uint32_t)(memory + i);
      ((uint32_t *)memory)[10000] = (uint32_t)(memory + i);
    }
// {
//   ((uint32_t *)memory)[i] = 0xaa;
//   ((uint32_t *)memory)[1000] = 0xaa;
//     // for (volatile int i = 100; i < 1000; i++)
//     //   ;
//   }
  }
}
void check_values_u32() {
  for (int i = 0; i < SIZE / 4; i++) {
    // printf("%d\n\n\n",((uint16_t *)memory)[i]);
    check(((uint32_t *)memory)[i] == (uint32_t)(memory + i));
  }
}
  
int main() {
  // printf("Testing mem_area[%x---%x]\n", memory, memory + SIZE);
  // printf("setting Uint8\n");
  // set_u8();
  // printf("checking Uint8\n");
  // check_values_u8();
  // printf("setting Uint16\n");
  // set_u16();
  // printf("checking Uint16\n");
  // check_values_u16();
  printf("setting Uint32\n");
  set_u32();
  printf("checking Uint32\n");
  check_values_u32();
  printf("mem-check OKEY!\n");
  return 0;
}