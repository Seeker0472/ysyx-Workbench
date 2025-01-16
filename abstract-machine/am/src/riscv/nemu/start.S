.section entry, "ax"
.globl _start
.type _start, @function

_start:
  mv s0, zero
  la sp, _stack_pointer
  li a1,0x40000
  csrw sstatus,a1
  jal _trm_init
