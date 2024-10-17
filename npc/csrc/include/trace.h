#include<isa.h>

void trace_and_difftest(paddr_t pc, word_t inst_in);
int update_reg_state();
void print_inst_asm(paddr_t pc, word_t inst);
void record_axi_write(const char *type, paddr_t addr, char wmask, word_t data);
void record_axi_read(const char *type, paddr_t addr, int len);
void record_pread(paddr_t addr, int len);
void record_pwrite(paddr_t addr, char wmask, word_t data);