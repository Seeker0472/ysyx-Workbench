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
            VL_FATAL_MT("build/core.sv", 587, "", "Settle region did not converge.");
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
        vlSelf->__Vm_traceActivity[2U] = 1U;
        vlSelf->__Vm_traceActivity[1U] = 1U;
        vlSelf->__Vm_traceActivity[0U] = 1U;
    }
}

VL_ATTR_COLD void Vcore___024root___stl_sequent__TOP__0(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___stl_sequent__TOP__0\n"); );
    // Init
    CData/*7:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T;
    core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T = 0;
    CData/*7:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1;
    core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1 = 0;
    CData/*7:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_3;
    core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_3 = 0;
    CData/*5:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_5;
    core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_5 = 0;
    SData/*9:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_12;
    core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_12 = 0;
    CData/*6:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_14;
    core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_14 = 0;
    SData/*15:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16;
    core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16 = 0;
    CData/*7:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17;
    core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17 = 0;
    SData/*15:0*/ core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_20;
    core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_20 = 0;
    CData/*0:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_29;
    core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_29 = 0;
    CData/*0:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_30;
    core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_30 = 0;
    CData/*1:0*/ core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_31;
    core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_31 = 0;
    // Body
    vlSelf->io_pc = vlSelf->core__DOT__ifu__DOT__pc;
    vlSelf->io_inst_now = vlSelf->io_instr;
    core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_29 
        = (IData)((0U == (0xbe000000U & vlSelf->io_instr)));
    core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_30 
        = (IData)((0U == (0xfe000000U & vlSelf->io_instr)));
    vlSelf->core__DOT__reg_0__DOT__casez_tmp = ((0x40000U 
                                                 & vlSelf->io_instr)
                                                 ? 
                                                ((0x20000U 
                                                  & vlSelf->io_instr)
                                                  ? 
                                                 ((0x10000U 
                                                   & vlSelf->io_instr)
                                                   ? 
                                                  ((0x8000U 
                                                    & vlSelf->io_instr)
                                                    ? vlSelf->core__DOT__reg_0__DOT__regs_15
                                                    : vlSelf->core__DOT__reg_0__DOT__regs_14)
                                                   : 
                                                  ((0x8000U 
                                                    & vlSelf->io_instr)
                                                    ? vlSelf->core__DOT__reg_0__DOT__regs_13
                                                    : vlSelf->core__DOT__reg_0__DOT__regs_12))
                                                  : 
                                                 ((0x10000U 
                                                   & vlSelf->io_instr)
                                                   ? 
                                                  ((0x8000U 
                                                    & vlSelf->io_instr)
                                                    ? vlSelf->core__DOT__reg_0__DOT__regs_11
                                                    : vlSelf->core__DOT__reg_0__DOT__regs_10)
                                                   : 
                                                  ((0x8000U 
                                                    & vlSelf->io_instr)
                                                    ? vlSelf->core__DOT__reg_0__DOT__regs_9
                                                    : vlSelf->core__DOT__reg_0__DOT__regs_8)))
                                                 : 
                                                ((0x20000U 
                                                  & vlSelf->io_instr)
                                                  ? 
                                                 ((0x10000U 
                                                   & vlSelf->io_instr)
                                                   ? 
                                                  ((0x8000U 
                                                    & vlSelf->io_instr)
                                                    ? vlSelf->core__DOT__reg_0__DOT__regs_7
                                                    : vlSelf->core__DOT__reg_0__DOT__regs_6)
                                                   : 
                                                  ((0x8000U 
                                                    & vlSelf->io_instr)
                                                    ? vlSelf->core__DOT__reg_0__DOT__regs_5
                                                    : vlSelf->core__DOT__reg_0__DOT__regs_4))
                                                  : 
                                                 ((0x10000U 
                                                   & vlSelf->io_instr)
                                                   ? 
                                                  ((0x8000U 
                                                    & vlSelf->io_instr)
                                                    ? vlSelf->core__DOT__reg_0__DOT__regs_3
                                                    : vlSelf->core__DOT__reg_0__DOT__regs_2)
                                                   : 
                                                  ((0x8000U 
                                                    & vlSelf->io_instr)
                                                    ? vlSelf->core__DOT__reg_0__DOT__regs_1
                                                    : vlSelf->core__DOT__reg_0__DOT__regs_0))));
    core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_5 
        = ((0x20U & (vlSelf->io_instr << 5U)) | ((0x10U 
                                                  & (vlSelf->io_instr 
                                                     << 3U)) 
                                                 | ((8U 
                                                     & (vlSelf->io_instr 
                                                        << 1U)) 
                                                    | ((4U 
                                                        & ((~ 
                                                            (vlSelf->io_instr 
                                                             >> 3U)) 
                                                           << 2U)) 
                                                       | ((2U 
                                                           & (vlSelf->io_instr 
                                                              >> 3U)) 
                                                          | (1U 
                                                             & (~ 
                                                                (vlSelf->io_instr 
                                                                 >> 6U))))))));
    core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_3 
        = ((0x80U & (vlSelf->io_instr << 7U)) | ((0x40U 
                                                  & (vlSelf->io_instr 
                                                     << 5U)) 
                                                 | ((0x20U 
                                                     & ((~ 
                                                         (vlSelf->io_instr 
                                                          >> 2U)) 
                                                        << 5U)) 
                                                    | ((0x10U 
                                                        & ((~ 
                                                            (vlSelf->io_instr 
                                                             >> 3U)) 
                                                           << 4U)) 
                                                       | ((8U 
                                                           & ((~ 
                                                               (vlSelf->io_instr 
                                                                >> 5U)) 
                                                              << 3U)) 
                                                          | ((4U 
                                                              & ((~ 
                                                                  (vlSelf->io_instr 
                                                                   >> 6U)) 
                                                                 << 2U)) 
                                                             | ((2U 
                                                                 & ((~ 
                                                                     (vlSelf->io_instr 
                                                                      >> 0xcU)) 
                                                                    << 1U)) 
                                                                | (1U 
                                                                   & (~ 
                                                                      (vlSelf->io_instr 
                                                                       >> 0xeU))))))))));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_18 
        = ((0x80U & (vlSelf->io_instr << 7U)) | ((0x40U 
                                                  & (vlSelf->io_instr 
                                                     << 5U)) 
                                                 | ((0x20U 
                                                     & ((~ 
                                                         (vlSelf->io_instr 
                                                          >> 2U)) 
                                                        << 5U)) 
                                                    | ((0x10U 
                                                        & ((~ 
                                                            (vlSelf->io_instr 
                                                             >> 3U)) 
                                                           << 4U)) 
                                                       | ((8U 
                                                           & ((~ 
                                                               (vlSelf->io_instr 
                                                                >> 4U)) 
                                                              << 3U)) 
                                                          | ((4U 
                                                              & (vlSelf->io_instr 
                                                                 >> 3U)) 
                                                             | ((2U 
                                                                 & (vlSelf->io_instr 
                                                                    >> 5U)) 
                                                                | (1U 
                                                                   & (vlSelf->io_instr 
                                                                      >> 0xeU)))))))));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_10 
        = ((0x80U & (vlSelf->io_instr << 7U)) | ((0x40U 
                                                  & (vlSelf->io_instr 
                                                     << 5U)) 
                                                 | ((0x20U 
                                                     & ((~ 
                                                         (vlSelf->io_instr 
                                                          >> 2U)) 
                                                        << 5U)) 
                                                    | ((0x10U 
                                                        & ((~ 
                                                            (vlSelf->io_instr 
                                                             >> 3U)) 
                                                           << 4U)) 
                                                       | ((8U 
                                                           & ((~ 
                                                               (vlSelf->io_instr 
                                                                >> 4U)) 
                                                              << 3U)) 
                                                          | ((4U 
                                                              & (vlSelf->io_instr 
                                                                 >> 3U)) 
                                                             | ((2U 
                                                                 & (vlSelf->io_instr 
                                                                    >> 5U)) 
                                                                | (1U 
                                                                   & (~ 
                                                                      (vlSelf->io_instr 
                                                                       >> 0xdU))))))))));
    core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_12 
        = ((0x200U & (vlSelf->io_instr << 9U)) | ((0x100U 
                                                   & (vlSelf->io_instr 
                                                      << 7U)) 
                                                  | ((0x80U 
                                                      & (vlSelf->io_instr 
                                                         << 5U)) 
                                                     | ((0x40U 
                                                         & ((~ 
                                                             (vlSelf->io_instr 
                                                              >> 3U)) 
                                                            << 6U)) 
                                                        | ((0x20U 
                                                            & ((~ 
                                                                (vlSelf->io_instr 
                                                                 >> 4U)) 
                                                               << 5U)) 
                                                           | ((0x10U 
                                                               & (vlSelf->io_instr 
                                                                  >> 1U)) 
                                                              | ((8U 
                                                                  & (vlSelf->io_instr 
                                                                     >> 3U)) 
                                                                 | ((4U 
                                                                     & ((~ 
                                                                         (vlSelf->io_instr 
                                                                          >> 0xcU)) 
                                                                        << 2U)) 
                                                                    | ((2U 
                                                                        & ((~ 
                                                                            (vlSelf->io_instr 
                                                                             >> 0xdU)) 
                                                                           << 1U)) 
                                                                       | (1U 
                                                                          & (~ 
                                                                             (vlSelf->io_instr 
                                                                              >> 0xeU))))))))))));
    core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16 
        = ((0x8000U & (vlSelf->io_instr << 0xfU)) | 
           ((0x4000U & (vlSelf->io_instr << 0xdU)) 
            | ((0x2000U & ((~ (vlSelf->io_instr >> 2U)) 
                           << 0xdU)) | ((0x1000U & 
                                         ((~ (vlSelf->io_instr 
                                              >> 3U)) 
                                          << 0xcU)) 
                                        | ((0x800U 
                                            & (vlSelf->io_instr 
                                               << 7U)) 
                                           | ((0x400U 
                                               & ((~ 
                                                   (vlSelf->io_instr 
                                                    >> 5U)) 
                                                  << 0xaU)) 
                                              | ((0x200U 
                                                  & ((~ 
                                                      (vlSelf->io_instr 
                                                       >> 6U)) 
                                                     << 9U)) 
                                                 | ((0x100U 
                                                     & (vlSelf->io_instr 
                                                        >> 4U)) 
                                                    | ((0x80U 
                                                        & ((~ 
                                                            (vlSelf->io_instr 
                                                             >> 0xdU)) 
                                                           << 7U)) 
                                                       | ((0x40U 
                                                           & ((~ 
                                                               (vlSelf->io_instr 
                                                                >> 0x19U)) 
                                                              << 6U)) 
                                                          | ((0x20U 
                                                              & ((~ 
                                                                  (vlSelf->io_instr 
                                                                   >> 0x1aU)) 
                                                                 << 5U)) 
                                                             | ((0x10U 
                                                                 & ((~ 
                                                                     (vlSelf->io_instr 
                                                                      >> 0x1bU)) 
                                                                    << 4U)) 
                                                                | ((8U 
                                                                    & ((~ 
                                                                        (vlSelf->io_instr 
                                                                         >> 0x1cU)) 
                                                                       << 3U)) 
                                                                   | ((4U 
                                                                       & ((~ 
                                                                           (vlSelf->io_instr 
                                                                            >> 0x1dU)) 
                                                                          << 2U)) 
                                                                      | ((2U 
                                                                          & ((~ 
                                                                              (vlSelf->io_instr 
                                                                               >> 0x1eU)) 
                                                                             << 1U)) 
                                                                         | (1U 
                                                                            & (~ 
                                                                               (vlSelf->io_instr 
                                                                                >> 0x1fU))))))))))))))))));
    core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_20 
        = ((0x8000U & (vlSelf->io_instr << 0xfU)) | 
           ((0x4000U & (vlSelf->io_instr << 0xdU)) 
            | ((0x2000U & ((~ (vlSelf->io_instr >> 2U)) 
                           << 0xdU)) | ((0x1000U & 
                                         ((~ (vlSelf->io_instr 
                                              >> 3U)) 
                                          << 0xcU)) 
                                        | ((0x800U 
                                            & (vlSelf->io_instr 
                                               << 7U)) 
                                           | ((0x400U 
                                               & ((~ 
                                                   (vlSelf->io_instr 
                                                    >> 5U)) 
                                                  << 0xaU)) 
                                              | ((0x200U 
                                                  & ((~ 
                                                      (vlSelf->io_instr 
                                                       >> 6U)) 
                                                     << 9U)) 
                                                 | ((0x100U 
                                                     & (vlSelf->io_instr 
                                                        >> 4U)) 
                                                    | ((0x80U 
                                                        & ((~ 
                                                            (vlSelf->io_instr 
                                                             >> 0xdU)) 
                                                           << 7U)) 
                                                       | ((0x40U 
                                                           & (vlSelf->io_instr 
                                                              >> 8U)) 
                                                          | ((0x20U 
                                                              & ((~ 
                                                                  (vlSelf->io_instr 
                                                                   >> 0x19U)) 
                                                                 << 5U)) 
                                                             | ((0x10U 
                                                                 & ((~ 
                                                                     (vlSelf->io_instr 
                                                                      >> 0x1aU)) 
                                                                    << 4U)) 
                                                                | ((8U 
                                                                    & ((~ 
                                                                        (vlSelf->io_instr 
                                                                         >> 0x1bU)) 
                                                                       << 3U)) 
                                                                   | ((4U 
                                                                       & ((~ 
                                                                           (vlSelf->io_instr 
                                                                            >> 0x1cU)) 
                                                                          << 2U)) 
                                                                      | ((2U 
                                                                          & ((~ 
                                                                              (vlSelf->io_instr 
                                                                               >> 0x1dU)) 
                                                                             << 1U)) 
                                                                         | (1U 
                                                                            & (~ 
                                                                               (vlSelf->io_instr 
                                                                                >> 0x1fU))))))))))))))))));
    core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T 
        = ((0x80U & (vlSelf->io_instr << 7U)) | ((0x40U 
                                                  & (vlSelf->io_instr 
                                                     << 5U)) 
                                                 | ((0x20U 
                                                     & ((~ 
                                                         (vlSelf->io_instr 
                                                          >> 2U)) 
                                                        << 5U)) 
                                                    | ((0x10U 
                                                        & ((~ 
                                                            (vlSelf->io_instr 
                                                             >> 3U)) 
                                                           << 4U)) 
                                                       | ((8U 
                                                           & ((~ 
                                                               (vlSelf->io_instr 
                                                                >> 4U)) 
                                                              << 3U)) 
                                                          | ((4U 
                                                              & ((~ 
                                                                  (vlSelf->io_instr 
                                                                   >> 5U)) 
                                                                 << 2U)) 
                                                             | ((2U 
                                                                 & ((~ 
                                                                     (vlSelf->io_instr 
                                                                      >> 6U)) 
                                                                    << 1U)) 
                                                                | (1U 
                                                                   & (~ 
                                                                      (vlSelf->io_instr 
                                                                       >> 0xdU))))))))));
    core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1 
        = ((0x80U & (vlSelf->io_instr << 7U)) | ((0x40U 
                                                  & (vlSelf->io_instr 
                                                     << 5U)) 
                                                 | ((0x20U 
                                                     & ((~ 
                                                         (vlSelf->io_instr 
                                                          >> 2U)) 
                                                        << 5U)) 
                                                    | ((0x10U 
                                                        & ((~ 
                                                            (vlSelf->io_instr 
                                                             >> 3U)) 
                                                           << 4U)) 
                                                       | ((8U 
                                                           & ((~ 
                                                               (vlSelf->io_instr 
                                                                >> 5U)) 
                                                              << 3U)) 
                                                          | ((4U 
                                                              & ((~ 
                                                                  (vlSelf->io_instr 
                                                                   >> 6U)) 
                                                                 << 2U)) 
                                                             | ((2U 
                                                                 & ((~ 
                                                                     (vlSelf->io_instr 
                                                                      >> 0xcU)) 
                                                                    << 1U)) 
                                                                | (1U 
                                                                   & (~ 
                                                                      (vlSelf->io_instr 
                                                                       >> 0xdU))))))))));
    core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17 
        = ((0x80U & (vlSelf->io_instr << 7U)) | ((0x40U 
                                                  & (vlSelf->io_instr 
                                                     << 5U)) 
                                                 | ((0x20U 
                                                     & ((~ 
                                                         (vlSelf->io_instr 
                                                          >> 2U)) 
                                                        << 5U)) 
                                                    | ((0x10U 
                                                        & ((~ 
                                                            (vlSelf->io_instr 
                                                             >> 3U)) 
                                                           << 4U)) 
                                                       | ((8U 
                                                           & (vlSelf->io_instr 
                                                              >> 1U)) 
                                                          | ((4U 
                                                              & ((~ 
                                                                  (vlSelf->io_instr 
                                                                   >> 5U)) 
                                                                 << 2U)) 
                                                             | ((2U 
                                                                 & ((~ 
                                                                     (vlSelf->io_instr 
                                                                      >> 6U)) 
                                                                    << 1U)) 
                                                                | (1U 
                                                                   & (vlSelf->io_instr 
                                                                      >> 0xdU)))))))));
    core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_31 
        = ((2U & (vlSelf->io_instr >> 4U)) | (1U & 
                                              (vlSelf->io_instr 
                                               >> 6U)));
    core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_14 
        = ((0x40U & (vlSelf->io_instr << 6U)) | ((0x20U 
                                                  & (vlSelf->io_instr 
                                                     << 4U)) 
                                                 | ((0x10U 
                                                     & ((~ 
                                                         (vlSelf->io_instr 
                                                          >> 2U)) 
                                                        << 4U)) 
                                                    | ((8U 
                                                        & ((~ 
                                                            (vlSelf->io_instr 
                                                             >> 3U)) 
                                                           << 3U)) 
                                                       | ((4U 
                                                           & (vlSelf->io_instr 
                                                              >> 2U)) 
                                                          | (IData)(core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_31))))));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_13 
        = ((0x40U & (vlSelf->io_instr << 6U)) | ((0x20U 
                                                  & (vlSelf->io_instr 
                                                     << 4U)) 
                                                 | ((0x10U 
                                                     & (vlSelf->io_instr 
                                                        << 2U)) 
                                                    | ((8U 
                                                        & vlSelf->io_instr) 
                                                       | ((4U 
                                                           & ((~ 
                                                               (vlSelf->io_instr 
                                                                >> 4U)) 
                                                              << 2U)) 
                                                          | (IData)(core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_31))))));
    vlSelf->core__DOT___decoder_io_out_pc_jump = ((0x3ffU 
                                                   == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_12)) 
                                                  | (0x7fU 
                                                     == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_13)));
    vlSelf->core__DOT___decoder_io_out_reg_write_enable 
        = ((0xffU == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T)) 
           | ((0xffU == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1)) 
              | ((0xffU == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_3)) 
                 | ((0x3fU == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_5)) 
                    | ((IData)(((0x33U == (0x707fU 
                                           & vlSelf->io_instr)) 
                                & (IData)(core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_29))) 
                       | ((IData)(((0x33U == (0x7fU 
                                              & vlSelf->io_instr)) 
                                   & (IData)(core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_30))) 
                          | ((0x3ffU == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_12)) 
                             | ((0x7fU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_13)) 
                                | ((0x7fU == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_14)) 
                                   | ((IData)(((0x1013U 
                                                == 
                                                (0x305fU 
                                                 & vlSelf->io_instr)) 
                                               & (IData)(core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_30))) 
                                      | ((0xffU == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17)) 
                                         | (IData)(
                                                   ((0x5013U 
                                                     == 
                                                     (0x705fU 
                                                      & vlSelf->io_instr)) 
                                                    & (IData)(core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_29))))))))))))));
    vlSelf->core__DOT___decoder_io_out_alu_use_Imm_2 
        = (1U & ((0xffU == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T)) 
                 | ((0xffU == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1)) 
                    | ((IData)((3U == (0x505fU & vlSelf->io_instr))) 
                       | ((IData)((3U == (0x605fU & vlSelf->io_instr))) 
                          | ((0x3ffU == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_12)) 
                             | ((0x7fU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_13)) 
                                | ((0x7fU == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_14)) 
                                   | ((0xffffU == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)) 
                                      | ((0xffU == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17)) 
                                         | (0xffffU 
                                            == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_20))))))))))));
    vlSelf->core__DOT__decoder__DOT__casez_tmp = ((
                                                   (0x3fU 
                                                    == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_5)) 
                                                   | (0x7fU 
                                                      == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_13)))
                                                   ? 
                                                  ((1U 
                                                    & ((IData)(
                                                               (0x23U 
                                                                == 
                                                                (0x507fU 
                                                                 & vlSelf->io_instr))) 
                                                       | ((IData)(
                                                                  (0x23U 
                                                                   == 
                                                                   (0x603fU 
                                                                    & vlSelf->io_instr))) 
                                                          | (0xffU 
                                                             == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_18)))))
                                                    ? 0U
                                                    : 
                                                   ((1U 
                                                     & ((0xffU 
                                                         == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T)) 
                                                        | ((0xffU 
                                                            == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1)) 
                                                           | ((0xffU 
                                                               == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_3)) 
                                                              | ((0xffU 
                                                                  == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_10)) 
                                                                 | ((IData)(
                                                                            (0x63U 
                                                                             == 
                                                                             (0x707bU 
                                                                              & vlSelf->io_instr))) 
                                                                    | ((0x7fU 
                                                                        == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_13)) 
                                                                       | ((0x7fU 
                                                                           == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_14)) 
                                                                          | ((0xffffU 
                                                                              == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)) 
                                                                             | ((0xffU 
                                                                                == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17)) 
                                                                                | ((0xffU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_18)) 
                                                                                | (0xffffU 
                                                                                == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_20)))))))))))))
                                                     ? 
                                                    (((- (IData)(
                                                                 (vlSelf->io_instr 
                                                                  >> 0x1fU))) 
                                                      << 0x14U) 
                                                     | ((0xff000U 
                                                         & vlSelf->io_instr) 
                                                        | ((0x800U 
                                                            & (vlSelf->io_instr 
                                                               >> 9U)) 
                                                           | (0x7feU 
                                                              & (vlSelf->io_instr 
                                                                 >> 0x14U)))))
                                                     : 
                                                    (0xfffff000U 
                                                     & vlSelf->io_instr)))
                                                   : 
                                                  ((1U 
                                                    & ((IData)(
                                                               (0x23U 
                                                                == 
                                                                (0x507fU 
                                                                 & vlSelf->io_instr))) 
                                                       | ((IData)(
                                                                  (0x23U 
                                                                   == 
                                                                   (0x603fU 
                                                                    & vlSelf->io_instr))) 
                                                          | (0xffU 
                                                             == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_18)))))
                                                    ? 
                                                   ((1U 
                                                     & ((0xffU 
                                                         == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T)) 
                                                        | ((0xffU 
                                                            == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1)) 
                                                           | ((0xffU 
                                                               == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_3)) 
                                                              | ((0xffU 
                                                                  == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_10)) 
                                                                 | ((IData)(
                                                                            (0x63U 
                                                                             == 
                                                                             (0x707bU 
                                                                              & vlSelf->io_instr))) 
                                                                    | ((0x7fU 
                                                                        == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_13)) 
                                                                       | ((0x7fU 
                                                                           == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_14)) 
                                                                          | ((0xffffU 
                                                                              == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)) 
                                                                             | ((0xffU 
                                                                                == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17)) 
                                                                                | ((0xffU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_18)) 
                                                                                | (0xffffU 
                                                                                == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_20)))))))))))))
                                                     ? 
                                                    (((- (IData)(
                                                                 (1U 
                                                                  & (vlSelf->io_instr 
                                                                     >> 8U)))) 
                                                      << 0x12U) 
                                                     | ((0x20000U 
                                                         & (vlSelf->io_instr 
                                                            >> 0xeU)) 
                                                        | ((0x10000U 
                                                            & (vlSelf->io_instr 
                                                               << 9U)) 
                                                           | ((0xf800U 
                                                               & (vlSelf->io_instr 
                                                                  << 4U)) 
                                                              | ((0x7e0U 
                                                                  & (vlSelf->io_instr 
                                                                     >> 0x14U)) 
                                                                 | (0x1eU 
                                                                    & (vlSelf->io_instr 
                                                                       >> 7U)))))))
                                                     : 
                                                    (((- (IData)(
                                                                 (vlSelf->io_instr 
                                                                  >> 0x1fU))) 
                                                      << 0xcU) 
                                                     | ((0xfe0U 
                                                         & (vlSelf->io_instr 
                                                            >> 0x14U)) 
                                                        | (0x1fU 
                                                           & (vlSelf->io_instr 
                                                              >> 7U)))))
                                                    : 
                                                   ((1U 
                                                     & ((0xffU 
                                                         == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T)) 
                                                        | ((0xffU 
                                                            == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1)) 
                                                           | ((0xffU 
                                                               == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_3)) 
                                                              | ((0xffU 
                                                                  == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_10)) 
                                                                 | ((IData)(
                                                                            (0x63U 
                                                                             == 
                                                                             (0x707bU 
                                                                              & vlSelf->io_instr))) 
                                                                    | ((0x7fU 
                                                                        == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_13)) 
                                                                       | ((0x7fU 
                                                                           == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_14)) 
                                                                          | ((0xffffU 
                                                                              == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)) 
                                                                             | ((0xffU 
                                                                                == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17)) 
                                                                                | ((0xffU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_18)) 
                                                                                | (0xffffU 
                                                                                == (IData)(core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_20)))))))))))))
                                                     ? 
                                                    (((- (IData)(
                                                                 (vlSelf->io_instr 
                                                                  >> 0x1fU))) 
                                                      << 0xcU) 
                                                     | (vlSelf->io_instr 
                                                        >> 0x14U))
                                                     : 0U)));
    vlSelf->core__DOT__reg_0__DOT___GEN = ((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
                                           & (0U != 
                                              (0x1fU 
                                               & (vlSelf->io_instr 
                                                  >> 7U))));
    vlSelf->core__DOT__exu__DOT___alu_io_result = (
                                                   (((0xffU 
                                                      == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_10)) 
                                                     | ((0x7fU 
                                                         == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_13)) 
                                                        | (0xffU 
                                                           == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_18))))
                                                     ? vlSelf->core__DOT__ifu__DOT__pc
                                                     : vlSelf->core__DOT__reg_0__DOT__casez_tmp) 
                                                   + 
                                                   ((IData)(vlSelf->core__DOT___decoder_io_out_alu_use_Imm_2)
                                                     ? vlSelf->core__DOT__decoder__DOT__casez_tmp
                                                     : vlSelf->core__DOT__reg_0__DOT__casez_tmp));
    if (vlSelf->core__DOT___decoder_io_out_pc_jump) {
        vlSelf->io_value = ((IData)(4U) + vlSelf->core__DOT__ifu__DOT__pc);
        vlSelf->core__DOT___exu_io_out_n_pc = vlSelf->core__DOT__exu__DOT___alu_io_result;
    } else {
        vlSelf->io_value = vlSelf->core__DOT__exu__DOT___alu_io_result;
        vlSelf->core__DOT___exu_io_out_n_pc = ((IData)(4U) 
                                               + vlSelf->core__DOT__ifu__DOT__pc);
    }
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
VL_ATTR_COLD void Vcore___024root___dump_triggers__ico(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ vlSelf->__VicoTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

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
    vlSelf->io_inst_now = VL_RAND_RESET_I(32);
    vlSelf->core__DOT___exu_io_out_n_pc = VL_RAND_RESET_I(32);
    vlSelf->core__DOT___decoder_io_out_alu_use_Imm_2 = VL_RAND_RESET_I(1);
    vlSelf->core__DOT___decoder_io_out_pc_jump = VL_RAND_RESET_I(1);
    vlSelf->core__DOT___decoder_io_out_reg_write_enable = VL_RAND_RESET_I(1);
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_10 = VL_RAND_RESET_I(8);
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_13 = VL_RAND_RESET_I(7);
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_18 = VL_RAND_RESET_I(8);
    vlSelf->core__DOT__decoder__DOT__casez_tmp = VL_RAND_RESET_I(32);
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
    vlSelf->core__DOT__reg_0__DOT__casez_tmp = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__reg_0__DOT___GEN = VL_RAND_RESET_I(1);
    vlSelf->core__DOT__ifu__DOT__pc = VL_RAND_RESET_I(32);
    vlSelf->core__DOT__exu__DOT___alu_io_result = VL_RAND_RESET_I(32);
    vlSelf->__Vtrigprevexpr___TOP__clock__0 = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
