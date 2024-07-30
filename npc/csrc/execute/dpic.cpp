#include <common.h>
#include <diftest.h>
#include <isa.h>
#include <stdio.h>
#include <utils.h>

#include "VysyxSoCFull.h"
#include "VysyxSoCFull__Dpi.h"
#include "VysyxSoCFull___024root.h"
#include <verilated.h>
#include <verilated_vcd_c.h>

extern VerilatedVcdC *tfp;

extern VysyxSoCFull *dut;

extern "C" void print_char(char w_char) {
  printf("%c", w_char);
  fflush(stdout);
}

// 使用DPI-C机制实现ebreak
void call_ebreak() {
  if (nemu_state.state ==
      NEMU_END) // Prevent_Display_Twice!!!!!------TODO:Why called Twice????
    return;
  Log("Ebreak Called!!");
  // tfp->
  uint32_t regs_2_value =
      dut->rootp
          ->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_10;
  uint32_t pc =
      dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__ifu__DOT__pc;

  Log("YDB: %s at pc = " FMT_WORD,
      ((regs_2_value == 0 ? ANSI_FMT("HIT GOOD TRAP", ANSI_FG_GREEN)
                          : ANSI_FMT("HIT BAD TRAP", ANSI_FG_RED))),
      pc);
  // printf("%x\n", regs_2_value);

  tfp->flush(); // not-关闭VCD文件
  // delete tfp;
  nemu_state.state = NEMU_END;
  nemu_state.halt_ret = regs_2_value;
  // exit(0);
}