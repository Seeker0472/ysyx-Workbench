#include "am.h"
#include <common.h>
void do_syscall(Context *c);
void trace_event(Event e) {
  printf("Event Type: %d Cause: %lu Reference: %lu Message: %s\n", e.event,
         e.cause, e.ref, e.msg?e.msg:"NULL");
}
static Context *do_event(Event e, Context *c) {
  // IFDEF(STRACE_ENABLE, trace_event(e););
#ifdef STRACE_ENABLE
  // trace_event(e);
#endif
  switch (e.event) {
  case EVENT_YIELD:
    printf("YIELD!");
    // do_syscall(c);
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
