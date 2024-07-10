#include <isa.h>
#include<stdio.h>

CPU_state* cpu;

const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

void isa_reg_display() {
  printf("================================================regs================================================\n");
  printf("%-4s \t%-20s\t%-10s\t","Name","Dec","Hex");  
  printf(" | ");
  printf("%-4s \t%-20s\t%-10s\t\n","Name","Dec","Hex");
  for(int i=0;i<MUXDEF(CONFIG_RVE, 8, 16);i++){
    MUXDEF(CONFIG_RV64,printf("%-4s \t%-20ld\t%-10lx\t",regs[i],cpu->gpr[i],cpu->gpr[i]);,printf("%-4s \t%-20d\t%-10x\t",regs[i],cpu->gpr[i],cpu->gpr[i]););
      
      printf(" | ");
    MUXDEF(CONFIG_RV64,printf("%-4s \t%-20ld\t%-10lx\t",regs[i+16],cpu->gpr[i+16],cpu->gpr[i+16]);,printf("%-4s \t%-20d\t%-10x\t",regs[i+16],cpu->gpr[i+16],cpu->gpr[i+16]););

      
      printf("\n");
  }
  MUXDEF(CONFIG_RV64,printf("%-4s \t%-20ld\t%-10lx\t\n","pc",cpu.pc,cpu.pc);,printf("%-4s \t%-20d\t%-10x\t\n","pc",cpu->pc,cpu->pc);)
  
}



//获取寄存器的值，s应该传入$xx
word_t isa_reg_str2val(const char *s, bool *success) {
  *success=false;
  // printf("%lu",cpu.pc);
  if(s[0]=='$')
    s+=1;
  if(strcmp(s,"pc")==0){
    *success=true;
    return cpu->pc;
  }
  for(int i=0;i<32;i++){
    if(strcmp(regs[i],s)==0){
      *success=true;
      return cpu->gpr[i];
    }
  }
  return 0;
}

void init_reg(){
  cpu=(CPU_state*)malloc(sizeof(CPU_state));
}