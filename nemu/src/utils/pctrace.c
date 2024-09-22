#include "stdio.h"
#include "stdint.h"
#include <stdio.h>
FILE *fp;
void trace_pc(uint32_t pc) { fprintf(fp, "%x\n", pc); }
void init_pc_trace() { fp = fopen("pc_trace", "w"); }
void close_pc_trace() {
  fclose(fp);
}