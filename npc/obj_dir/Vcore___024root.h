// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vcore.h for the primary calling header

#ifndef VERILATED_VCORE___024ROOT_H_
#define VERILATED_VCORE___024ROOT_H_  // guard

#include "verilated.h"


class Vcore__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vcore___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clock,0,0);
    VL_IN8(reset,0,0);
    CData/*2:0*/ core__DOT__state;
    CData/*4:0*/ core__DOT__rs1;
    CData/*4:0*/ core__DOT__rd;
    CData/*0:0*/ core__DOT__addi;
    CData/*2:0*/ core__DOT__casez_tmp;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clock__0;
    CData/*0:0*/ __VactContinue;
    VL_OUT(io_pc,31,0);
    VL_OUT(io_value,31,0);
    VL_IN(io_addr,31,0);
    VL_IN(io_instr,31,0);
    IData/*31:0*/ core__DOT__pc;
    IData/*31:0*/ core__DOT__immI;
    IData/*31:0*/ core__DOT__src1;
    IData/*31:0*/ core__DOT__res;
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
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_16;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_17;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_18;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_19;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_20;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_21;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_22;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_23;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_24;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_25;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_26;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_27;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_28;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_29;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_30;
    IData/*31:0*/ core__DOT__reg_0__DOT__regs_31;
    IData/*31:0*/ core__DOT__reg_0__DOT__casez_tmp;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<CData/*0:0*/, 2> __Vm_traceActivity;
    VlTriggerVec<1> __VstlTriggered;
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
