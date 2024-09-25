// #define NPC

#ifdef NPC
#define PC_STRUCT dut->rootp->raw_core__DOT__ypc__DOT__ifu__DOT__pc
#define REG_0_STRUCT 0
#define REG_1_STRUCT dut->rootp->raw_core__DOT__ypc__DOT__reg_0__DOT__regs_0
#define REG_2_STRUCT dut->rootp->raw_core__DOT__ypc__DOT__reg_0__DOT__regs_1
#define REG_3_STRUCT dut->rootp->raw_core__DOT__ypc__DOT__reg_0__DOT__regs_2
#define REG_4_STRUCT dut->rootp->raw_core__DOT__ypc__DOT__reg_0__DOT__regs_3
#define REG_5_STRUCT dut->rootp->raw_core__DOT__ypc__DOT__reg_0__DOT__regs_4
#define REG_6_STRUCT dut->rootp->raw_core__DOT__ypc__DOT__reg_0__DOT__regs_5
#define REG_7_STRUCT dut->rootp->raw_core__DOT__ypc__DOT__reg_0__DOT__regs_6
#define REG_8_STRUCT dut->rootp->raw_core__DOT__ypc__DOT__reg_0__DOT__regs_7
#define REG_9_STRUCT dut->rootp->raw_core__DOT__ypc__DOT__reg_0__DOT__regs_8
#define REG_10_STRUCT dut->rootp->raw_core__DOT__ypc__DOT__reg_0__DOT__regs_9
#define REG_11_STRUCT dut->rootp->raw_core__DOT__ypc__DOT__reg_0__DOT__regs_10
#define REG_12_STRUCT dut->rootp->raw_core__DOT__ypc__DOT__reg_0__DOT__regs_11
#define REG_13_STRUCT dut->rootp->raw_core__DOT__ypc__DOT__reg_0__DOT__regs_12
#define REG_14_STRUCT dut->rootp->raw_core__DOT__ypc__DOT__reg_0__DOT__regs_13
#define REG_15_STRUCT dut->rootp->raw_core__DOT__ypc__DOT__reg_0__DOT__regs_14
#define IFU_STATE dut->rootp->raw_core__DOT__ypc__DOT__ifu__DOT__state

#else
#define PC_STRUCT                                                              \
  dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__ifu__DOT__pc
#define REG_0_STRUCT 0
#define REG_1_STRUCT dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_0
#define REG_2_STRUCT dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_1
#define REG_3_STRUCT dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_2
#define REG_4_STRUCT dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_3
#define REG_5_STRUCT dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_4
#define REG_6_STRUCT dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_5
#define REG_7_STRUCT dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_6
#define REG_8_STRUCT dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_7
#define REG_9_STRUCT dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_8
#define REG_10_STRUCT dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_9
#define REG_11_STRUCT dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_10
#define REG_12_STRUCT dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_11
#define REG_13_STRUCT dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_12
#define REG_14_STRUCT dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_13
#define REG_15_STRUCT dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__reg_0__DOT__regs_14
#define IFU_STATE                                                              \
  dut->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__ifu__DOT__state

#endif