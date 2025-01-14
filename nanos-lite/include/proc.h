#ifndef __PROC_H__
#define __PROC_H__

#include <common.h>
#include <memory.h>
#include <stdint.h>

#define STACK_SIZE (8 * PGSIZE)

typedef union {
  uint8_t stack[STACK_SIZE] PG_ALIGN;
  struct {
    Context *cp;
    AddrSpace as;
    // we do not free memory, so use `max_brk' to determine when to call _map()
    uintptr_t max_brk;
    uintptr_t active;//wheather the thread alive
  };
} PCB;

extern PCB *current;

#endif
