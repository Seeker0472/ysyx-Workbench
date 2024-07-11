// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcore.h for the primary calling header

#include "Vcore__pch.h"
#include "Vcore__Syms.h"
#include "Vcore___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcore___024root___dump_triggers__ico(Vcore___024root* vlSelf);
#endif  // VL_DEBUG

void Vcore___024root___eval_triggers__ico(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___eval_triggers__ico\n"); );
    // Body
    vlSelf->__VicoTriggered.set(0U, (IData)(vlSelf->__VicoFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vcore___024root___dump_triggers__ico(vlSelf);
    }
#endif
}

void Vcore___024unit____Vdpiimwrap_call_ebreak_TOP____024unit();

VL_INLINE_OPT void Vcore___024root___ico_sequent__TOP__0(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___ico_sequent__TOP__0\n"); );
    // Body
    vlSelf->io_inst_now = vlSelf->io_instr;
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_42 
        = (IData)((0U == (0xbe000000U & vlSelf->io_instr)));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_33 
        = (IData)((0x2000U == (0x6000U & vlSelf->io_instr)));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_36 
        = (IData)((0x40000000U == (0xfe000000U & vlSelf->io_instr)));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_38 
        = (IData)((0x6000U == (0x6000U & vlSelf->io_instr)));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_5 
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
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_26 
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
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_28 
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
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_6 
        = ((0x40U & (vlSelf->io_instr << 6U)) | ((0x20U 
                                                  & (vlSelf->io_instr 
                                                     << 4U)) 
                                                 | ((0x10U 
                                                     & (vlSelf->io_instr 
                                                        << 2U)) 
                                                    | ((8U 
                                                        & ((~ 
                                                            (vlSelf->io_instr 
                                                             >> 3U)) 
                                                           << 3U)) 
                                                       | ((4U 
                                                           & (vlSelf->io_instr 
                                                              >> 2U)) 
                                                          | ((2U 
                                                              & ((~ 
                                                                  (vlSelf->io_instr 
                                                                   >> 5U)) 
                                                                 << 1U)) 
                                                             | (1U 
                                                                & (~ 
                                                                   (vlSelf->io_instr 
                                                                    >> 6U)))))))));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_20 
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
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_35 
        = ((0x4000U & (vlSelf->io_instr << 0xeU)) | 
           ((0x2000U & (vlSelf->io_instr << 0xcU)) 
            | ((0x1000U & ((~ (vlSelf->io_instr >> 2U)) 
                           << 0xcU)) | ((0x800U & (
                                                   (~ 
                                                    (vlSelf->io_instr 
                                                     >> 3U)) 
                                                   << 0xbU)) 
                                        | ((0x400U 
                                            & (vlSelf->io_instr 
                                               << 6U)) 
                                           | ((0x200U 
                                               & (vlSelf->io_instr 
                                                  << 4U)) 
                                              | ((0x100U 
                                                  & (vlSelf->io_instr 
                                                     << 2U)) 
                                                 | ((0x80U 
                                                     & ((~ 
                                                         (vlSelf->io_instr 
                                                          >> 0xcU)) 
                                                        << 7U)) 
                                                    | ((0x40U 
                                                        & ((~ 
                                                            (vlSelf->io_instr 
                                                             >> 0xdU)) 
                                                           << 6U)) 
                                                       | ((0x20U 
                                                           & ((~ 
                                                               (vlSelf->io_instr 
                                                                >> 0xeU)) 
                                                              << 5U)) 
                                                          | ((0x10U 
                                                              & (vlSelf->io_instr 
                                                                 >> 0x10U)) 
                                                             | ((8U 
                                                                 & ((~ 
                                                                     (vlSelf->io_instr 
                                                                      >> 0x15U)) 
                                                                    << 3U)) 
                                                                | ((4U 
                                                                    & ((~ 
                                                                        (vlSelf->io_instr 
                                                                         >> 0x16U)) 
                                                                       << 2U)) 
                                                                   | ((2U 
                                                                       & ((~ 
                                                                           (vlSelf->io_instr 
                                                                            >> 0x17U)) 
                                                                          << 1U)) 
                                                                      | (1U 
                                                                         & (~ 
                                                                            (vlSelf->io_instr 
                                                                             >> 0x18U)))))))))))))))));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_13 
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
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T 
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
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1 
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
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_46 
        = ((0x200U & ((~ (vlSelf->io_instr >> 6U)) 
                      << 9U)) | ((0x100U & (vlSelf->io_instr 
                                            >> 4U)) 
                                 | ((0x80U & ((~ (vlSelf->io_instr 
                                                  >> 0xdU)) 
                                              << 7U)) 
                                    | ((0x40U & ((~ 
                                                  (vlSelf->io_instr 
                                                   >> 0x19U)) 
                                                 << 6U)) 
                                       | ((0x20U & 
                                           ((~ (vlSelf->io_instr 
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
                                                             >> 0x1fU))))))))))));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16 
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
                                                          | ((2U 
                                                              & (vlSelf->io_instr 
                                                                 >> 4U)) 
                                                             | (1U 
                                                                & (vlSelf->io_instr 
                                                                   >> 6U))))))));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_34 
        = (IData)((0U == (0xfe000000U & vlSelf->io_instr)));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_43 
        = ((4U & ((~ (vlSelf->io_instr >> 6U)) << 2U)) 
           | ((2U & ((~ (vlSelf->io_instr >> 0xcU)) 
                     << 1U)) | (1U & (~ (vlSelf->io_instr 
                                         >> 0xeU)))));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_44 
        = ((2U & ((~ (vlSelf->io_instr >> 0xdU)) << 1U)) 
           | (1U & (~ (vlSelf->io_instr >> 0xeU))));
    if ((0x7fffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_35))) {
        Vcore___024unit____Vdpiimwrap_call_ebreak_TOP____024unit();
    }
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17 
        = ((0x4000U & (vlSelf->io_instr << 0xeU)) | 
           ((0x2000U & (vlSelf->io_instr << 0xcU)) 
            | ((0x1000U & ((~ (vlSelf->io_instr >> 2U)) 
                           << 0xcU)) | ((0x800U & (
                                                   (~ 
                                                    (vlSelf->io_instr 
                                                     >> 3U)) 
                                                   << 0xbU)) 
                                        | ((0x400U 
                                            & (vlSelf->io_instr 
                                               << 6U)) 
                                           | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_46))))));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_18 
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
                                              | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_46)))))));
    vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src1 
        = (((0x7fU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_6)) 
            | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_13)) 
               | ((0x7fU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)) 
                  | (0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_26)))))
            ? vlSelf->core__DOT__ifu__DOT__pc : vlSelf->core__DOT__reg_0__DOT__casez_tmp);
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_35 
        = ((~ (vlSelf->io_instr >> 0xeU)) & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_34));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_39 
        = ((vlSelf->io_instr >> 0xeU) & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_34));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_2 
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
                                                          | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_43))))));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_3 
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
                                                          | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_43))))));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_4 
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
                                                                   >> 6U)) 
                                                                 << 2U)) 
                                                             | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_44)))))));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_45 
        = ((0x40U & ((~ (vlSelf->io_instr >> 3U)) << 6U)) 
           | ((0x20U & ((~ (vlSelf->io_instr >> 4U)) 
                        << 5U)) | ((0x10U & (vlSelf->io_instr 
                                             >> 1U)) 
                                   | ((8U & (vlSelf->io_instr 
                                             >> 3U)) 
                                      | ((4U & ((~ 
                                                 (vlSelf->io_instr 
                                                  >> 0xcU)) 
                                                << 2U)) 
                                         | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_44))))));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_40 
        = ((~ (vlSelf->io_instr >> 0xdU)) & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_39));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_15 
        = ((0x200U & (vlSelf->io_instr << 9U)) | ((0x100U 
                                                   & (vlSelf->io_instr 
                                                      << 7U)) 
                                                  | ((0x80U 
                                                      & (vlSelf->io_instr 
                                                         << 5U)) 
                                                     | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_45))));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_14 
        = ((0x100U & (vlSelf->io_instr << 8U)) | ((0x80U 
                                                   & (vlSelf->io_instr 
                                                      << 6U)) 
                                                  | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_45)));
    vlSelf->core__DOT___decoder_io_out_pc_jump = ((0x3ffU 
                                                   == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_15)) 
                                                  | (0x7fU 
                                                     == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)));
    vlSelf->core__DOT___decoder_io_out_reg_write_enable 
        = ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T)) 
           | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1)) 
              | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_3)) 
                 | ((0x3fU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_5)) 
                    | ((IData)(((0x33U == (0x707fU 
                                           & vlSelf->io_instr)) 
                                & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_42))) 
                       | ((IData)(((0x33U == (0x7fU 
                                              & vlSelf->io_instr)) 
                                   & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_34))) 
                          | ((0x3ffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_15)) 
                             | ((0x7fU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)) 
                                | ((0x7fffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17)) 
                                   | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_20)) 
                                      | ((IData)(((0x5013U 
                                                   == 
                                                   (0x705fU 
                                                    & vlSelf->io_instr)) 
                                                  & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_42))) 
                                         | (0x7fffU 
                                            == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_35)))))))))))));
    vlSelf->core__DOT___decoder_io_out_alu_op_type 
        = (((IData)(((0x13U == (0x1fU & vlSelf->io_instr)) 
                     & ((IData)(((0U == (0x60U & vlSelf->io_instr)) 
                                 & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_33))) 
                        | ((IData)(((0x2020U == (0x2060U 
                                                 & vlSelf->io_instr)) 
                                    & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_35))) 
                           | (IData)(((0x5000U == (0x7040U 
                                                   & vlSelf->io_instr)) 
                                      & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_36))))))) 
            << 3U) | ((((0x7fffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17)) 
                        | (IData)(((0x13U == (0x1fU 
                                              & vlSelf->io_instr)) 
                                   & ((IData)(((0U 
                                                == 
                                                (0x60U 
                                                 & vlSelf->io_instr)) 
                                               & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_38))) 
                                      | (IData)(((0x2020U 
                                                  == 
                                                  (0x2060U 
                                                   & vlSelf->io_instr)) 
                                                 & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_39))))))) 
                       << 2U) | ((2U & (((0x7fffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17)) 
                                         | (IData)(
                                                   ((0x13U 
                                                     == 
                                                     (0x1fU 
                                                      & vlSelf->io_instr)) 
                                                    & ((IData)(
                                                               ((0x1020U 
                                                                 == 
                                                                 (0x1060U 
                                                                  & vlSelf->io_instr)) 
                                                                & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_35))) 
                                                       | ((IData)(
                                                                  ((0x1000U 
                                                                    == 
                                                                    (0x1060U 
                                                                     & vlSelf->io_instr)) 
                                                                   & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_33))) 
                                                          | ((IData)(
                                                                     (0x4000U 
                                                                      == 
                                                                      (0x7060U 
                                                                       & vlSelf->io_instr))) 
                                                             | (IData)(
                                                                       ((0x20U 
                                                                         == 
                                                                         (0x60U 
                                                                          & vlSelf->io_instr)) 
                                                                        & ((IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_40) 
                                                                           | (IData)(
                                                                                ((0U 
                                                                                == 
                                                                                (0x7000U 
                                                                                & vlSelf->io_instr)) 
                                                                                & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_36)))))))))))) 
                                        << 1U)) | (1U 
                                                   & ((0xffU 
                                                       == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T)) 
                                                      | ((0xffU 
                                                          == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1)) 
                                                         | ((0xffU 
                                                             == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_2)) 
                                                            | ((0xffU 
                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_3)) 
                                                               | ((0xffU 
                                                                   == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_4)) 
                                                                  | ((0x7fU 
                                                                      == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_6)) 
                                                                     | ((IData)(
                                                                                ((0x33U 
                                                                                == 
                                                                                (0x307fU 
                                                                                & vlSelf->io_instr)) 
                                                                                & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_34))) 
                                                                        | ((IData)(
                                                                                ((0x33U 
                                                                                == 
                                                                                (0x107fU 
                                                                                & vlSelf->io_instr)) 
                                                                                & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_35))) 
                                                                           | ((0xffU 
                                                                               == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_13)) 
                                                                              | ((0x1ffU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_14)) 
                                                                                | ((0x7fU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)) 
                                                                                | (IData)(
                                                                                ((3U 
                                                                                == 
                                                                                (0xfU 
                                                                                & vlSelf->io_instr)) 
                                                                                & ((IData)(
                                                                                ((0x1010U 
                                                                                == 
                                                                                (0x1050U 
                                                                                & vlSelf->io_instr)) 
                                                                                & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_40))) 
                                                                                | ((IData)(
                                                                                ((0x1030U 
                                                                                == 
                                                                                (0x1070U 
                                                                                & vlSelf->io_instr)) 
                                                                                & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_39))) 
                                                                                | ((IData)(
                                                                                (0x5060U 
                                                                                == 
                                                                                (0x5070U 
                                                                                & vlSelf->io_instr))) 
                                                                                | (IData)(
                                                                                ((0x1010U 
                                                                                == 
                                                                                (0x1070U 
                                                                                & vlSelf->io_instr)) 
                                                                                & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_38)))))))))))))))))))))));
    vlSelf->core__DOT__decoder__DOT__casez_tmp = ((
                                                   (0x3fU 
                                                    == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_5)) 
                                                   | (0x7fU 
                                                      == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)))
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
                                                             == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_26)))))
                                                    ? 0U
                                                    : 
                                                   (((0xffU 
                                                      == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T)) 
                                                     | ((0xffU 
                                                         == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1)) 
                                                        | ((0xffU 
                                                            == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_3)) 
                                                           | ((0xffU 
                                                               == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_13)) 
                                                              | ((0x1ffU 
                                                                  == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_14)) 
                                                                 | ((0x7fU 
                                                                     == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)) 
                                                                    | ((0xffffU 
                                                                        == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_18)) 
                                                                       | ((0xffU 
                                                                           == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_20)) 
                                                                          | ((0xffU 
                                                                              == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_26)) 
                                                                             | ((0xffffU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_28)) 
                                                                                | (0x7fffU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_35))))))))))))
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
                                                             == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_26)))))
                                                    ? 
                                                   (((0xffU 
                                                      == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T)) 
                                                     | ((0xffU 
                                                         == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1)) 
                                                        | ((0xffU 
                                                            == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_3)) 
                                                           | ((0xffU 
                                                               == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_13)) 
                                                              | ((0x1ffU 
                                                                  == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_14)) 
                                                                 | ((0x7fU 
                                                                     == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)) 
                                                                    | ((0xffffU 
                                                                        == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_18)) 
                                                                       | ((0xffU 
                                                                           == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_20)) 
                                                                          | ((0xffU 
                                                                              == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_26)) 
                                                                             | ((0xffffU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_28)) 
                                                                                | (0x7fffU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_35))))))))))))
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
                                                   (((0xffU 
                                                      == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T)) 
                                                     | ((0xffU 
                                                         == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1)) 
                                                        | ((0xffU 
                                                            == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_3)) 
                                                           | ((0xffU 
                                                               == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_13)) 
                                                              | ((0x1ffU 
                                                                  == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_14)) 
                                                                 | ((0x7fU 
                                                                     == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)) 
                                                                    | ((0xffffU 
                                                                        == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_18)) 
                                                                       | ((0xffU 
                                                                           == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_20)) 
                                                                          | ((0xffU 
                                                                              == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_26)) 
                                                                             | ((0xffffU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_28)) 
                                                                                | (0x7fffU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_35))))))))))))
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
    vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src2 
        = (((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T)) 
            | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1)) 
               | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_2)) 
                  | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_4)) 
                     | ((0x7fU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_6)) 
                        | ((0x3ffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_15)) 
                           | ((0x7fU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)) 
                              | ((0xffffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_18)) 
                                 | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_20)) 
                                    | ((0xffffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_28)) 
                                       | (0x7fffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_35))))))))))))
            ? vlSelf->core__DOT__decoder__DOT__casez_tmp
            : vlSelf->core__DOT__reg_0__DOT__casez_tmp);
    vlSelf->core__DOT__exu__DOT__alu__DOT__casez_tmp 
        = ((8U & (IData)(vlSelf->core__DOT___decoder_io_out_alu_op_type))
            ? ((4U & (IData)(vlSelf->core__DOT___decoder_io_out_alu_op_type))
                ? 0U : ((2U & (IData)(vlSelf->core__DOT___decoder_io_out_alu_op_type))
                         ? ((1U & (IData)(vlSelf->core__DOT___decoder_io_out_alu_op_type))
                             ? 0U : (vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src1 
                                     < vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src2))
                         : ((1U & (IData)(vlSelf->core__DOT___decoder_io_out_alu_op_type))
                             ? VL_LTS_III(32, vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src1, vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src2)
                             : VL_SHIFTRS_III(32,32,32, vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src1, 
                                              (0xfU 
                                               & vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src2)))))
            : ((4U & (IData)(vlSelf->core__DOT___decoder_io_out_alu_op_type))
                ? ((2U & (IData)(vlSelf->core__DOT___decoder_io_out_alu_op_type))
                    ? ((1U & (IData)(vlSelf->core__DOT___decoder_io_out_alu_op_type))
                        ? VL_SHIFTR_III(32,32,32, vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src1, 
                                        (0xfU & vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src2))
                        : (vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src1 
                           << (0xfU & vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src2)))
                    : ((1U & (IData)(vlSelf->core__DOT___decoder_io_out_alu_op_type))
                        ? (vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src1 
                           & vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src2)
                        : (vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src1 
                           | vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src2)))
                : ((2U & (IData)(vlSelf->core__DOT___decoder_io_out_alu_op_type))
                    ? ((1U & (IData)(vlSelf->core__DOT___decoder_io_out_alu_op_type))
                        ? (vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src1 
                           ^ vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src2)
                        : (vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src1 
                           - vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src2))
                    : ((1U & (IData)(vlSelf->core__DOT___decoder_io_out_alu_op_type))
                        ? (vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src1 
                           + vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src2)
                        : 0U))));
    if (vlSelf->core__DOT___decoder_io_out_pc_jump) {
        vlSelf->io_value = ((IData)(4U) + vlSelf->core__DOT__ifu__DOT__pc);
        vlSelf->core__DOT___exu_io_out_n_pc = vlSelf->core__DOT__exu__DOT__alu__DOT__casez_tmp;
    } else {
        vlSelf->io_value = vlSelf->core__DOT__exu__DOT__alu__DOT__casez_tmp;
        vlSelf->core__DOT___exu_io_out_n_pc = ((IData)(4U) 
                                               + vlSelf->core__DOT__ifu__DOT__pc);
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcore___024root___dump_triggers__act(Vcore___024root* vlSelf);
#endif  // VL_DEBUG

void Vcore___024root___eval_triggers__act(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___eval_triggers__act\n"); );
    // Body
    vlSelf->__VactTriggered.set(0U, ((IData)(vlSelf->clock) 
                                     & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__clock__0))));
    vlSelf->__Vtrigprevexpr___TOP__clock__0 = vlSelf->clock;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vcore___024root___dump_triggers__act(vlSelf);
    }
#endif
}
