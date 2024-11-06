#include <common.h>
#include "syscall.h"
#include "fs.h"

// uintptr_t end_symbol;

const char *syscall_names[] = {
    "SYS_exit",  "SYS_yield",  "SYS_open",   "SYS_read",   "SYS_write",
    "SYS_kill",  "SYS_getpid", "SYS_close",  "SYS_lseek",  "SYS_brk",
    "SYS_fstat", "SYS_time",   "SYS_signal", "SYS_execve", "SYS_fork",
    "SYS_link",  "SYS_unlink", "SYS_wait",   "SYS_times",  "SYS_gettimeofday"};

void do_syscall(Context *c) {
#ifdef STRACE_ENABLE
  Log("syscall:0x%s,0x%x,0x%x,0x%x\n", syscall_names[c->GPR1], c->GPR2, c->GPR3, c->GPR4);
#endif
  uintptr_t a[4];
  a[0] = c->GPR1;

  switch (a[0]) {
  case SYS_exit:
    halt(0);
    break;
  case SYS_yield:
    yield();
    c->GPRx=0;
    break;
  case SYS_write:
    c->GPRx = fs_write(c->GPR2, (void *)c->GPR3, c->GPR4);
    break;
  case SYS_read:
    c->GPRx = fs_read(c->GPR2, (void *)c->GPR3, c->GPR4);
    break;
  case SYS_open:
    c->GPRx=fs_open((const char *)c->GPR2,c->GPR3,c->GPR4);
    break;
  case SYS_close:
    c->GPRx = fs_close(c->GPR2);
    break;
  case SYS_lseek:
    c->GPRx = fs_lseek(c->GPR2, c->GPR3, c->GPR4);
    break;
  case SYS_brk:
    c->GPRx = 0;
    break;
    default: panic("Unhandled syscall ID = %d", a[0]);
  }
}
