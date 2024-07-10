# include <diftest.h>
#include <common.h>
#include <isa.h>
// #include <diftest.h>


extern CPU_state *cpu;
CPU_state *ref_cpu;
extern uint32_t mem[10000000];
extern word_t mem_size;

//temp!!
extern const char *regs[];
void reg_display(CPU_state *cpu) {
  printf("================================================regs================================================\n");
  printf("%-4s \t%-20s\t%-10s\t","Name","Dec","Hex");  
  printf(" | ");
  printf("%-4s \t%-20s\t%-10s\t\n","Name","Dec","Hex");
#ifdef CONFIG_RVE
  for(int i=0;i<8;i++){
    MUXDEF(CONFIG_RV64,printf("%-4s \t%-20ld\t%-10lx\t",regs[i],cpu->gpr[i],cpu->gpr[i]);,printf("%-4s \t%-20d\t%-10x\t",regs[i],cpu->gpr[i],cpu->gpr[i]););
      
      printf(" | ");
    MUXDEF(CONFIG_RV64,printf("%-4s \t%-20ld\t%-10lx\t",regs[i+8],cpu->gpr[i+8],cpu->gpr[i+8]);,printf("%-4s \t%-20d\t%-10x\t",regs[i+8],cpu->gpr[i+8],cpu->gpr[i+8]););

      
      printf("\n");
  }
#elif
  for(int i=0;i<16;i++){
    MUXDEF(CONFIG_RV64,printf("%-4s \t%-20ld\t%-10lx\t",regs[i],cpu->gpr[i],cpu->gpr[i]);,printf("%-4s \t%-20d\t%-10x\t",regs[i],cpu->gpr[i],cpu->gpr[i]););
      
      printf(" | ");
    MUXDEF(CONFIG_RV64,printf("%-4s \t%-20ld\t%-10lx\t",regs[i+16],cpu->gpr[i+16],cpu->gpr[i+16]);,printf("%-4s \t%-20d\t%-10x\t",regs[i+16],cpu->gpr[i+16],cpu->gpr[i+16]););

      
      printf("\n");
  }
#endif

  MUXDEF(CONFIG_RV64,printf("%-4s \t%-20ld\t%-10lx\t\n","pc",cpu.pc,cpu.pc);,printf("%-4s \t%-20d\t%-10x\t\n","pc",cpu->pc,cpu->pc);)
}


bool difftest_check_regs(){
    if(cpu->pc!=ref_cpu->pc)
    for(int i=0;i<MUXDEF(CONFIG_RVE,16,32);i++){
        if(cpu->gpr[i]!=ref_cpu->gpr[i]){
            reg_display(cpu);
            reg_display(ref_cpu);

            printf("----------------%d\n",i);
            return false;
        }
    }
    return true;
}
void difftest_check_state(){
    difftest_regcpy(ref_cpu,DIFFTEST_TO_DUT);
    if(!difftest_check_regs()){
        assert(0);
    }
}


void difftest_init_all(){
    difftest_init(0);
    ref_cpu=(CPU_state*)malloc(sizeof(CPU_state));
    difftest_regcpy(cpu,DIFFTEST_TO_REF);
    difftest_memcpy(0x80000000,mem,mem_size,DIFFTEST_TO_REF);
}
