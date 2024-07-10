# include <diftest.h>
#include <common.h>
#include <isa.h>
// #include <diftest.h>


extern CPU_state *cpu;
CPU_state *ref_cpu;
extern uint32_t mem[10000000];
extern word_t mem_size;

bool difftest_check_regs(){
    return true;
}
void difftest_check_state(){
    if(!difftest_check_regs()){

    }
}


void difftest_init_all(){
    difftest_init(0);
    ref_cpu=(CPU_state*)malloc(sizeof(CPU_state));
    difftest_regcpy(cpu,DIFFTEST_TO_REF);
    difftest_memcpy(0x80000000,mem,mem_size,DIFFTEST_TO_REF);
}