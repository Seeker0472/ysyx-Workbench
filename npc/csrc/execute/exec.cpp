#include "VysyxSoCFull.h"
#include "VysyxSoCFull___024root.h"
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <common.h>
#include <utils.h>
#include <diftest.h>

// #include <bits/getopt_ext.h>
static VerilatedVcdC *tfp; // 用于生成波形的指针
VysyxSoCFull *dut;

#include "svdpi.h"
#include "VysyxSoCFull__Dpi.h"
#include <isa.h>

//TODO:re
extern "C" void print_char(char w_char){
    printf("%c",w_char);
    fflush(stdout);
}
void init_verilator(int argc, char *argv[]){
    Verilated::commandArgs(argc, argv);

}

uint64_t g_nr_guest_inst = 0;

uint32_t mem_read(uint32_t pc);
extern CPU_state *cpu;
bool check_watch_point();
extern "C" void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
void ftrace_check_inst(paddr_t pc_now, word_t inst);
void difftest_check_state();
void print_inst_asm(paddr_t pc, word_t inst);

#define PRINT_INST_MIN 10

int prev_state = 0;
static bool state_valid()//检测从状态valid->fetching
{
    bool ret = false;
    if (prev_state == 3&&dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__ifu__DOT__state==1)
        ret = true;
    prev_state = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__ifu__DOT__state;
    return ret;
    // if(dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__ifu__DOT__state==2)
    //     return true;
    
}

static void trace_and_difftest(paddr_t pc, word_t inst_in)
{
    if (!state_valid())
        return;
            print_inst_asm(pc, inst_in);

#ifdef CONFIG_ITRACE
    char buf[200];
    char *p = buf;
    p += snprintf(p, sizeof(buf), FMT_WORD ":", pc); // 打印地址
    // printf("0x%08x"
    //        ":",
    //        pc);
    int ilen = 4;
    int i;
    uint8_t *inst = (uint8_t *)&inst_in;
    for (i = ilen - 1; i >= 0; i--)
    {
        p += snprintf(p, 4, " %02x", inst[i]);
    }
    int ilen_max = 4;
    int space_len = ilen_max - ilen;
    if (space_len < 0)
        space_len = 0;
    space_len = space_len * 3 + 1;
    memset(p, ' ', space_len);
    p += space_len;
    disassemble(p, buf + sizeof(buf) - p,
                pc, (uint8_t *)&inst_in, ilen);
#ifdef CONFIG_ITRACE_COND // 在condition为true的时候记录！
    if (CONFIG_ITRACE_COND)
    {
        // printf("BUF++%s\n",buf);
        log_write("%s\n", buf);
    } // 把缓冲区数据打印出来
#endif
#endif
#ifdef CONFIG_FTRACE
    // ftrace--------------------
    ftrace_check_inst(pc, inst_in);
#endif
#ifdef CONFIG_DIFFTEST
    difftest_exec(1);
    difftest_check_state();
#endif
}

void print_inst_asm(paddr_t pc, word_t inst)
{
    char buf[100];
    char *pbuf = buf;
    pbuf += snprintf(buf, 14, "0x%08x : ", pc);
    disassemble(pbuf, pbuf - buf + sizeof(buf), pc, (uint8_t *)(&inst), 8); // 反编译？
    printf("%s\n", buf);//TODO++++++++++++++++++++++++++++++++++++++++++++++++++++++====
}

unsigned int sim_time = 0;
// 使用DPI-C机制实现ebreak
void call_ebreak()
{
    if (nemu_state.state == NEMU_END) // Prevent_Display_Twice!!!!!------TODO:Why called Twice????
        return;
    Log("Ebreak Called!!");
    // tfp->
    uint32_t regs_2_value = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_10;
    uint32_t pc = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__ifu__DOT__pc;

    Log("YDB: %s at pc = " FMT_WORD,
        (
            (regs_2_value == 0 ? ANSI_FMT("HIT GOOD TRAP", ANSI_FG_GREEN) : ANSI_FMT("HIT BAD TRAP", ANSI_FG_RED))),
        pc);
    // printf("%x\n", regs_2_value);

    tfp->flush(); // not-关闭VCD文件
    // delete tfp;
    nemu_state.state = NEMU_END;
    nemu_state.halt_ret = regs_2_value;
    // exit(0);
}

void update_reg_state()
{
    cpu->pc = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__ifu__DOT__pc;
    cpu->gpr[0] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_0;
    cpu->gpr[1] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_1;
    cpu->gpr[2] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_2;
    cpu->gpr[3] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_3;
    cpu->gpr[4] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_4;
    cpu->gpr[5] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_5;
    cpu->gpr[6] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_6;
    cpu->gpr[7] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_7;
    cpu->gpr[8] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_8;
    cpu->gpr[9] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_9;
    cpu->gpr[10] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_10;
    cpu->gpr[11] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_11;
    cpu->gpr[12] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_12;
    cpu->gpr[13] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_13;
    cpu->gpr[14] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_14;
    cpu->gpr[15] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_15;
#ifndef CONFIG_RVE
    cpu->gpr[16] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_16;
    cpu->gpr[17] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_17;
    cpu->gpr[18] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_18;
    cpu->gpr[19] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_19;
    cpu->gpr[20] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_20;
    cpu->gpr[21] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_21;
    cpu->gpr[22] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_22;
    cpu->gpr[23] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_23;
    cpu->gpr[24] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_24;
    cpu->gpr[25] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_25;
    cpu->gpr[26] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_26;
    cpu->gpr[27] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_27;
    cpu->gpr[28] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_28;
    cpu->gpr[29] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_29;
    cpu->gpr[30] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_30;
    cpu->gpr[31] = dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_31;
#endif
}
void check_mem_fail(){
    assert(dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__ifu__DOT__state!=4);
}

void single_cycle()
{
    // dut->io_instr = mem_read(dut->io_pc); // 取指令
    dut->clock = 0;
    dut->eval();
    IFDEF(CONFIG_WAVE_FORM, tfp->dump(sim_time++);) // Dump波形信息

    dut->clock = 1;
    dut->eval();
    IFDEF(CONFIG_WAVE_FORM, tfp->dump(sim_time++);) // Dump波形信息
    // printf("%x\n",dut->io_pc);
    // dut->io_instr = mem_read(dut->io_pc); // 下一条指令
    update_reg_state();

#ifdef CONFIG_WATCHPOINT
    if (check_watch_point() && nemu_state.state == NEMU_RUNNING)
        nemu_state.state = NEMU_STOP;
#endif
check_mem_fail();
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
    reset(5);                                                                             // 复位5个周期
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

// 使用Assert宏的时候输出信息
void assert_fail_msg()
{
    isa_reg_display();
    // 打印iringbuf！TODO:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::;;
    // IFDEF(CONFIG_ITRACE, print_iringbuf());
    //   statistic(); TODO:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::;;
}
