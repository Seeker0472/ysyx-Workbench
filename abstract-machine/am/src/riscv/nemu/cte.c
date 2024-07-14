#include <am.h>
#include <riscv/riscv.h>
#include <klib.h>

static Context* (*user_handler)(Event, Context*) = NULL;

Context* __am_irq_handle(Context *c) {
  printf("c.mepc=%x mstatus=%x mcause=%x\n",c->mepc,c->mstatus,c->mcause);

  if (user_handler) {
    Event ev = {0};
    switch (c->mcause) {
      default: ev.event = EVENT_ERROR; break;
    }

    c = user_handler(ev, c);
    assert(c != NULL);
  }

  return c;
}

extern void __am_asm_trap(void);

bool cte_init(Context*(*handler)(Event, Context*)) {
  // initialize exception entry
  asm volatile("csrw mtvec, %0" : : "r"(__am_asm_trap));
  //这里是将变量__am_asm_trap的值写入RISC-V处理器的mtvec寄存器。
  //mtvec(Machine Trap Vector)寄存器用于存储陷阱向量的基地址，当处理器发生异常或中断时，会跳转到这个地址去执行相应的处理程序。
  //TODO:实现这个寄存器

  //在Trap.S中，会跳转到__am_irq_handle
  //TODO:这个Handler应该是操作系统注册的？

  // register event handler
  user_handler = handler;

  return true;
}

Context *kcontext(Area kstack, void (*entry)(void *), void *arg) {
  return NULL;
}

void yield() {
#ifdef __riscv_e
  asm volatile("li a5, -1; ecall");
#else
  asm volatile("li a7, -1; ecall");
#endif
}

bool ienabled() {
  return false;
}

void iset(bool enable) {
}
