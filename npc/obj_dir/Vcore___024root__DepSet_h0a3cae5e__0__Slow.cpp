// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcore.h for the primary calling header

#include "Vcore__pch.h"
#include "Vcore__Syms.h"
#include "Vcore___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcore___024root___dump_triggers__stl(Vcore___024root* vlSelf);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vcore___024root___eval_triggers__stl(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___eval_triggers__stl\n"); );
    // Body
    vlSelf->__VstlTriggered.set(0U, (IData)(vlSelf->__VstlFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vcore___024root___dump_triggers__stl(vlSelf);
    }
#endif
}

void Vcore___024unit____Vdpiimwrap_call_ebreak_TOP____024unit();

VL_ATTR_COLD void Vcore___024root___stl_sequent__TOP__0(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___stl_sequent__TOP__0\n"); );
    // Body
    vlSelf->io_pc = vlSelf->core__DOT__ifu__DOT__pc;
    vlSelf->io_inst_now = vlSelf->io_instr;
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_28 
        = (IData)((0U == (0xbe000000U & vlSelf->io_instr)));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_29 
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
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_12 
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
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16 
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
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_20 
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
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17 
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
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_30 
        = ((2U & (vlSelf->io_instr >> 4U)) | (1U & 
                                              (vlSelf->io_instr 
                                               >> 6U)));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_14 
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
                                                          | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_30))))));
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
                                                          | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_30))))));
    if ((0x7fU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_14))) {
        Vcore___024unit____Vdpiimwrap_call_ebreak_TOP____024unit();
    }
    vlSelf->core__DOT___decoder_io_out_reg_write_enable 
        = ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T)) 
           | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1)) 
              | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_3)) 
                 | ((0x3fU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_5)) 
                    | ((IData)(((0x33U == (0x707fU 
                                           & vlSelf->io_instr)) 
                                & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_28))) 
                       | ((IData)(((0x33U == (0x7fU 
                                              & vlSelf->io_instr)) 
                                   & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_29))) 
                          | ((0x3ffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_12)) 
                             | ((0x7fU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_13)) 
                                | ((0x7fU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_14)) 
                                   | ((IData)(((0x1013U 
                                                == 
                                                (0x305fU 
                                                 & vlSelf->io_instr)) 
                                               & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_29))) 
                                      | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17)) 
                                         | (IData)(
                                                   ((0x5013U 
                                                     == 
                                                     (0x705fU 
                                                      & vlSelf->io_instr)) 
                                                    & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_28))))))))))))));
    vlSelf->core__DOT___decoder_io_out_pc_jump = ((0x3ffU 
                                                   == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_12)) 
                                                  | (0x7fU 
                                                     == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_13)));
    vlSelf->core__DOT___decoder_io_out_alu_use_Imm_2 
        = (1U & ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T)) 
                 | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1)) 
                    | ((IData)((3U == (0x505fU & vlSelf->io_instr))) 
                       | ((IData)((3U == (0x605fU & vlSelf->io_instr))) 
                          | ((0x3ffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_12)) 
                             | ((0x7fU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_13)) 
                                | ((0x7fU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_14)) 
                                   | ((0xffffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)) 
                                      | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17)) 
                                         | (0xffffU 
                                            == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_20))))))))))));
    vlSelf->core__DOT__decoder__DOT__casez_tmp = ((
                                                   (0x3fU 
                                                    == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_5)) 
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
                                                         == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T)) 
                                                        | ((0xffU 
                                                            == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1)) 
                                                           | ((0xffU 
                                                               == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_3)) 
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
                                                                           == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_14)) 
                                                                          | ((0xffffU 
                                                                              == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)) 
                                                                             | ((0xffU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17)) 
                                                                                | ((0xffU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_18)) 
                                                                                | (0xffffU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_20)))))))))))))
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
                                                         == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T)) 
                                                        | ((0xffU 
                                                            == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1)) 
                                                           | ((0xffU 
                                                               == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_3)) 
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
                                                                           == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_14)) 
                                                                          | ((0xffffU 
                                                                              == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)) 
                                                                             | ((0xffU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17)) 
                                                                                | ((0xffU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_18)) 
                                                                                | (0xffffU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_20)))))))))))))
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
                                                         == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T)) 
                                                        | ((0xffU 
                                                            == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1)) 
                                                           | ((0xffU 
                                                               == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_3)) 
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
                                                                           == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_14)) 
                                                                          | ((0xffffU 
                                                                              == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)) 
                                                                             | ((0xffU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17)) 
                                                                                | ((0xffU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_18)) 
                                                                                | (0xffffU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_20)))))))))))))
                                                     ? 
                                                    (((- (IData)(
                                                                 (vlSelf->io_instr 
                                                                  >> 0x1fU))) 
                                                      << 0xcU) 
                                                     | (vlSelf->io_instr 
                                                        >> 0x14U))
                                                     : 0U)));
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
