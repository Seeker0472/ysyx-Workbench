#include <nvboard.h>
#include <Vexample.h>
#include<iostream>

static TOP_NAME dut;

void nvboard_bind_all_pins(TOP_NAME *dut);

void single_cycle(){
  dut.clk = 0;
  dut.eval();
  dut.clk = 1;
  dut.eval();
}

void reset(int n){
  dut.rst = 1;
  while (n-- > 0)
    single_cycle();
  dut.rst = 0;
}

int main(){
  std::cout<<"start";
  nvboard_bind_all_pins(&dut);
  std::cout<<"start";

  nvboard_init();
  reset(10); // 复位10个周期
  std::cout<<"start";

  while (1)
  {
    dut.eval();
    single_cycle();
    std::cout<<dut.clk;
  }
}
