#include <common.h>
#include "syscall.h"
void do_syscall(Context *c) {
  printf("syscall:%d,%d,%d,%d\n", c->GPR1, c->GPR2, c->GPR3, c->GPR4);
  uintptr_t a[4];
  a[0] = c->GPR1;

  switch (a[0]) {
  case SYS_exit:
    halt(0);
    break;
  case SYS_yield:
    yield();
    // return 0;
    c->GPRx=0;
    break;
  case SYS_write:
    // temp solution as the write to fs also calls
    // printf("%s",(char *)c->GPR3);
    for (int i = 0; i <= c->GPR4; i++)
      putch(((char*)c->GPR3)[i]);
    break;
    default: panic("Unhandled syscall ID = %d", a[0]);
  }
}
