#include "Vcore.h"
#include "Vcore___024root.h"
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <debug.h>
// #include <bits/getopt_ext.h>
static VerilatedVcdC *tfp; // 用于生成波形的指针

#include "svdpi.h"
#include "Vcore__Dpi.h"

uint32_t mem_read(int pc);


Vcore *dut;
unsigned int sim_time = 0;
static int wave_enable = true;
// 使用DPI-C机制实现ebreak
void call_ebreak()
{
    Log("Ebreak Called!!");
    // tfp->
     uint32_t regs_2_value = dut->rootp->core__DOT__reg_0__DOT__regs_10;

     Log("nemu: %s at pc = " FMT_WORD,
          (
           (regs_2_value == 0 ? ANSI_FMT("HIT GOOD TRAP", ANSI_FG_GREEN) :
            ANSI_FMT("HIT BAD TRAP", ANSI_FG_RED))),
          nemu_state.halt_pc);
    printf("%x\n", regs_2_value);

    tfp->close(); // 关闭VCD文件
    delete tfp;
    exit(0);
}
void single_cycle()
{
    dut->clock = 0;
    dut->eval();
    if (wave_enable)
        tfp->dump(sim_time++); // Dump波形信息
    dut->clock = 1;
    dut->eval();
    if (wave_enable)
        tfp->dump(sim_time++); // Dump波形信息

    dut->io_instr = mem_read(dut->io_pc);//下一条指令
    // printf("%x\n", dut->io_instr);

}

void reset(int n)
{
    dut->reset = 1;
    while (n-- > 0)
        single_cycle();
    dut->reset = 0;
}
void init_runtime(){
    dut = new Vcore;              // Initialize the DUT instance
    Verilated::traceEverOn(true); // 启用波形追踪
    tfp = new VerilatedVcdC;
    dut->trace(tfp, 99); // 跟踪99级信号
    if (wave_enable)
        tfp->open("./build/waveform.vcd"); // 打开VCD文件
    else
        tfp->open("/dev/null"); // 不开启追踪，放弃记录
    reset(10);                  // 复位10个周期
}

int run()
{
    while (1)
    {
        single_cycle();
        tfp->flush();
    }
}
