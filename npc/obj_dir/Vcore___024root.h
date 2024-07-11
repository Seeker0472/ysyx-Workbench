// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vcore.h for the primary calling header

#ifndef VERILATED_VCORE___024ROOT_H_
#define VERILATED_VCORE___024ROOT_H_  // guard

#include "verilated.h"
class Vcore___024unit;


class Vcore__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vcore___024root final : public VerilatedModule {
  public:
    // CELLS
    Vcore___024unit* __PVT____024unit;

    // DESIGN SPECIFIC STATE
    VL_IN8(clock,0,0);
    VL_IN8(reset,0,0);
    CData/*0:0*/ core__DOT___decoder_io_out_alu_use_Imm_2;
    CData/*0:0*/ core__DOT___decoder_io_out_pc_jump;
    CData/*0:0*/ core__DOT___decoder_io_out_reg_write_enable;
    CData/*7:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T;
    CData/*7:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1;
    CData/*7:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_3;
    CData/*5:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_6;
    CData/*6:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_7;
    CData/*7:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_13;
    CData/*6:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16;
    CData/*7:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_19;
    CData/*7:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_21;
    CData/*0:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_25;
    CData/*0:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_30;
    CData/*0:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_31;
    CData/*0:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_32;
    CData/*0:0*/ core__DOT__reg_0__DOT___GEN;
    CData/*1:0*/ __VdfgRegularize_hd87f99a1_0_0;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clock__0;
    CData/*0:0*/ __VactContinue;
    SData/*9:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_15;
    SData/*15:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_18;
    SData/*15:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_23;
    SData/*14:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_24;
    VL_OUT(io_pc,31,0);
    VL_OUT(io_value,31,0);
    VL_IN(io_addr,31,0);
    VL_IN(io_instr,31,0);
    VL_OUT(io_inst_now,31,0);
    IData/*31:0*/ core__DOT___exu_io_out_n_pc;
    IData/*31:0*/ core__DOT__decoder__DOT__casez_tmp;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_0;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_1;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_2;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_3;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_4;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_5;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_6;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_7;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_8;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_9;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_10;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_11;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_12;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_13;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_14;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_15;
    IData/*31:0*/ core__DOT__reg_0__DOT__casez_tmp;
    IData/*31:0*/ core__DOT__ifu__DOT__pc;
    IData/*31:0*/ core__DOT__exu__DOT___alu_io_result;
    IData/*31:0*/ core__DOT__exu__DOT____Vcellinp__alu__io_in_src2;
    IData/*31:0*/ core__DOT__exu__DOT____Vcellinp__alu__io_in_src1;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<CData/*0:0*/, 3> __Vm_traceActivity;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vcore__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vcore___024root(Vcore__Syms* symsp, const char* v__name);
    ~Vcore___024root();
    VL_UNCOPYABLE(Vcore___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
