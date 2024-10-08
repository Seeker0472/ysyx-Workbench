// #define NPC
#include "../include/regs.h"

#include "../include/diftest.h"
#include "../include/ydb_all.h"

#ifndef NPC
#include "VysyxSoCFull.h"
#include "VysyxSoCFull__Dpi.h"
#include "VysyxSoCFull___024root.h"
extern VysyxSoCFull *dut;
#else
#include "Vraw_core.h"
#include "Vraw_core__Dpi.h"
#include "Vraw_core___024root.h"
extern Vraw_core *dut;
#endif
#include "svdpi.h"
#include <stdint.h>
#include <verilated.h>
#include <verilated_vcd_c.h>

extern CPU_state *cpu;
bool difftest_step = false;
void ftrace_check_inst(paddr_t pc_now, word_t inst);
void difftest_check_state();
void difftest_copy_regs();
void write_iringbuf(paddr_t pc, word_t inst);

extern "C" void disassemble(char *str, int size, uint64_t pc, uint8_t *code,
                            int nbyte);

void print_inst_asm(paddr_t pc, word_t inst) {
  char buf[100];
  char *pbuf = buf;
  pbuf += snprintf(buf, 14, "0x%08x : ", pc);
  disassemble(pbuf, pbuf - buf + sizeof(buf), pc, (uint8_t *)(&inst),
              8); // 反编译？
  printf("%s\n", buf); // TODO++++++++++++++++++++++++++++++++++++++++++++++++++++++====
}
int prev_state = 0;
static bool state_valid() //检测从状态valid->fetching
{
  bool ret = false;
  if (prev_state == 3 && IFU_STATE == 1)
    ret = true;
  prev_state = IFU_STATE;
  return ret;
  // if(dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__ifu__DOT__state==2)
  //     return true;
}

int update_reg_state() {
  cpu->pc = PC_STRUCT;
  cpu->gpr[0] = REG_0_STRUCT;
  cpu->gpr[1] = REG_1_STRUCT;
  cpu->gpr[2] = REG_2_STRUCT;
  cpu->gpr[3] = REG_3_STRUCT;
  cpu->gpr[4] = REG_4_STRUCT;
  cpu->gpr[5] = REG_5_STRUCT;
  cpu->gpr[6] = REG_6_STRUCT;
  cpu->gpr[7] = REG_7_STRUCT;
  cpu->gpr[8] = REG_8_STRUCT;
  cpu->gpr[9] = REG_9_STRUCT;
  cpu->gpr[10] = REG_10_STRUCT;
  cpu->gpr[11] = REG_11_STRUCT;
  cpu->gpr[12] = REG_12_STRUCT;
  cpu->gpr[13] = REG_13_STRUCT;
  cpu->gpr[14] = REG_14_STRUCT;
  cpu->gpr[15] = REG_15_STRUCT;
#ifndef CONFIG_RVE
  cpu->gpr[16] =
      dut->rootp
          ->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_16;
  cpu->gpr[17] =
      dut->rootp
          ->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_17;
  cpu->gpr[18] =
      dut->rootp
          ->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_18;
  cpu->gpr[19] =
      dut->rootp
          ->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_19;
  cpu->gpr[20] =
      dut->rootp
          ->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_20;
  cpu->gpr[21] =
      dut->rootp
          ->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_21;
  cpu->gpr[22] =
      dut->rootp
          ->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_22;
  cpu->gpr[23] =
      dut->rootp
          ->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_23;
  cpu->gpr[24] =
      dut->rootp
          ->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_24;
  cpu->gpr[25] =
      dut->rootp
          ->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_25;
  cpu->gpr[26] =
      dut->rootp
          ->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_26;
  cpu->gpr[27] =
      dut->rootp
          ->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_27;
  cpu->gpr[28] =
      dut->rootp
          ->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_28;
  cpu->gpr[29] =
      dut->rootp
          ->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_29;
  cpu->gpr[30] =
      dut->rootp
          ->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_30;
  cpu->gpr[31] =
      dut->rootp
          ->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_31;
#endif
  return 0;
}

void trace_and_difftest(paddr_t pc, word_t inst_in) {
  //   if (!state_valid())
  //     return;
  // print_inst_asm(pc, inst_in);

#ifdef CONFIG_ITRACE
  char buf[200];
  char *p = buf;
  p += snprintf(p, sizeof(buf), FMT_WORD ":", pc); // 打印地址
  // printf("0x%08x"
  //        ":",
  //        pc);
  int ilen = 4;
  int i;
  uint8_t *inst = (uint8_t *)&inst_in;
  for (i = ilen - 1; i >= 0; i--) {
    p += snprintf(p, 4, " %02x", inst[i]);
  }
  int ilen_max = 4;
  int space_len = ilen_max - ilen;
  if (space_len < 0)
    space_len = 0;
  space_len = space_len * 3 + 1;
  memset(p, ' ', space_len);
  p += space_len;
  disassemble(p, buf + sizeof(buf) - p, pc, (uint8_t *)&inst_in, ilen);
#ifdef CONFIG_ITRACE_COND // 在condition为true的时候记录！
  if (CONFIG_ITRACE_COND) {
    log_write("%s\n", buf);
  } // 把缓冲区数据打印出来
#endif
#endif
#ifdef CONFIG_IRINGBUF
  write_iringbuf(pc, inst_in);
#endif
#ifdef CONFIG_FTRACE
  // ftrace--------------------
  ftrace_check_inst(pc, inst_in);
#endif
#ifdef CONFIG_DIFFTEST
  if (unlikely(difftest_step)) {
    difftest_copy_regs();
    difftest_step = false;
  } else {
    difftest_exec(1);
    difftest_check_state();
  }
#endif
}
