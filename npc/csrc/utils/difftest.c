# include <diftest.h>
#include <common.h>
#include <isa.h>
// #include <diftest.h>


extern CPU_state *cpu;
CPU_state *ref_cpu;
extern uint32_t mem[10000000];
extern word_t mem_size;
void reg_display_diff(CPU_state* nemu);


bool difftest_check_regs(){
    if(cpu->pc!=ref_cpu->pc)
    for(int i=0;i<MUXDEF(CONFIG_RVE,16,32);i++){
        if(cpu->gpr[i]!=ref_cpu->gpr[i]){
          reg_display_diff(ref_cpu);
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
