#include "stdio.h"
#include "stdint.h"
#include <stdio.h>
#include "common.h"
FILE *fp;
void trace_pc(vaddr_t pc, word_t inst, int rs1, int rs2, int rd) {
  fprintf(fp, "%x\n", pc);
}
void init_pc_trace() { fp = fopen("pc_trace", "w"); }
void close_pc_trace() {
  fclose(fp);
}