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
#include <isa.h>

uint32_t mem_read(uint32_t pc);
extern CPU_state *cpu;
bool check_watch_point();

void print_inst_asm(paddr_t pc,word_t inst)
{
    char buf[100];
    void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
    disassemble(&buf, sizeof(buf), pc, (uint8_t *)inst, 4); // 反编译？
    printf("%s\n",buf);
}

Vcore *dut;
unsigned int sim_time = 0;
static int wave_enable = true;
// 使用DPI-C机制实现ebreak
void call_ebreak()
{
    if (nemu_state.state == NEMU_ABORT) // Prevent_Display_Twice!!!!!------TODO:Why called Twice????
        return;
    Log("Ebreak Called!!");
    // tfp->
    uint32_t regs_2_value = dut->rootp->core__DOT__reg_0__DOT__regs_10;
    uint32_t pc = dut->rootp->core__DOT__ifu__DOT__pc;

    Log("YDB: %s at pc = " FMT_WORD,
        (
            (regs_2_value == 0 ? ANSI_FMT("HIT GOOD TRAP", ANSI_FG_GREEN) : ANSI_FMT("HIT BAD TRAP", ANSI_FG_RED))),
        pc);
    // printf("%x\n", regs_2_value);

    tfp->flush(); // not-关闭VCD文件
    // delete tfp;
    nemu_state.state = NEMU_ABORT;
    // exit(0);
}

void update_reg_state()
{
    cpu->pc = dut->rootp->core__DOT__ifu__DOT__pc;
    cpu->gpr[0] = dut->rootp->core__DOT__reg_0__DOT__regs_0;
    cpu->gpr[1] = dut->rootp->core__DOT__reg_0__DOT__regs_1;
    cpu->gpr[2] = dut->rootp->core__DOT__reg_0__DOT__regs_2;
    cpu->gpr[3] = dut->rootp->core__DOT__reg_0__DOT__regs_3;
    cpu->gpr[4] = dut->rootp->core__DOT__reg_0__DOT__regs_4;
    cpu->gpr[5] = dut->rootp->core__DOT__reg_0__DOT__regs_5;
    cpu->gpr[6] = dut->rootp->core__DOT__reg_0__DOT__regs_6;
    cpu->gpr[7] = dut->rootp->core__DOT__reg_0__DOT__regs_7;
    cpu->gpr[8] = dut->rootp->core__DOT__reg_0__DOT__regs_8;
    cpu->gpr[9] = dut->rootp->core__DOT__reg_0__DOT__regs_9;
    cpu->gpr[10] = dut->rootp->core__DOT__reg_0__DOT__regs_10;
    cpu->gpr[11] = dut->rootp->core__DOT__reg_0__DOT__regs_11;
    cpu->gpr[12] = dut->rootp->core__DOT__reg_0__DOT__regs_12;
    cpu->gpr[13] = dut->rootp->core__DOT__reg_0__DOT__regs_13;
    cpu->gpr[14] = dut->rootp->core__DOT__reg_0__DOT__regs_14;
    cpu->gpr[15] = dut->rootp->core__DOT__reg_0__DOT__regs_15;
    cpu->gpr[16] = dut->rootp->core__DOT__reg_0__DOT__regs_16;
    cpu->gpr[17] = dut->rootp->core__DOT__reg_0__DOT__regs_17;
    cpu->gpr[18] = dut->rootp->core__DOT__reg_0__DOT__regs_18;
    cpu->gpr[19] = dut->rootp->core__DOT__reg_0__DOT__regs_19;
    cpu->gpr[20] = dut->rootp->core__DOT__reg_0__DOT__regs_20;
    cpu->gpr[21] = dut->rootp->core__DOT__reg_0__DOT__regs_21;
    cpu->gpr[22] = dut->rootp->core__DOT__reg_0__DOT__regs_22;
    cpu->gpr[23] = dut->rootp->core__DOT__reg_0__DOT__regs_23;
    cpu->gpr[24] = dut->rootp->core__DOT__reg_0__DOT__regs_24;
    cpu->gpr[25] = dut->rootp->core__DOT__reg_0__DOT__regs_25;
    cpu->gpr[26] = dut->rootp->core__DOT__reg_0__DOT__regs_26;
    cpu->gpr[27] = dut->rootp->core__DOT__reg_0__DOT__regs_27;
    cpu->gpr[28] = dut->rootp->core__DOT__reg_0__DOT__regs_28;
    cpu->gpr[29] = dut->rootp->core__DOT__reg_0__DOT__regs_29;
    cpu->gpr[30] = dut->rootp->core__DOT__reg_0__DOT__regs_30;
    cpu->gpr[31] = dut->rootp->core__DOT__reg_0__DOT__regs_31;
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
        tfp->dump(sim_time++);            // Dump波形信息
    dut->io_instr = mem_read(dut->io_pc); // 下一条指令
    update_reg_state();
    // TODO:＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊OPEN/CLOSE　ＷＰ
    if (check_watch_point() && nemu_state.state == NEMU_RUNNING)
        nemu_state.state = NEMU_STOP;

    //TODO::在某一些条件下打印指令！！！！
    uint32_t pc = dut->io_pc
    uint32_t addr = dut->io_inst_now
    print_inst_asm(pc,addr);


    // printf("%x\n", dut->io_instr);
}

void reset(int n)
{
    dut->reset = 1;
    while (n-- > 0)
        single_cycle();
    dut->reset = 0;
}
void init_runtime()
{
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

int run(int step)
{

    while ((step--) != 0)
    {
        switch (nemu_state.state)
        {
        case NEMU_ABORT:
        case NEMU_END:
            printf("Program execution has ended. To restart the program, exit NEMU and run again.\n");
            return -1;
        default:
            nemu_state.state = NEMU_RUNNING;
        }
        single_cycle();
        if (nemu_state.state != NEMU_RUNNING)
            break; // 出现异常
        tfp->flush();
    }
    return 0;
}

// 使用Assert宏的时候输出信息
void assert_fail_msg()
{
    isa_reg_display();
    // 打印iringbuf！
    IFDEF(CONFIG_ITRACE, print_iringbuf());
    //   statistic(); TODO:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::;;
}
