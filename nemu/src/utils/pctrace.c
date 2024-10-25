#include "stdio.h"
#include "stdint.h"
#include <stdio.h>
#include "common.h"
FILE *fp;
// #define WRITE
// #define FORWARD_CALC

//TODO:calc the times of each instr ,and the acc of the arg
int last_write = 0;
int forward_calc = 0;
struct {
  uint64_t jal_f;
  uint64_t jal;
  uint64_t jalr_f;
  uint64_t jalr;
} inst_count;
void printInstCount() {
  printf("jal_f: %lu\n", inst_count.jal_f);
  printf("jal: %lu\n", inst_count.jal);
  printf("jalr_f: %lu\n", inst_count.jalr_f);
  printf("jalr: %lu\n", inst_count.jalr);
}

void trace_pc(vaddr_t pc, word_t inst, int rs1, int rs2, int rd,int type,char* name) {
  // printf("PC: %x, Inst: %x, RS1: %d, RS2: %d, RD: %d\n", pc, inst, rs1, rs2, rd);
#ifdef FORWARD_CALC
  if (rs1 != 0 && rs1 == last_write) {
    forward_calc++;
  }else if (rs2 != 0 && rs2 == last_write) {
    forward_calc++;
  }
  last_write = rd;
#endif
  // printf("%s\n",name);
  if (strcmp(name, "jal_f"))
    inst_count.jal_f++;
  if (strcmp(name, "jal"))
    inst_count.jal++;
  if (strcmp(name, "jalr_f"))
    inst_count.jalr_f++;
  if (strcmp(name, "jalr"))
    inst_count.jalr++;
  IFDEF(WRITE, fprintf(fp, "%x\n", pc);)
}
void init_pc_trace() { fp = fopen("pc_trace", "w"); }
void close_pc_trace() {
  printInstCount();
  // printf("forward_times:%d",forward_calc);
  fclose(fp);
}