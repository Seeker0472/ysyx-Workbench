#### STACK
##################
#  mepc 
#  mstatus 
#  mcause 
##################
#   REGs         #
################## <---sp


# 一些约定
# ksp=0 -> from kernel;ksp!=0then is the kernel addr
# c->sp => $sp's value before trap(no usp)

__am_asm_trap_draft:
# stage 1-detect user-mod and make sure sp->kernel stack!
  csrrw sp, mscratch, sp   // (1) atomically exchange sp and mscratch
  bnez sp, save_context    // (2) take the branch if we trapped from user
  csrrw sp, mscratch, sp   // (3) if we trapped from kernel, restore the original sp

# Kernel:mscrach=0;sp==kern;
# User: $sp=kernel mscratch=user_stack

# stage-2 save_context!
# note that c->gpr[sp] should always be $sp before trap
# note thar c->gpr[sp] will not be copied by MAP!
save_context:
  // now sp is pointing to the kernel stack
  // save the context... 
  addi sp, sp, -CONTEXT_SIZE

  # Store Data on stack and pass them to _am_irq_handle!
  MAP(REGS, PUSH)

  csrr t0, mcause
  csrr t1, mstatus
  csrr t2, mepc
  csrr t3, mscratch #TODO:add the reg in menu and change the context size
  # calc origional sp;t4 stores the np!
  addi t4, sp, CONTEXT_SIZE
  bnez t3,from_kern
  # mstatus==0;user_mod!
  li t5,0 
  mv t4,t3
  j b_end
from_kern:
  # mstatus!=0;kernel_mod!
  t5,1
b_end:

  STORE t0, OFFSET_CAUSE(sp)
  STORE t1, OFFSET_STATUS(sp)
  STORE t2, OFFSET_EPC(sp)
  STORE t3, OFFSET_SCRATCH(sp)
  STORE t4, OFFSET_SP(sp) # set sp(sp before trap)
#  STORE t5, OFFSET_NP(sp)# set np,not used?

# stage-3 set mstatus.MPRV?--pass difftest??<-TODO:need to change?
  li a0, (1 << 17)
  or t1, t1, a0
  csrw mstatus, t1

# stage-4 call __am_irq_handle
  mv a0, sp
  jal __am_irq_handle
  mv sp,a0

# stage-5 restore context
  LOAD t1, OFFSET_STATUS(sp)
  LOAD t2, OFFSET_EPC(sp)
  csrw mstatus, t1
  csrw mepc, t2

  MAP(REGS, POP)

# stage-6 
# if np==user update ksp(ksp=$sp)
# restore $sp($sp = c->sp)  

# now sp is pointing at ksp+Context
# check if mscratch==0(kernelmod)
  LOAD sp OFFSET_SP(sp)
  csrrw sp,mscratch,sp # atm switch sp
  bnez sp to_user
# return to kernel
# kern -> kern;
  csrrw sp,mscratch,sp # restore sp
  addi sp, sp, CONTEXT_SIZE
  j end_ret
to_user:
# return to user
# user -> user;
  csrrw sp,mscratch,sp # restore sp
  addi sp, sp, CONTEXT_SIZE
  csrrw sp,mscratch,sp # now the user's stack pointer

end_ret:
  mret