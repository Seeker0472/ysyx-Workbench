# define NVBOARD
// #ifdef NVBOARD
#include <nvboard.h>
// #endif
#include <Vkeyboard.h>
#include<iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
static TOP_NAME dut;
static VerilatedVcdC* tfp; // 用于生成波形的指针
// #ifdef NVBOARD
void nvboard_bind_all_pins(TOP_NAME *dut);
// #endif
unsigned int sim_time=0;
static int wave_enable=true;

void single_cycle(){
  dut.clk = 0;
  dut.eval();
  if(wave_enable)
    tfp->dump(sim_time++); // Dump波形信息
  dut.clk = 1;
  dut.eval();
  if(wave_enable)
    tfp->dump(sim_time++); // Dump波形信息
}

void reset(int n){
  // dut.rst = 1;
  // while (n-- > 0)
  //   single_cycle();
  // dut.rst = 0;
}

int main(int argc, char** argv){
#ifdef NVBOARD
  nvboard_bind_all_pins(&dut);
  nvboard_init();
#endif

  Verilated::commandArgs(argc, argv); 
  Verilated::traceEverOn(true); // 启用波形追踪
  tfp = new VerilatedVcdC;
  dut.trace(tfp, 99); // 跟踪99级信号
  if(wave_enable)
    tfp->open("./build/waveform.vcd"); // 打开VCD文件
  else
    tfp->open("/dev/null");//不开启追踪，放弃记录
  reset(10); // 复位10个周期
  while (1){
    single_cycle();
    #ifdef NVBOARD
    nvboard_update();
    #endif
    // std::cout<<"1"<<dut.clk<<dut.led<<std::endl;
  }
  tfp->close(); // 关闭VCD文件
  delete tfp;
  return 0;
}
