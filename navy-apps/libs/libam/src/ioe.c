#include <am.h>
#include <stdlib.h>
#define HEAP_SIZE 0x80000
bool ioe_init() {
  heap.start = malloc(HEAP_SIZE);
  heap.end = heap.start+HEAP_SIZE;
  return true;
}

void ioe_read (int reg, void *buf) { }
void ioe_write(int reg, void *buf) { }
