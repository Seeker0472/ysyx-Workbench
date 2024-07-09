#include <stdint.h>
#include <macro.h>
#include <debug.h>

#define word_t uint32_t 
#define paddr_t uint32_t 

//TODO:寄存器的数量！！
typedef struct {
  word_t gpr[32];
  vaddr_t pc;
} CPU_state;

word_t isa_reg_str2val(const char *s, bool *success);
int run(int step);
void isa_reg_display();