// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcore.h for the primary calling header

#include "Vcore__pch.h"
#include "Vcore___024root.h"

VL_ATTR_COLD void Vcore___024root___eval_static(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___eval_static\n"); );
}

VL_ATTR_COLD void Vcore___024root___eval_initial(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vtrigprevexpr___TOP__clock__0 = vlSelf->clock;
}

VL_ATTR_COLD void Vcore___024root___eval_final(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___eval_final\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcore___024root___dump_triggers__stl(Vcore___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vcore___024root___eval_phase__stl(Vcore___024root* vlSelf);

VL_ATTR_COLD void Vcore___024root___eval_settle(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___eval_settle\n"); );
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelf->__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY((0x64U < __VstlIterCount))) {
#ifdef VL_DEBUG
            Vcore___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("build/core.sv", 343, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vcore___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelf->__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcore___024root___dump_triggers__stl(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ vlSelf->__VstlTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vcore___024root___stl_sequent__TOP__0(Vcore___024root* vlSelf);

VL_ATTR_COLD void Vcore___024root___eval_stl(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___eval_stl\n"); );
    // Body
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        Vcore___024root___stl_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[1U] = 1U;
        vlSelf->__Vm_traceActivity[0U] = 1U;
    }
}

VL_ATTR_COLD void Vcore___024root___stl_sequent__TOP__0(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___stl_sequent__TOP__0\n"); );
    // Body
    vlSelf->io_pc = vlSelf->core__DOT__pc;
    vlSelf->io_value = vlSelf->core__DOT__res;
    vlSelf->core__DOT__reg_0__DOT__casez_tmp = ((0x10U 
                                                 & (IData)(vlSelf->core__DOT__rs1))
                                                 ? 
                                                ((8U 
                                                  & (IData)(vlSelf->core__DOT__rs1))
                                                  ? 
                                                 ((4U 
                                                   & (IData)(vlSelf->core__DOT__rs1))
                                                   ? 
                                                  ((2U 
                                                    & (IData)(vlSelf->core__DOT__rs1))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelf->core__DOT__rs1))
                                                     ? vlSelf->core__DOT__reg_0__DOT__regs_31
                                                     : vlSelf->core__DOT__reg_0__DOT__regs_30)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelf->core__DOT__rs1))
                                                     ? vlSelf->core__DOT__reg_0__DOT__regs_29
                                                     : vlSelf->core__DOT__reg_0__DOT__regs_28))
                                                   : 
                                                  ((2U 
                                                    & (IData)(vlSelf->core__DOT__rs1))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelf->core__DOT__rs1))
                                                     ? vlSelf->core__DOT__reg_0__DOT__regs_27
                                                     : vlSelf->core__DOT__reg_0__DOT__regs_26)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelf->core__DOT__rs1))
                                                     ? vlSelf->core__DOT__reg_0__DOT__regs_25
                                                     : vlSelf->core__DOT__reg_0__DOT__regs_24)))
                                                  : 
                                                 ((4U 
                                                   & (IData)(vlSelf->core__DOT__rs1))
                                                   ? 
                                                  ((2U 
                                                    & (IData)(vlSelf->core__DOT__rs1))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelf->core__DOT__rs1))
                                                     ? vlSelf->core__DOT__reg_0__DOT__regs_23
                                                     : vlSelf->core__DOT__reg_0__DOT__regs_22)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelf->core__DOT__rs1))
                                                     ? vlSelf->core__DOT__reg_0__DOT__regs_21
                                                     : vlSelf->core__DOT__reg_0__DOT__regs_20))
                                                   : 
                                                  ((2U 
                                                    & (IData)(vlSelf->core__DOT__rs1))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelf->core__DOT__rs1))
                                                     ? vlSelf->core__DOT__reg_0__DOT__regs_19
                                                     : vlSelf->core__DOT__reg_0__DOT__regs_18)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelf->core__DOT__rs1))
                                                     ? vlSelf->core__DOT__reg_0__DOT__regs_17
                                                     : vlSelf->core__DOT__reg_0__DOT__regs_16))))
                                                 : 
                                                ((8U 
                                                  & (IData)(vlSelf->core__DOT__rs1))
                                                  ? 
                                                 ((4U 
                                                   & (IData)(vlSelf->core__DOT__rs1))
                                                   ? 
                                                  ((2U 
                                                    & (IData)(vlSelf->core__DOT__rs1))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelf->core__DOT__rs1))
                                                     ? vlSelf->core__DOT__reg_0__DOT__regs_15
                                                     : vlSelf->core__DOT__reg_0__DOT__regs_14)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelf->core__DOT__rs1))
                                                     ? vlSelf->core__DOT__reg_0__DOT__regs_13
                                                     : vlSelf->core__DOT__reg_0__DOT__regs_12))
                                                   : 
                                                  ((2U 
                                                    & (IData)(vlSelf->core__DOT__rs1))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelf->core__DOT__rs1))
                                                     ? vlSelf->core__DOT__reg_0__DOT__regs_11
                                                     : vlSelf->core__DOT__reg_0__DOT__regs_10)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelf->core__DOT__rs1))
                                                     ? vlSelf->core__DOT__reg_0__DOT__regs_9
                                                     : vlSelf->core__DOT__reg_0__DOT__regs_8)))
                                                  : 
                                                 ((4U 
                                                   & (IData)(vlSelf->core__DOT__rs1))
                                                   ? 
                                                  ((2U 
                                                    & (IData)(vlSelf->core__DOT__rs1))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelf->core__DOT__rs1))
                                                     ? vlSelf->core__DOT__reg_0__DOT__regs_7
                                                     : vlSelf->core__DOT__reg_0__DOT__regs_6)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelf->core__DOT__rs1))
                                                     ? vlSelf->core__DOT__reg_0__DOT__regs_5
                                                     : vlSelf->core__DOT__reg_0__DOT__regs_4))
                                                   : 
                                                  ((2U 
                                                    & (IData)(vlSelf->core__DOT__rs1))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelf->core__DOT__rs1))
                                                     ? vlSelf->core__DOT__reg_0__DOT__regs_3
                                                     : vlSelf->core__DOT__reg_0__DOT__regs_2)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelf->core__DOT__rs1))
                                                     ? vlSelf->core__DOT__reg_0__DOT__regs_1
                                                     : vlSelf->core__DOT__reg_0__DOT__regs_0)))));
}

VL_ATTR_COLD void Vcore___024root___eval_triggers__stl(Vcore___024root* vlSelf);

VL_ATTR_COLD bool Vcore___024root___eval_phase__stl(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___eval_phase__stl\n"); );
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vcore___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelf->__VstlTriggered.any();
    if (__VstlExecute) {
        Vcore___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcore___024root___dump_triggers__act(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ vlSelf->__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clock)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcore___024root___dump_triggers__nba(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ vlSelf->__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clock)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vcore___024root___ctor_var_reset(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clock = VL_RAND_RESET_I(1);
    vlSelf->reset = VL_RAND_RESET_I(1);
    vlSelf->io_pc = VL_RAND_RESET_I(32);
    vlSelf->io_value = VL_RAND_RESET_I(32);
    vlSelf->io_addr = VL_RAND_RESET_I(32);
    vlSelf->io_instr = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__pc = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__immI = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__rs1 = VL_RAND_RESET_I(5);
    vlSelf->core__DOT__rd = VL_RAND_RESET_I(5);
    vlSelf->core__DOT__addi = VL_RAND_RESET_I(1);
    vlSelf->core__DOT__src1 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__res = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_0 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_1 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_2 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_3 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_4 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_5 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_6 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_7 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_8 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_9 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_10 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_11 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_12 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_13 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_14 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_15 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_16 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_17 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_18 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_19 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_20 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_21 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_22 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_23 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_24 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_25 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_26 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_27 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_28 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_29 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_30 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__regs_31 = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT__casez_tmp = VL_RAND_RESET_I(32);
    vlSelf->__Vtrigprevexpr___TOP__clock__0 = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
