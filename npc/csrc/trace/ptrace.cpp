#include "../include/ydb_all.h"
#include "svdpi.h"
#include <cstdint>
#include <stdio.h>

#define OK(ITEM) (ITEM ? "True" : "False")

extern "C" void trace_decoder(svBit mem_R, svBit mem_W, svBit calc, svBit csr);
extern "C" void trace_exu();
extern "C" void trace_ifu(int unsigned addr, svBit start_end);
extern "C" void trace_lsu(int unsigned addr, svBit RW, svBit start_end);
extern uint64_t g_cycles;
extern uint64_t g_nr_guest_inst;
// count!!

// count inst Type
typedef struct {
  uint64_t calc;
  uint64_t memr;
  uint64_t memw;
  uint64_t csr;
} instType;
enum { INS_CALC, INS_MR, INS_MW, INS_CSR, INS_O };
instType instTypeCount = {0, 0, 0, 0};
instType instCycles = {0, 0, 0, 0};

typedef struct {
  uint64_t lsur;
  uint64_t lsuw;
  uint64_t ifu;
} latency;
latency memLatency = {0, 0, 0};

uint64_t last_inst = INS_O;
//记录当前指令类型和指令总数
extern "C" void trace_decoder(svBit mem_R, svBit mem_W, svBit calc, svBit csr) {
  // Log("Decoded_result:
  // MEMR:%s,MEMW:%s,calc:%s,csr:%s\n",OK(mem_R),OK(mem_W),OK(calc),OK(csr));
  if (mem_R) {
    instTypeCount.memr++;
    last_inst = INS_MR;
  } else if (mem_W) {
    instTypeCount.memw++;
    last_inst = INS_MW;
  } else if (calc) {
    instTypeCount.calc++;
    last_inst = INS_CALC;
  } else if (csr) {
    instTypeCount.csr++;
    last_inst = INS_CSR;
  } else
    last_inst = INS_O;
}
extern "C" void trace_exu() {
  // Log("Trace_EXU\n");
  // exu_complete++;
}

uint64_t last_cycle = 0;
extern "C" void trace_ifu(int unsigned addr, svBit start_end) {
  // Log("IFU:addr = %x,start=%s",addr,OK(start_end));
  if (start_end) {
    //ifu-start上一条指令结束--TODO:多周期失效？？
    if (last_cycle != 0)
      switch (last_inst) {
      case INS_MR:
        instCycles.memr += g_cycles - last_cycle;
        break;
      case INS_MW:
        instCycles.memw += g_cycles - last_cycle;
        break;
      case INS_CALC:
        instCycles.calc += g_cycles - last_cycle;
        break;
      case INS_CSR:
        instCycles.csr += g_cycles - last_cycle;
        break;
      }
    last_cycle = g_cycles;
  } else {
    // ifu_end 取到了指令
    memLatency.ifu+=g_cycles-last_cycle;
  }
}

uint64_t lsu_start = 0;
//维护memLatency
extern "C" void trace_lsu(int unsigned addr, svBit RW, svBit start_end) {
  // Log("LSU:addr = %x,start=%s,Read=%s",addr,OK(start_end),OK(RW));
  if (start_end) {
    lsu_start = g_cycles;
  } else if (RW) {
    memLatency.lsur+=g_cycles-lsu_start;
  } else {
    memLatency.lsuw+=g_cycles-lsu_start;
  }
}

void print_perf_statistics() {
  printf("YPC's performance statistics as follows:===============\n");
  printf("Instructions:%ld  IFU Latency=%ld\n", g_nr_guest_inst,
         memLatency.ifu / g_nr_guest_inst);
  printf("Calc: %ld  Cycles: %ld\n", instTypeCount.calc,
         instCycles.calc / instTypeCount.calc);
  printf("MEMr: %ld  Cycles: %ld\n", instTypeCount.memr,
         instCycles.memr/instTypeCount.memr);
  printf("MEMw: %ld  Cycles: %ld\n", instTypeCount.memw,
         instCycles.memr / instTypeCount.memr);
  printf("CSR: %ld Cycles:%ld\n\n", instTypeCount.csr,
         instCycles.csr / instTypeCount.csr);

  printf("LSUr: %ld LSUw: %ld IFU: %ld\n", memLatency.lsur / instTypeCount.memr,
         memLatency.lsuw / instTypeCount.memw,
         memLatency.ifu / g_nr_guest_inst);
  //   printf("")
}