#include "am.h"
#include <common.h>

char *syscall_names[] = {
    "EVENT_NULL",  "EVENT_YIELD",     "EVENT_SYSCALL",   "EVENT_PAGEFAULT",
    "EVENT_ERROR", "EVENT_IRQ_TIMER", "EVENT_IRQ_IODEV"
};

void do_syscall(Context *c);
void trace_event(Event e) {
  Log("Event Type: %s Cause: %x Reference: %x Message: %s\n",syscall_names[e.event] , e.cause,
      e.ref, e.msg ? e.msg : "NULL");
}
static Context *do_event(Event e, Context *c) {
  // IFDEF(STRACE_ENABLE, trace_event(e););
#ifdef STRACE_ENABLE
  trace_event(e);
#endif
  switch (e.event) {
  case EVENT_YIELD:
    printf("YIELD!");
    break;
  case EVENT_SYSCALL:
    // printf("syscall!");
    do_syscall(c);
    break;
    default: panic("Unhandled event ID = %d", e.event);
  }

  return c;
}

void init_irq(void) {
  Log("Initializing interrupt/exception handler...");
  cte_init(do_event);
}
