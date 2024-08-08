#include "../include/ydb_all.h"
#include "VysyxSoCFull.h"
#include "VysyxSoCFull___024root.h"
#include <diftest.h>
#include <iostream>
#include <nvboard.h>
#include <verilated.h>
#include <verilated_vcd_c.h>

VerilatedVcdC *tfp; // 用于生成波形的指针
VysyxSoCFull *dut;
void nvboard_bind_all_pins(VysyxSoCFull *dut);

uint64_t sim_time = 0;
uint64_t g_nr_guest_inst = 0;
uint64_t g_timer = 0; // unit: us
void print_iringbuf();

void trace_and_difftest(paddr_t pc, word_t inst_in);
int update_reg_state();
void print_inst_asm(paddr_t pc, word_t inst);
void statistic();

void init_verilator(int argc, char *argv[]) {
  Verilated::commandArgs(argc, argv);
}

uint32_t mem_read(uint32_t pc);
bool check_watch_point();
extern "C" void disassemble(char *str, int size, uint64_t pc, uint8_t *code,
                            int nbyte);

#define PRINT_INST_MIN 10

void statistic() {
#define NUMBERIC_FMT MUXDEF(CONFIG_TARGET_AM, "%", "%'") PRIu64
  Log("host time spent = " NUMBERIC_FMT " us", g_timer);
  Log("total guest instructions = " NUMBERIC_FMT, g_nr_guest_inst);
  if (g_timer > 0)
    Log("simulation frequency = " NUMBERIC_FMT " inst/s",
        g_nr_guest_inst * 1000000 / g_timer);
  else
    Log("Finish running in less than 1 us and can not calculate the simulation "
        "frequency");
}

void single_cycle(bool check_pc) {
  uint32_t prev_pc =
      dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__ifu__DOT__pc;
  uint32_t now_pc =
      dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__ifu__DOT__pc;
  int i = 0;
  do {
    i++;
    dut->clock = 0;
    dut->eval();
    IFDEF(CONFIG_WAVE_FORM, tfp->dump(sim_time++);) // Dump波形信息
    dut->clock = 1;
    dut->eval();
    IFDEF(CONFIG_WAVE_FORM, tfp->dump(sim_time++);) // Dump波形信息
    now_pc =
        dut->rootp
            ->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__ifu__DOT__pc;
    if (i % 1000 == 0) {
      nemu_state.state= NEMU_STOP;
      Info_R("WARN: PC didn't change for 1000 Cycles!\n");
      nemu_state.halt_ret = -1;
      break;
    }
    nvboard_update();
  } while (prev_pc == now_pc && check_pc);
  update_reg_state();

#ifdef CONFIG_WATCHPOINT
  if (check_watch_point() && nemu_state.state == NEMU_RUNNING)
    nemu_state.state = NEMU_STOP;
#endif

  // printf("%x\n", dut->io_instr);
}

void reset(int n) {
  dut->reset = 1;
  dut->clock = 0;
  dut->eval();
  dut->clock = 1;
  dut->eval();
  while (n-- > 0)
    single_cycle(false);
  dut->reset = 0;
}

void init_runtime() {
  dut = new VysyxSoCFull;       // Initialize the DUT instance
  Verilated::traceEverOn(true); // 启用波形追踪
  tfp = new VerilatedVcdC;
  dut->trace(tfp, 99); // 跟踪99级信号
  MUXDEF(CONFIG_WAVE_FORM, tfp->open("./build/waveform.vcd");
         , tfp->open("/dev/null");) // 打开VCD文件
  nvboard_bind_all_pins(dut);
  nvboard_init();
  reset(20);                        // 复位5个周期

}

int run(int step) {
  int now = step;
  uint64_t timer_start = get_time();
  while ((now) != 0) {
    now = now >= 0 ? now - 1 : now;
    switch (nemu_state.state) {
    case NEMU_ABORT:
    case NEMU_END:
      printf("Program execution has ended. To restart the program, exit NEMU "
             "and run again.\n");
      return -1;
    default:
      nemu_state.state = NEMU_RUNNING;
    }
    uint32_t pc =
        dut->rootp
            ->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__ifu__DOT__pc;
    single_cycle(true);
    tfp->flush();
    g_nr_guest_inst++;
    word_t inst =
        dut->rootp
            ->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__ifu__DOT__inst;
    if (step < PRINT_INST_MIN && step >= 0)
      print_inst_asm(pc, inst);
    // // TODO::在某一些条件下打印指令！！！！
    trace_and_difftest(pc, inst);

    if (nemu_state.state != NEMU_RUNNING)
      break; // 出现异常
  }
  uint64_t timer_end = get_time();
  g_timer += timer_end - timer_start;
  return 0;
}

void assert_fail_msg() {
  isa_reg_display();
  IFDEF(CONFIG_ITRACE, print_iringbuf());
  statistic();
}
