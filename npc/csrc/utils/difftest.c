# include <diftest.h>
#include <common.h>
#include <isa.h>
#include <diftest.h>


extern CPU_state *cpu;
extern CPU_state *ref_cpu;

void difftest_check_state(){
    if(!difftest_check_regs()){

    }
}
bool difftest_check_regs(){
    return true;
}

void difftest_init_all(){
    difftest_init(0);
    ref_cpu=malloc(sizeof(CPU_state));
    difftest_regcpy(cpu,DIFFTEST_TO_REF);
    // difftest_memcpy();
}