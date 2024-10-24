#include "stdio.h"
#include "stdint.h"
#include <stdio.h>
#include "common.h"
FILE *fp;
#define WRITE
#define FORWARD_CALC
int last_write = 0;
int forward_calc = 0;
void trace_pc(vaddr_t pc, word_t inst, int rs1, int rs2, int rd,int type) {
  // printf("PC: %x, Inst: %x, RS1: %d, RS2: %d, RD: %d\n", pc, inst, rs1, rs2, rd);
#ifdef FORWARD_CALC
  if (rs1 != 0 && rs1 == last_write) {
    forward_calc++;
  }else if (rs2 != 0 && rs2 == last_write) {
    forward_calc++;
  }
  last_write = rd;
#endif
  IFDEF(WRITE,fprintf(fp, "%x\n", pc);)
}
void init_pc_trace() { fp = fopen("pc_trace", "w"); }
void close_pc_trace() {
  printf("forward_times:%d",forward_calc);
  fclose(fp);
}