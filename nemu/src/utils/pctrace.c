#include "stdio.h"
#include "stdint.h"
#include <stdio.h>
#include "common.h"
FILE *fp;
void trace_pc(vaddr_t pc, word_t inst, int rs1, int rs2, int rd) {
  printf("PC: %x, Inst: %x, RS1: %d, RS2: %d, RD: %d\n", pc, inst, rs1, rs2, rd);
  fprintf(fp, "%x\n", pc);
}
void init_pc_trace() { fp = fopen("pc_trace", "w"); }
void close_pc_trace() {
  fclose(fp);
}