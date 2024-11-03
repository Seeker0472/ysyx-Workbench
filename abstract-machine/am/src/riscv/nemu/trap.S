#define concat_temp(x, y) x ## y
#define concat(x, y) concat_temp(x, y)
#define MAP(c, f) c(f)

#if __riscv_xlen == 32
#define LOAD  lw
#define STORE sw
#define XLEN  4
#else
#define LOAD  ld
#define STORE sd
#define XLEN  8
#endif

#define REGS_LO16(f) \
      f( 1)       f( 3) f( 4) f( 5) f( 6) f( 7) f( 8) f( 9) \
f(10) f(11) f(12) f(13) f(14) f(15)
#ifndef __riscv_e
#define REGS_HI16(f) \
                                    f(16) f(17) f(18) f(19) \
f(20) f(21) f(22) f(23) f(24) f(25) f(26) f(27) f(28) f(29) \
f(30) f(31)
#define NR_REGS 32
#else
#define REGS_HI16(f)
#define NR_REGS 16
#endif

#define REGS(f) REGS_LO16(f) REGS_HI16(f)

#define PUSH(n) STORE concat(x, n), (n * XLEN)(sp);
#define POP(n)  LOAD  concat(x, n), (n * XLEN)(sp);

#define CONTEXT_SIZE  ((NR_REGS + 3 + 4) * XLEN)
#define OFFSET_SP     ( 2 * XLEN)
#define OFFSET_CAUSE  ((NR_REGS + 0) * XLEN)
#define OFFSET_STATUS ((NR_REGS + 1) * XLEN)
#define OFFSET_EPC    ((NR_REGS + 2) * XLEN)

#define OFFSET_EVENT  ((NR_REGS + 3) * XLEN)
#define OFFSET_CAUSE_E  ((NR_REGS + 4) * XLEN)
#define OFFSET_REF    ((NR_REGS + 5) * XLEN)
#define OFFSET_MSG    ((NR_REGS + 6) * XLEN)

# 这里似乎是把寄存器，mcause，mstatus，mepc放在了栈上?
#### STACK
##################
# msg
# ref
# cause
# event
################## <-
#  mepc 
#  mstatus 
#  mcause 
##################
#   REGs         #
################## <---sp

.align 3
.globl __am_asm_trap
__am_asm_trap:
  addi sp, sp, -CONTEXT_SIZE

# 似乎是在复制寄存器？(保存上下文),!!不是为了保护上下文,是把他们当成Content结构体传递给了_am_irq_handle
  MAP(REGS, PUSH)

  csrr t0, mcause
  csrr t1, mstatus
  csrr t2, mepc
# 这里应该是把数据(封装成Context结构体)传递给_am_irq_handle
  STORE t0, OFFSET_CAUSE(sp)
  STORE t1, OFFSET_STATUS(sp)
  STORE t2, OFFSET_EPC(sp)
# make Event Struct!
  STORE a5, OFFSET_EVENT(sp)
  STORE a0, OFFSET_CAUSE_E(sp)
  STORE a1, OFFSET_REF(sp)
  STORE a2, OFFSET_MSG(sp)

  # set mstatus.MPRV to pass difftest
  li a0, (1 << 17)
  or t1, t1, a0
  csrw mstatus, t1

  mv a1, sp
  li a0, OFFSET_EVENT
  add a0,sp,a0

  jal __am_irq_handle
  
  mv sp,a0

  LOAD t1, OFFSET_STATUS(sp)
  LOAD t2, OFFSET_EPC(sp)
  csrw mstatus, t1
  csrw mepc, t2

  MAP(REGS, POP)

  addi sp, sp, CONTEXT_SIZE
  mret
