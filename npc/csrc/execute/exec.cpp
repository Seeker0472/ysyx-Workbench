#include "VysyxSoCFull.h"
#include "VysyxSoCFull___024root.h"
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <common.h>
#include <utils.h>
#include <diftest.h>

VerilatedVcdC *tfp; // 用于生成波形的指针
VysyxSoCFull *dut;


#include <isa.h>

void trace_and_difftest(paddr_t pc, word_t inst_in);
void update_reg_state();



//TODO:re

void init_verilator(int argc, char *argv[]){
    Verilated::commandArgs(argc, argv);
}

uint64_t g_nr_guest_inst = 0;

uint32_t mem_read(uint32_t pc);
bool check_watch_point();
extern "C" void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
// void print_inst_asm(paddr_t pc, word_t inst);

#define PRINT_INST_MIN 10



void single_cycle()
{
    dut->clock = 0;
    dut->eval();
    IFDEF(CONFIG_WAVE_FORM, tfp->dump(sim_time++);) // Dump波形信息

    dut->clock = 1;
    dut->eval();
    IFDEF(CONFIG_WAVE_FORM, tfp->dump(sim_time++);) // Dump波形信息
    update_reg_state();

#ifdef CONFIG_WATCHPOINT
    if (check_watch_point() && nemu_state.state == NEMU_RUNNING)
        nemu_state.state = NEMU_STOP;
#endif

    // printf("%x\n", dut->io_instr);
}

void reset(int n)
{
    dut->reset = 1;
    dut->clock = 0;
    dut->eval();
    dut->clock = 1;
    dut->eval();
    while (n-- > 0)
        single_cycle();
    dut->reset = 0;
}
void init_runtime()
{
    dut = new VysyxSoCFull;              // Initialize the DUT instance
    Verilated::traceEverOn(true); // 启用波形追踪
    tfp = new VerilatedVcdC;
    dut->trace(tfp, 99);                                                                  // 跟踪99级信号
    MUXDEF(CONFIG_WAVE_FORM, tfp->open("./build/waveform.vcd");, tfp->open("/dev/null");) // 打开VCD文件
    reset(20);                                                                             // 复位5个周期
}

int run(int step)
{
    int now = step;

    while ((now) != 0)
    {
        now=now>=0?now-1:now;
        switch (nemu_state.state)
        {
        case NEMU_ABORT:
        case NEMU_END:
            printf("Program execution has ended. To restart the program, exit NEMU and run again.\n");
            return -1;
        default:
            nemu_state.state = NEMU_RUNNING;
        }
        uint32_t pc = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__ifu__DOT__pc;
        single_cycle();
        tfp->flush();
        g_nr_guest_inst++;
        //TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        word_t inst = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__ifu__DOT__inst;
        // if (step < PRINT_INST_MIN)
            // print_inst_asm(pc, inst);
        // // TODO::在某一些条件下打印指令！！！！
        trace_and_difftest(pc, inst);

        if (nemu_state.state != NEMU_RUNNING)
            break; // 出现异常
    }
    return 0;
}


void assert_fail_msg()
{
    isa_reg_display();
    // 打印iringbuf！TODO:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::;;
    // IFDEF(CONFIG_ITRACE, print_iringbuf());
    //   statistic(); TODO:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::;;
}
