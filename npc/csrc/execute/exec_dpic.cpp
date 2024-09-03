#include "../include/diftest.h"
#include "../include/ydb_all.h"
#include "VysyxSoCFull.h"
#include "VysyxSoCFull__Dpi.h"
#include "VysyxSoCFull___024root.h"
#include "svdpi.h"
#include <cstdint>
#include <cstdio>
#include <verilated.h>
#include <verilated_vcd_c.h>

extern VerilatedVcdC *tfp;

extern VysyxSoCFull *dut;
extern bool difftest_step;
extern "C" void print_char(char w_char) {
  printf("%c", w_char);
  fflush(stdout);
}
void record_axi_write(const char *type, paddr_t addr, char wmask, word_t data);
void record_axi_read(const char *type, paddr_t addr, int len);

// 使用DPI-C机制实现ebreak
extern "C" void call_ebreak() {
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

#define MROM_BASE 0x20000000
#define MROM_TOP 0x20000fff
#define SRAM_BASE 0x0f000000
#define SRAM_TOP 0x0fffffff
#define FLASH_BASE 0x30000000
#define FLASH_TOP 0x3fffffff
#define SDRAM_BASE 0xa0000000
#define SDRAM_TOP 0xbfffffff
#define PSRAM_BASE 0x80000000
#define PSRAM_TOP 0x9fffffff
#define MEM_IN(addr, start, end) ((addr >= (start)) && (addr <= (end)))

// TODO:加入更多设备的地址检测，同时用宏定义减少Copy_Paste Code
extern "C" void check_addr(uint32_t addr, svBit access_type, uint32_t wmask,
                           uint32_t wdata, uint32_t len) {

  if (MEM_IN(addr, MROM_BASE, MROM_TOP)) { // mrom
    if (access_type) {
      record_axi_read("MROM", addr, len);
    } else {
      record_axi_write("MROM", addr, wmask, wdata);
    }
    return;
  }
  if (MEM_IN(addr, SRAM_BASE, SRAM_TOP)) { // sram
    if (access_type) {
      record_axi_read("SRAM", addr, len);
    } else {
      record_axi_write("SRAM", addr, wmask, wdata);
    }
    return;
  }
  if (MEM_IN(addr, FLASH_BASE, FLASH_TOP)) { // flash
    if (access_type) {
      record_axi_read("FLASH", addr, len);
    } else {
      record_axi_write("FLASH", addr, wmask, wdata);
    }
    return;
  }
  if (MEM_IN(addr, SDRAM_BASE, SDRAM_TOP)) { // sdram
    if (access_type) {
      record_axi_read("SDRAM", addr, len);
    } else {
      record_axi_write("SDRAM", addr, wmask, wdata);
    }
    return;
  }
  if (MEM_IN(addr, PSRAM_BASE, PSRAM_TOP)) { // psram
    if (access_type) {
      record_axi_read("PSRAM", addr, len);
    } else {
      record_axi_write("PSRAM", addr, wmask, wdata);
    }
    return;
  }
  if (access_type) {
    record_axi_read("Other", addr, len);
  } else {
    //TODO:Mask not correct?
    record_axi_write("Other", addr, wmask, wdata);
  }
  difftest_step = true;
  // printf("STEP\n");
  // sleep(1);
}