.section entry, "ax"
.globl _start
.type _start, @function

_start:
  mv s0, zero
  la sp, _stack_pointer
  li a1,0x41800
  csrr a2,mstatus
  or a2,a1,a2
  csrw mstatus,a1
  jal _trm_init
