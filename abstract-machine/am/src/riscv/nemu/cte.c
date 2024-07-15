#include <am.h>
#include <riscv/riscv.h>
#include <klib.h>

static Context* (*user_handler)(Event, Context*) = NULL;

Context* __am_irq_handle(Context *c) {
  if (user_handler) {
      printf("mcause:::::::::%x\n",c->mcause);
    Event ev = {0};
    switch (c->mcause) {
      default:  c->mepc += 4; ev.event = EVENT_YIELD; break;
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
  //TODO:是不是要在栈上放置点什么东西(是应该把内容保存在栈上吗)
  // Context * con= malloc(sizeof(Context));
  // Context *bottom=(Context *)kstack.end;
  Context *top=(Context *)(((void *)kstack.end)-sizeof(Context));
  top->mepc=(uintptr_t)entry;
  top->mstatus=0x1800;
  top->mcause=0xb;
  return top;
  // return NULL;
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
