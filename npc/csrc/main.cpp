
#include <Vcore.h>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
// #include <bits/getopt_ext.h>
#include <getopt.h>
static VerilatedVcdC *tfp; // 用于生成波形的指针

#include "svdpi.h"
#include "Vcore__Dpi.h"

Vcore *dut;
unsigned int sim_time = 0;
static int wave_enable = true;

//使用DPI-C机制实现ebreak
void call_ebreak(){
  printf("Ebreak Called!!");
  exit(0);
}
static char *img_file = NULL;
static char *elf_file = NULL;

static int parse_args(int argc, char *argv[]) {
  const struct option table[] = {
    // {"batch"    , no_argument      , NULL, 'b'},
    // {"log"      , required_argument, NULL, 'l'},
    // {"diff"     , required_argument, NULL, 'd'},
    // {"port"     , required_argument, NULL, 'p'},
    // {"help"     , no_argument      , NULL, 'h'},
    {"elf-file" , required_argument, NULL, 'e'},
    {0          , 0                , 0,  0 },
  };
  int o;
  while ( (o = getopt_long(argc, argv, "-e:", table, NULL)) != -1) {
    switch (o) {
      // case 'b': sdb_set_batch_mode(); break;
      // case 'p': sscanf(optarg, "%d", &difftest_port); break;
      // case 'l': log_file = optarg; break;
      // case 'd': diff_so_file = optarg; break;
      
      case 'e': elf_file = optarg; break;
      case 1: img_file = optarg; printf("%s",img_file);return 0;
      default:
        printf("Usage: %s [OPTION...] IMAGE [args]\n\n", argv[0]);
        // printf("\t-b,--batch              run with batch mode\n");
        // printf("\t-l,--log=FILE           output log to FILE\n");
        // printf("\t-d,--diff=REF_SO        run DiffTest with reference REF_SO\n");
        // printf("\t-p,--port=PORT          run DiffTest with port PORT\n");
        // printf("\t-e,--elf-file=FILE      input Elf File\n");
        printf("\n");
        exit(0);
    }
  }
  return 0;
}

int default_insts[100] = {
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
    0x00100073,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
    0x00448493,
};

int mem_read(int pc){
  return default_insts[(pc-0x80000000)/4];
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
  parse_args(argc,argv);
  dut = new Vcore; // Initialize the DUT instance
  // Verilated::commandArgs(argc, argv);
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
    // printf("%x\n", dut->io_pc);
    dut->io_instr=mem_read(dut->io_pc);
  //   if(dut->io_pc==0x80000060){
  // tfp->close(); // 关闭VCD文件

  //     return 0;}
    // std::cout<<"1"<<dut->clk<<dut->led<<std::endl;
  }
  tfp->close(); // 关闭VCD文件
  delete tfp;
  return 0;
}
