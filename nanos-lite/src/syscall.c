#include <common.h>
#include "syscall.h"
#include "fs.h"

// uintptr_t end_symbol;
extern char * get_filename(int fd);
const char *event_names[] = {
    "SYS_exit",  "SYS_yield",  "SYS_open",   "SYS_read",   "SYS_write",
    "SYS_kill",  "SYS_getpid", "SYS_close",  "SYS_lseek",  "SYS_brk",
    "SYS_fstat", "SYS_time",   "SYS_signal", "SYS_execve", "SYS_fork",
    "SYS_link",  "SYS_unlink", "SYS_wait",   "SYS_times",  "SYS_gettimeofday"};

void do_syscall(Context *c) {
#ifdef STRACE_ENABLE
  switch (c->GPR3) {
  case SYS_open:
  case SYS_read:
  case SYS_write:
  case SYS_lseek:
  case SYS_close:
    Log("Syscall: %s,%s,0x%x,0x%x\n", event_names[c->GPR1], get_filename(c->GPR2), c->GPR3, c->GPR4);
    break;
  default:
    Log("Syscall: %s,0x%x,0x%x,0x%x\n", event_names[c->GPR1], c->GPR2, c->GPR3, c->GPR4);
    break;
  }
#endif
  uintptr_t a[4];
  a[0] = c->GPR1;
  a[1] = c->GPR2;
  a[2] = c->GPR3;
  a[3] = c->GPR4;

  switch (a[0]) {
  case SYS_exit:
    halt(0);
    break;
  case SYS_yield:
    yield();
    c->GPRx=0;
    break;
  case SYS_write:
    c->GPRx = fs_write(a[1], (void *)a[2], a[3]);
    break;
  case SYS_read:
    c->GPRx = fs_read(a[1], (void *)a[2], a[3]);
    break;
  case SYS_open:
    c->GPRx = fs_open((const char *)a[1], a[2], a[3]);
    break;
  case SYS_close:
    c->GPRx = fs_close(a[1]);
    break;
  case SYS_lseek:
    c->GPRx = fs_lseek(a[1], a[2], a[3]);
    break;
  case SYS_brk:
    c->GPRx = 0;
    break;
    default: panic("Unhandled syscall ID = %d", a[0]);
  }
}
