#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main() {
  uint32_t *small = malloc(sizeof(uint32_t));
  printf("small:%x",small);
  uint32_t *med = malloc(sizeof(uint32_t) * 0x100);
  printf("small:%x",med);
  uint32_t *large = malloc(sizeof(uint32_t)*0x1000);
  printf("small:%x",large);
  printf("PASS!!!\n");

  return 0;
}
