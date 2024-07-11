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
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(clock,0,0);
        VL_IN8(reset,0,0);
        CData/*3:0*/ core__DOT___decoder_io_out_alu_op_type;
        CData/*0:0*/ core__DOT___decoder_io_out_pc_jump;
        CData/*0:0*/ core__DOT___decoder_io_out_mem_read_enable;
        CData/*2:0*/ core__DOT___decoder_io_out_mem_read_type;
        CData/*1:0*/ core__DOT___decoder_io_out_mem_write_type;
        CData/*2:0*/ core__DOT___decoder_io_out_branch_type;
        CData/*7:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T;
        CData/*7:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1;
        CData/*7:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_2;
        CData/*7:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_3;
        CData/*5:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_7;
        CData/*6:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_8;
        CData/*7:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_10;
        CData/*7:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16;
        CData/*6:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_19;
        CData/*7:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_28;
        CData/*7:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_40;
        CData/*0:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_33;
        CData/*0:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_34;
        CData/*0:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_35;
        CData/*0:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_36;
        CData/*0:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_40;
        CData/*0:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_41;
        CData/*0:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_44;
        CData/*0:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_45;
        CData/*0:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_47;
        CData/*0:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_48;
        CData/*0:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_58;
        CData/*0:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_60;
        CData/*0:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_61;
        CData/*2:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_62;
        CData/*1:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_63;
        CData/*5:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_64;
        CData/*6:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_65;
        CData/*7:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_66;
        CData/*6:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_67;
        CData/*2:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_68;
        CData/*3:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_70;
        CData/*1:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_71;
        CData/*7:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_72;
        CData/*1:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_74;
        CData/*0:0*/ core__DOT__reg_0__DOT___GEN;
        CData/*0:0*/ core__DOT__exu__DOT__comp__DOT___io_result_T_18;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VicoFirstIteration;
        CData/*0:0*/ __Vtrigprevexpr___TOP__clock__0;
        CData/*0:0*/ __VactContinue;
        SData/*8:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_9;
        SData/*15:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_12;
        SData/*15:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_15;
        SData/*8:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17;
        SData/*9:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_18;
        SData/*8:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_20;
        SData/*14:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_21;
        SData/*15:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_22;
        SData/*15:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_23;
        SData/*8:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_24;
        SData/*8:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_34;
        SData/*15:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_38;
        SData/*9:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_44;
        SData/*14:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_45;
        SData/*15:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_46;
    };
    struct {
        SData/*8:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_49;
        SData/*8:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_51;
        SData/*15:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_52;
        SData/*9:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_54;
        SData/*14:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_57;
        SData/*9:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_69;
        SData/*9:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_73;
        SData/*15:0*/ core__DOT__exu__DOT___mem_read_result_sint_T_19;
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
        IData/*31:0*/ core__DOT__reg_0__DOT__casez_tmp_0;
        IData/*31:0*/ core__DOT__ifu__DOT__pc;
        IData/*31:0*/ core__DOT__exu__DOT___mem_read_data;
        IData/*31:0*/ core__DOT__exu__DOT____Vcellinp__alu__io_in_src2;
        IData/*31:0*/ core__DOT__exu__DOT____Vcellinp__alu__io_in_src1;
        IData/*31:0*/ core__DOT__exu__DOT__alu__DOT__casez_tmp;
        IData/*31:0*/ __Vfunc_pmem_read__1__Vfuncout;
        IData/*31:0*/ __VactIterCount;
        VlUnpacked<CData/*0:0*/, 3> __Vm_traceActivity;
    };
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
