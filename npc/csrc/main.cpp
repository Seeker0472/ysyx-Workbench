
#include <Vcore.h>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
static VerilatedVcdC *tfp; // 用于生成波形的指针

#include "svdpi.h"
#include "Vcore__Dpi.h"

Vcore *dut;
unsigned int sim_time = 0;
static int wave_enable = true;

int instructions[100] = {
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
};

int add(int a, int b) { return a+b; }

int mem_read(int pc){
  return instructions[(pc-0x80000000)/4];
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
}

void reset(int n)
{
  dut->reset = 1;
  while (n-- > 0)
    single_cycle();
  dut->reset = 0;
}

int main(int argc, char **argv)
{

  dut = new Vcore; // Initialize the DUT instance
  Verilated::commandArgs(argc, argv);
  Verilated::traceEverOn(true); // 启用波形追踪
  tfp = new VerilatedVcdC;
  dut->trace(tfp, 99); // 跟踪99级信号
  if (wave_enable)
    tfp->open("./build/waveform.vcd"); // 打开VCD文件
  else
    tfp->open("/dev/null"); // 不开启追踪，放弃记录
  reset(10);                // 复位10个周期
  while (1)
  {
    single_cycle();
    // sleep(1);
    printf("%x\n", dut->io_pc);
    dut->io_instr=mem_read(dut->io_pc);
    if(dut->io_pc==0x80000060){
  tfp->close(); // 关闭VCD文件

      return 0;}
    // std::cout<<"1"<<dut->clk<<dut->led<<std::endl;
  }
  tfp->close(); // 关闭VCD文件
  delete tfp;
  return 0;
}
