// # include <diftest.h>
// #include <common.h>
// #include <isa.h>
#include "../include/diftest.h"
#include "../include/ydb_all.h"
#include "utils.h"


extern CPU_state *cpu;
CPU_state *ref_cpu;
extern uint32_t *mem;
extern uint32_t* mrom;
extern uint32_t* flash;
extern word_t mem_size;
void reg_display_diff(CPU_state* nemu);

extern const char *regs[];

bool difftest_check_regs(){
    // if(cpu->pc!=ref_cpu->pc)
    if(!difftest_check_reg("pc",cpu->pc,ref_cpu->pc,cpu->pc))
      return false;
    for(int i=0;i<MUXDEF(CONFIG_RVE,16,32);i++){
      // printf("-----------------------------------------%d\n",i);
        if(!difftest_check_reg(regs[i],cpu->pc,ref_cpu->gpr[i],cpu->gpr[i]))
          return false;
    }
    return true;
}
void difftest_check_state(){
    difftest_regcpy(ref_cpu,DIFFTEST_TO_DUT);
    if(!difftest_check_regs()){
      reg_display_diff(ref_cpu);
      // assert(0);
      nemu_state.state = NEMU_ABORT;
      nemu_state.halt_ret=-1;
    }
}

void difftest_copy_regs() { difftest_regcpy(cpu, DIFFTEST_TO_REF); }

void difftest_init_all(){
    difftest_init(0);
    ref_cpu=(CPU_state*)malloc(sizeof(CPU_state));
    difftest_copy_regs();
    // difftest_memcpy(0x20000000,mrom,4 * 1024 *
    // sizeof(uint8_t),DIFFTEST_TO_REF);
#ifdef NPC
    difftest_memcpy(0x80000000, mem, mem_size, DIFFTEST_TO_REF);
#else
    difftest_memcpy(0x30000000, flash, mem_size, DIFFTEST_TO_REF);
#endif
}

