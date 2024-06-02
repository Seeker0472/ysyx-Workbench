#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <verilated.h>
#include "../obj_dir/Vexample.h"
#include <verilated_vcd_c.h>

int main(int argc, char **argv, char **env){
    Verilated::commandArgs(argc, argv);
    Vexample* top = new Vexample;

    int rec_time=0;
    Verilated::traceEverOn(true);
    VerilatedVcdC *trace = new VerilatedVcdC;
    top->trace(trace, 1);
    trace->open("waveform.vcd");
    while (rec_time<1000) {
    int a = rand() & 1;
    int b = rand() & 1;
    top->a = a;
    top->b = b;
    top->eval();
    printf("a = %d, b = %d, f = %d\n", a, b, top->f);
    assert(top->f == (a ^ b));

    trace->dump(rec_time);
    // 全局时钟计时
    rec_time++;
  }
    trace->close();
    top->final();
    delete top;
    exit(0);
}