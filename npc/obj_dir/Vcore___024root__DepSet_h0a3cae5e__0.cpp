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
void Vcore___024unit____Vdpiimwrap_pmem_read_TOP____024unit(IData/*31:0*/ read_addr, IData/*31:0*/ &pmem_read__Vfuncrtn);
void Vcore___024unit____Vdpiimwrap_pmem_write_TOP____024unit(IData/*31:0*/ write_addr, IData/*31:0*/ write_data, CData/*7:0*/ write_mask);

VL_INLINE_OPT void Vcore___024root___ico_sequent__TOP__0(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___ico_sequent__TOP__0\n"); );
    // Body
    vlSelf->io_inst_now = vlSelf->io_instr;
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_60 
        = (IData)((0x6000U == (0x6000U & vlSelf->io_instr)));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_61 
        = (IData)((0x4000U == (0x5000U & vlSelf->io_instr)));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_33 
        = (IData)((0x2000U == (0x6000U & vlSelf->io_instr)));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_36 
        = (IData)((0x40000000U == (0xfe000000U & vlSelf->io_instr)));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_70 
        = ((8U & ((~ (vlSelf->io_instr >> 6U)) << 3U)) 
           | ((4U & ((~ (vlSelf->io_instr >> 0xcU)) 
                     << 2U)) | ((2U & (vlSelf->io_instr 
                                       >> 0xcU)) | 
                                (1U & (~ (vlSelf->io_instr 
                                          >> 0xeU))))));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_7 
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
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_49 
        = ((0x100U & (vlSelf->io_instr << 8U)) | ((0x80U 
                                                   & (vlSelf->io_instr 
                                                      << 6U)) 
                                                  | ((0x40U 
                                                      & ((~ 
                                                          (vlSelf->io_instr 
                                                           >> 2U)) 
                                                         << 6U)) 
                                                     | ((0x20U 
                                                         & ((~ 
                                                             (vlSelf->io_instr 
                                                              >> 3U)) 
                                                            << 5U)) 
                                                        | ((0x10U 
                                                            & ((~ 
                                                                (vlSelf->io_instr 
                                                                 >> 4U)) 
                                                               << 4U)) 
                                                           | ((8U 
                                                               & (vlSelf->io_instr 
                                                                  >> 2U)) 
                                                              | ((4U 
                                                                  & (vlSelf->io_instr 
                                                                     >> 4U)) 
                                                                 | ((2U 
                                                                     & (vlSelf->io_instr 
                                                                        >> 0xbU)) 
                                                                    | (1U 
                                                                       & (vlSelf->io_instr 
                                                                          >> 0xeU))))))))));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_44 
        = (IData)((0U == (0x6000U & vlSelf->io_instr)));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_40 
        = (IData)((0x4000U == (0x6000U & vlSelf->io_instr)));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_28 
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
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_71 
        = ((2U & ((~ (vlSelf->io_instr >> 0xdU)) << 1U)) 
           | (1U & (vlSelf->io_instr >> 0xeU)));
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
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_8 
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
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_40 
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
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16 
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
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_74 
        = ((2U & (vlSelf->io_instr >> 0xcU)) | (1U 
                                                & (vlSelf->io_instr 
                                                   >> 0xeU)));
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
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_57 
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
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_19 
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
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_64 
        = ((0x20U & ((~ (vlSelf->io_instr >> 0x19U)) 
                     << 5U)) | ((0x10U & ((~ (vlSelf->io_instr 
                                              >> 0x1aU)) 
                                          << 4U)) | 
                                ((8U & ((~ (vlSelf->io_instr 
                                            >> 0x1bU)) 
                                        << 3U)) | (
                                                   (4U 
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
                                                             >> 0x1fU))))))));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_34 
        = (IData)((0U == (0xfe000000U & vlSelf->io_instr)));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_62 
        = ((4U & ((~ (vlSelf->io_instr >> 6U)) << 2U)) 
           | ((2U & ((~ (vlSelf->io_instr >> 0xcU)) 
                     << 1U)) | (1U & (~ (vlSelf->io_instr 
                                         >> 0xeU)))));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_63 
        = ((2U & ((~ (vlSelf->io_instr >> 0xdU)) << 1U)) 
           | (1U & (~ (vlSelf->io_instr >> 0xeU))));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_65 
        = ((0x40U & ((~ (vlSelf->io_instr >> 0x19U)) 
                     << 6U)) | ((0x20U & ((~ (vlSelf->io_instr 
                                              >> 0x1aU)) 
                                          << 5U)) | 
                                ((0x10U & ((~ (vlSelf->io_instr 
                                               >> 0x1bU)) 
                                           << 4U)) 
                                 | ((8U & ((~ (vlSelf->io_instr 
                                               >> 0x1cU)) 
                                           << 3U)) 
                                    | ((4U & ((~ (vlSelf->io_instr 
                                                  >> 0x1dU)) 
                                              << 2U)) 
                                       | ((2U & ((~ 
                                                  (vlSelf->io_instr 
                                                   >> 0x1eU)) 
                                                 << 1U)) 
                                          | (1U & (~ 
                                                   (vlSelf->io_instr 
                                                    >> 0x1fU)))))))));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_45 
        = ((~ (vlSelf->io_instr >> 6U)) & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_44));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_41 
        = ((~ (vlSelf->io_instr >> 0xcU)) & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_40));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_34 
        = ((0x100U & (vlSelf->io_instr << 8U)) | ((0x80U 
                                                   & (vlSelf->io_instr 
                                                      << 6U)) 
                                                  | ((0x40U 
                                                      & ((~ 
                                                          (vlSelf->io_instr 
                                                           >> 2U)) 
                                                         << 6U)) 
                                                     | ((0x20U 
                                                         & ((~ 
                                                             (vlSelf->io_instr 
                                                              >> 3U)) 
                                                            << 5U)) 
                                                        | ((0x10U 
                                                            & ((~ 
                                                                (vlSelf->io_instr 
                                                                 >> 5U)) 
                                                               << 4U)) 
                                                           | ((8U 
                                                               & ((~ 
                                                                   (vlSelf->io_instr 
                                                                    >> 6U)) 
                                                                  << 3U)) 
                                                              | ((4U 
                                                                  & ((~ 
                                                                      (vlSelf->io_instr 
                                                                       >> 0xcU)) 
                                                                     << 2U)) 
                                                                 | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_71))))))));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_44 
        = ((0x200U & (vlSelf->io_instr << 9U)) | ((0x100U 
                                                   & (vlSelf->io_instr 
                                                      << 7U)) 
                                                  | ((0x80U 
                                                      & ((~ 
                                                          (vlSelf->io_instr 
                                                           >> 2U)) 
                                                         << 7U)) 
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
                                                               & ((~ 
                                                                   (vlSelf->io_instr 
                                                                    >> 5U)) 
                                                                  << 4U)) 
                                                              | ((8U 
                                                                  & ((~ 
                                                                      (vlSelf->io_instr 
                                                                       >> 6U)) 
                                                                     << 3U)) 
                                                                 | ((4U 
                                                                     & (vlSelf->io_instr 
                                                                        >> 0xaU)) 
                                                                    | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_71)))))))));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_51 
        = ((0x100U & (vlSelf->io_instr << 8U)) | ((0x80U 
                                                   & (vlSelf->io_instr 
                                                      << 6U)) 
                                                  | ((0x40U 
                                                      & ((~ 
                                                          (vlSelf->io_instr 
                                                           >> 2U)) 
                                                         << 6U)) 
                                                     | ((0x20U 
                                                         & ((~ 
                                                             (vlSelf->io_instr 
                                                              >> 3U)) 
                                                            << 5U)) 
                                                        | ((0x10U 
                                                            & vlSelf->io_instr) 
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
                                                                 | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_74))))))));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_54 
        = ((0x200U & (vlSelf->io_instr << 9U)) | ((0x100U 
                                                   & (vlSelf->io_instr 
                                                      << 7U)) 
                                                  | ((0x80U 
                                                      & ((~ 
                                                          (vlSelf->io_instr 
                                                           >> 2U)) 
                                                         << 7U)) 
                                                     | ((0x40U 
                                                         & ((~ 
                                                             (vlSelf->io_instr 
                                                              >> 3U)) 
                                                            << 6U)) 
                                                        | ((0x20U 
                                                            & (vlSelf->io_instr 
                                                               << 1U)) 
                                                           | ((0x10U 
                                                               & ((~ 
                                                                   (vlSelf->io_instr 
                                                                    >> 5U)) 
                                                                  << 4U)) 
                                                              | ((8U 
                                                                  & ((~ 
                                                                      (vlSelf->io_instr 
                                                                       >> 6U)) 
                                                                     << 3U)) 
                                                                 | ((4U 
                                                                     & (vlSelf->io_instr 
                                                                        >> 0xaU)) 
                                                                    | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_74)))))))));
    vlSelf->core__DOT___decoder_io_out_mem_read_enable 
        = (1U & ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T)) 
                 | (IData)((3U == (0x507fU & vlSelf->io_instr)))));
    if ((0x7fffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_57))) {
        Vcore___024unit____Vdpiimwrap_call_ebreak_TOP____024unit();
    }
    vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src1 
        = (((0x7fU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_8)) 
            | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)) 
               | ((0x7fU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_19)) 
                  | (0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_40)))))
            ? vlSelf->core__DOT__ifu__DOT__pc : vlSelf->core__DOT__reg_0__DOT__casez_tmp);
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_12 
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
                                               & (vlSelf->io_instr 
                                                  << 5U)) 
                                              | ((0x200U 
                                                  & ((~ 
                                                      (vlSelf->io_instr 
                                                       >> 6U)) 
                                                     << 9U)) 
                                                 | ((0x100U 
                                                     & ((~ 
                                                         (vlSelf->io_instr 
                                                          >> 0xcU)) 
                                                        << 8U)) 
                                                    | ((0x80U 
                                                        & ((~ 
                                                            (vlSelf->io_instr 
                                                             >> 0xdU)) 
                                                           << 7U)) 
                                                       | ((0x40U 
                                                           & ((~ 
                                                               (vlSelf->io_instr 
                                                                >> 0xeU)) 
                                                              << 6U)) 
                                                          | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_64)))))))))));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_73 
        = ((0x200U & ((~ (vlSelf->io_instr >> 6U)) 
                      << 9U)) | ((0x100U & (vlSelf->io_instr 
                                            >> 4U)) 
                                 | ((0x80U & ((~ (vlSelf->io_instr 
                                                  >> 0xdU)) 
                                              << 7U)) 
                                    | ((0x40U & (vlSelf->io_instr 
                                                 >> 8U)) 
                                       | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_64)))));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_35 
        = ((~ (vlSelf->io_instr >> 0xeU)) & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_34));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_47 
        = ((vlSelf->io_instr >> 0xeU) & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_34));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_9 
        = ((0x100U & (vlSelf->io_instr << 8U)) | ((0x80U 
                                                   & (vlSelf->io_instr 
                                                      << 6U)) 
                                                  | ((0x40U 
                                                      & ((~ 
                                                          (vlSelf->io_instr 
                                                           >> 2U)) 
                                                         << 6U)) 
                                                     | ((0x20U 
                                                         & ((~ 
                                                             (vlSelf->io_instr 
                                                              >> 3U)) 
                                                            << 5U)) 
                                                        | ((0x10U 
                                                            & ((~ 
                                                                (vlSelf->io_instr 
                                                                 >> 4U)) 
                                                               << 4U)) 
                                                           | ((8U 
                                                               & (vlSelf->io_instr 
                                                                  >> 2U)) 
                                                              | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_62)))))));
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
                                                          | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_62))))));
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
                                                          | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_62))))));
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
                                                             | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_63)))))));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_68 
        = ((4U & (vlSelf->io_instr >> 0xaU)) | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_63));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_67 
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
                                         | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_63))))));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_72 
        = ((0x80U & (vlSelf->io_instr >> 7U)) | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_65));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_69 
        = ((0x200U & ((~ (vlSelf->io_instr >> 6U)) 
                      << 9U)) | ((0x100U & (vlSelf->io_instr 
                                            >> 4U)) 
                                 | ((0x80U & ((~ (vlSelf->io_instr 
                                                  >> 0xdU)) 
                                              << 7U)) 
                                    | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_65))));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_66 
        = ((0x80U & ((~ (vlSelf->io_instr >> 0xeU)) 
                     << 7U)) | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_65));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_45 
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
                                           | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_73))))));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_46 
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
                                              | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_73)))))));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_48 
        = ((~ (vlSelf->io_instr >> 0xdU)) & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_47));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_20 
        = ((0x100U & (vlSelf->io_instr << 8U)) | ((0x80U 
                                                   & (vlSelf->io_instr 
                                                      << 6U)) 
                                                  | ((0x40U 
                                                      & ((~ 
                                                          (vlSelf->io_instr 
                                                           >> 2U)) 
                                                         << 6U)) 
                                                     | ((0x20U 
                                                         & ((~ 
                                                             (vlSelf->io_instr 
                                                              >> 3U)) 
                                                            << 5U)) 
                                                        | ((0x10U 
                                                            & ((~ 
                                                                (vlSelf->io_instr 
                                                                 >> 4U)) 
                                                               << 4U)) 
                                                           | ((8U 
                                                               & ((~ 
                                                                   (vlSelf->io_instr 
                                                                    >> 6U)) 
                                                                  << 3U)) 
                                                              | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_68)))))));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_24 
        = ((0x100U & (vlSelf->io_instr << 8U)) | ((0x80U 
                                                   & (vlSelf->io_instr 
                                                      << 6U)) 
                                                  | ((0x40U 
                                                      & ((~ 
                                                          (vlSelf->io_instr 
                                                           >> 2U)) 
                                                         << 6U)) 
                                                     | ((0x20U 
                                                         & ((~ 
                                                             (vlSelf->io_instr 
                                                              >> 3U)) 
                                                            << 5U)) 
                                                        | ((0x10U 
                                                            & ((~ 
                                                                (vlSelf->io_instr 
                                                                 >> 4U)) 
                                                               << 4U)) 
                                                           | ((8U 
                                                               & (vlSelf->io_instr 
                                                                  >> 2U)) 
                                                              | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_68)))))));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_18 
        = ((0x200U & (vlSelf->io_instr << 9U)) | ((0x100U 
                                                   & (vlSelf->io_instr 
                                                      << 7U)) 
                                                  | ((0x80U 
                                                      & (vlSelf->io_instr 
                                                         << 5U)) 
                                                     | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_67))));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17 
        = ((0x100U & (vlSelf->io_instr << 8U)) | ((0x80U 
                                                   & (vlSelf->io_instr 
                                                      << 6U)) 
                                                  | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_67)));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_38 
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
                                               & (vlSelf->io_instr 
                                                  << 5U)) 
                                              | ((0x200U 
                                                  & ((~ 
                                                      (vlSelf->io_instr 
                                                       >> 6U)) 
                                                     << 9U)) 
                                                 | ((0x100U 
                                                     & ((~ 
                                                         (vlSelf->io_instr 
                                                          >> 0xdU)) 
                                                        << 8U)) 
                                                    | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_72)))))))));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_52 
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
                                               & (vlSelf->io_instr 
                                                  << 5U)) 
                                              | ((0x200U 
                                                  & ((~ 
                                                      (vlSelf->io_instr 
                                                       >> 6U)) 
                                                     << 9U)) 
                                                 | ((0x100U 
                                                     & (vlSelf->io_instr 
                                                        >> 5U)) 
                                                    | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_72)))))))));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_21 
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
                                           | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_69))))));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_22 
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
                                              | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_69)))))));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_23 
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
                                                    >> 6U)) 
                                                  << 0xaU)) 
                                              | ((0x200U 
                                                  & (vlSelf->io_instr 
                                                     >> 3U)) 
                                                 | ((0x100U 
                                                     & ((~ 
                                                         (vlSelf->io_instr 
                                                          >> 0xdU)) 
                                                        << 8U)) 
                                                    | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_66)))))))));
    vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_15 
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
                                               & (vlSelf->io_instr 
                                                  << 5U)) 
                                              | ((0x200U 
                                                  & ((~ 
                                                      (vlSelf->io_instr 
                                                       >> 6U)) 
                                                     << 9U)) 
                                                 | ((0x100U 
                                                     & ((~ 
                                                         (vlSelf->io_instr 
                                                          >> 0xcU)) 
                                                        << 8U)) 
                                                    | (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_66)))))))));
    vlSelf->core__DOT___decoder_io_out_pc_jump = ((0x3ffU 
                                                   == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_18)) 
                                                  | (0x7fU 
                                                     == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_19)));
    vlSelf->core__DOT__reg_0__DOT___GEN = (((0xffU 
                                             == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T)) 
                                            | ((0xffU 
                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1)) 
                                               | ((0xffU 
                                                   == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_3)) 
                                                  | ((0x3fU 
                                                      == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_7)) 
                                                     | ((0xffffU 
                                                         == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_12)) 
                                                        | ((IData)(
                                                                   ((0x33U 
                                                                     == 
                                                                     (0x7fU 
                                                                      & vlSelf->io_instr)) 
                                                                    & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_34))) 
                                                           | ((0x3ffU 
                                                               == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_18)) 
                                                              | ((0x7fU 
                                                                  == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_19)) 
                                                                 | ((0x7fffU 
                                                                     == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_21)) 
                                                                    | ((0xffU 
                                                                        == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_28)) 
                                                                       | ((0x7fffU 
                                                                           == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_45)) 
                                                                          | (0x7fffU 
                                                                             == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_57))))))))))))) 
                                           & (0U != 
                                              (0x1fU 
                                               & (vlSelf->io_instr 
                                                  >> 7U))));
    vlSelf->core__DOT__decoder__DOT__casez_tmp = ((
                                                   (0x3fU 
                                                    == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_7)) 
                                                   | (0x7fU 
                                                      == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_19)))
                                                   ? 
                                                  (((0x1ffU 
                                                     == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_9)) 
                                                    | ((0xffU 
                                                        == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_10)) 
                                                       | (0xffU 
                                                          == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_40))))
                                                    ? 0U
                                                    : 
                                                   (((0xffU 
                                                      == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T)) 
                                                     | ((0xffU 
                                                         == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1)) 
                                                        | ((0xffU 
                                                            == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_3)) 
                                                           | ((0xffU 
                                                               == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)) 
                                                              | ((0x1ffU 
                                                                  == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17)) 
                                                                 | ((0x7fU 
                                                                     == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_19)) 
                                                                    | ((0xffffU 
                                                                        == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_22)) 
                                                                       | ((0xffU 
                                                                           == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_28)) 
                                                                          | ((0xffU 
                                                                              == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_40)) 
                                                                             | ((0xffffU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_46)) 
                                                                                | (0x7fffU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_57))))))))))))
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
                                                  (((0x1ffU 
                                                     == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_9)) 
                                                    | ((0xffU 
                                                        == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_10)) 
                                                       | (0xffU 
                                                          == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_40))))
                                                    ? 
                                                   (((0xffU 
                                                      == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T)) 
                                                     | ((0xffU 
                                                         == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1)) 
                                                        | ((0xffU 
                                                            == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_3)) 
                                                           | ((0xffU 
                                                               == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)) 
                                                              | ((0x1ffU 
                                                                  == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17)) 
                                                                 | ((0x7fU 
                                                                     == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_19)) 
                                                                    | ((0xffffU 
                                                                        == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_22)) 
                                                                       | ((0xffU 
                                                                           == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_28)) 
                                                                          | ((0xffU 
                                                                              == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_40)) 
                                                                             | ((0xffffU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_46)) 
                                                                                | (0x7fffU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_57))))))))))))
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
                                                               == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)) 
                                                              | ((0x1ffU 
                                                                  == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17)) 
                                                                 | ((0x7fU 
                                                                     == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_19)) 
                                                                    | ((0xffffU 
                                                                        == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_22)) 
                                                                       | ((0xffU 
                                                                           == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_28)) 
                                                                          | ((0xffU 
                                                                              == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_40)) 
                                                                             | ((0xffffU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_46)) 
                                                                                | (0x7fffU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_57))))))))))))
                                                     ? 
                                                    (((- (IData)(
                                                                 (vlSelf->io_instr 
                                                                  >> 0x1fU))) 
                                                      << 0xcU) 
                                                     | (vlSelf->io_instr 
                                                        >> 0x14U))
                                                     : 0U)));
    vlSelf->core__DOT___decoder_io_out_branch_type 
        = ((((0x3ffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_44)) 
             | ((0x7fffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_45)) 
                | ((0x1ffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_49)) 
                   | ((0x1ffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_51)) 
                      | ((0xffffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_52)) 
                         | (IData)(((0x63U == (0x7fU 
                                               & vlSelf->io_instr)) 
                                    & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_60)))))))) 
            << 2U) | ((((0x1ffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_20)) 
                        | ((0xffffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_23)) 
                           | ((0x1ffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_24)) 
                              | ((0x1ffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_34)) 
                                 | ((IData)(((0x33U 
                                              == (0x107fU 
                                                  & vlSelf->io_instr)) 
                                             & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_48))) 
                                    | ((IData)(((0x63U 
                                                 == 
                                                 (0x7fU 
                                                  & vlSelf->io_instr)) 
                                                & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_41))) 
                                       | ((0x3ffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_54)) 
                                          | (IData)(
                                                    ((3U 
                                                      == 
                                                      (0xfU 
                                                       & vlSelf->io_instr)) 
                                                     & ((IData)(
                                                                ((0x3030U 
                                                                  == 
                                                                  (0x3070U 
                                                                   & vlSelf->io_instr)) 
                                                                 & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_47))) 
                                                        | (IData)(
                                                                  ((0x1060U 
                                                                    == 
                                                                    (0x1070U 
                                                                     & vlSelf->io_instr)) 
                                                                   & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_60))))))))))))) 
                       << 1U) | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1)) 
                                 | ((IData)(((3U == 
                                              (0x105fU 
                                               & vlSelf->io_instr)) 
                                             & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_44))) 
                                    | ((0xffffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_12)) 
                                       | ((0x1ffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17)) 
                                          | ((IData)(
                                                     ((0x13U 
                                                       == 
                                                       (0x7fU 
                                                        & vlSelf->io_instr)) 
                                                      & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_61))) 
                                             | ((IData)(
                                                        ((0x33U 
                                                          == 
                                                          (0x107fU 
                                                           & vlSelf->io_instr)) 
                                                         & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_47))) 
                                                | ((IData)(
                                                           ((0x63U 
                                                             == 
                                                             (0x7fU 
                                                              & vlSelf->io_instr)) 
                                                            & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_61))) 
                                                   | (0x7fffU 
                                                      == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_57)))))))))));
    vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_58 
        = ((0x1ffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_20)) 
           | ((0xffffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_23)) 
              | ((0x1ffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_24)) 
                 | ((IData)(((3U == (0x1fU & vlSelf->io_instr)) 
                             & (0xfU == (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_70)))) 
                    | ((IData)(((3U == (0x2fU & vlSelf->io_instr)) 
                                & (0xfU == (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_70)))) 
                       | (IData)(((0x2033U == (0x307fU 
                                               & vlSelf->io_instr)) 
                                  & (0xffU == (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_66)))))))));
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
            << 3U) | ((((0x7fffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_21)) 
                        | ((0x1ffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_51)) 
                           | (0xffffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_52)))) 
                       << 2U) | ((((0x7fffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_21)) 
                                   | ((IData)(((0x1033U 
                                                == 
                                                (0x107fU 
                                                 & vlSelf->io_instr)) 
                                               & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_35))) 
                                      | ((IData)(((0x1013U 
                                                   == 
                                                   (0x107fU 
                                                    & vlSelf->io_instr)) 
                                                  & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_33))) 
                                         | ((IData)(
                                                    ((0x13U 
                                                      == 
                                                      (0x7fU 
                                                       & vlSelf->io_instr)) 
                                                     & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_41))) 
                                            | ((0xffffU 
                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_38)) 
                                               | (IData)(
                                                         ((0x33U 
                                                           == 
                                                           (0x707fU 
                                                            & vlSelf->io_instr)) 
                                                          & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_36)))))))) 
                                  << 1U) | ((0xffU 
                                             == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T)) 
                                            | ((0xffU 
                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1)) 
                                               | ((0xffU 
                                                   == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_2)) 
                                                  | ((0xffU 
                                                      == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_3)) 
                                                     | ((IData)(
                                                                ((3U 
                                                                  == 
                                                                  (0x1fU 
                                                                   & vlSelf->io_instr)) 
                                                                 & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_45))) 
                                                        | ((0x7fU 
                                                            == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_8)) 
                                                           | ((IData)(
                                                                      ((0x33U 
                                                                        == 
                                                                        (0x307fU 
                                                                         & vlSelf->io_instr)) 
                                                                       & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_34))) 
                                                              | ((0xffffU 
                                                                  == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_15)) 
                                                                 | ((0xffU 
                                                                     == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)) 
                                                                    | ((0x1ffU 
                                                                        == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17)) 
                                                                       | ((0x7fU 
                                                                           == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_19)) 
                                                                          | ((IData)(
                                                                                ((0x1013U 
                                                                                == 
                                                                                (0x105fU 
                                                                                & vlSelf->io_instr)) 
                                                                                & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_48))) 
                                                                             | ((IData)(
                                                                                ((0x1033U 
                                                                                == 
                                                                                (0x107fU 
                                                                                & vlSelf->io_instr)) 
                                                                                & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_47))) 
                                                                                | ((0x1ffU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_49)) 
                                                                                | (0x3ffU 
                                                                                == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_54)))))))))))))))))));
    vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src2 
        = (((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T)) 
            | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1)) 
               | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_2)) 
                  | ((0x7fU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_8)) 
                     | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_10)) 
                        | ((0x1ffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17)) 
                           | ((0x7fU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_19)) 
                              | ((0xffffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_22)) 
                                 | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_28)) 
                                    | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_40)) 
                                       | ((0xffffU 
                                           == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_46)) 
                                          | (0x7fffU 
                                             == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_57)))))))))))))
            ? vlSelf->core__DOT__decoder__DOT__casez_tmp
            : vlSelf->core__DOT__reg_0__DOT__casez_tmp);
    vlSelf->core__DOT__exu__DOT__comp__DOT___io_result_T_18 
        = (1U == (IData)(vlSelf->core__DOT___decoder_io_out_branch_type));
    vlSelf->core__DOT___decoder_io_out_mem_read_type 
        = ((((IData)(((3U == (0x7fU & vlSelf->io_instr)) 
                      & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_40))) 
             | ((0x1ffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_34)) 
                | ((0xffffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_38)) 
                   | ((IData)(((0x63U == (0x7fU & vlSelf->io_instr)) 
                               & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_40))) 
                      | (0x7fffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_45)))))) 
            << 2U) | (((IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_58) 
                       << 1U) | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_2)) 
                                 | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_3)) 
                                    | ((0xffffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_12)) 
                                       | ((0xffffU 
                                           == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_15)) 
                                          | ((0x1ffU 
                                              == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17)) 
                                             | ((0x3ffU 
                                                 == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_44)) 
                                                | ((0x7fffU 
                                                    == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_45)) 
                                                   | ((IData)(
                                                              ((0x1063U 
                                                                == 
                                                                (0x107fU 
                                                                 & vlSelf->io_instr)) 
                                                               & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_40))) 
                                                      | (0x7fffU 
                                                         == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_57))))))))))));
    vlSelf->core__DOT___decoder_io_out_mem_write_type 
        = (((IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_58) 
            << 1U) | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_2)) 
                      | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_3)) 
                         | ((0xffffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_12)) 
                            | ((0xffffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_15)) 
                               | ((0x1ffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17)) 
                                  | (0x7fffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_57))))))));
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
    vlSelf->io_value = ((IData)(vlSelf->core__DOT___decoder_io_out_pc_jump)
                         ? ((IData)(4U) + vlSelf->core__DOT__ifu__DOT__pc)
                         : vlSelf->core__DOT__exu__DOT__alu__DOT__casez_tmp);
    if (vlSelf->core__DOT___decoder_io_out_mem_read_enable) {
        Vcore___024unit____Vdpiimwrap_pmem_read_TOP____024unit(vlSelf->core__DOT__exu__DOT__alu__DOT__casez_tmp, vlSelf->__Vfunc_pmem_read__1__Vfuncout);
        vlSelf->core__DOT__exu__DOT___mem_read_data 
            = vlSelf->__Vfunc_pmem_read__1__Vfuncout;
    }
    if (((0x1ffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_9)) 
         | (IData)(((0x23U == (0x3fU & vlSelf->io_instr)) 
                    & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_45))))) {
        Vcore___024unit____Vdpiimwrap_pmem_write_TOP____024unit(vlSelf->core__DOT__exu__DOT__alu__DOT__casez_tmp, vlSelf->core__DOT__reg_0__DOT__casez_tmp, 
                                                                ((0U 
                                                                  == (IData)(vlSelf->core__DOT___decoder_io_out_mem_write_type))
                                                                  ? 0U
                                                                  : 
                                                                 ((1U 
                                                                   == (IData)(vlSelf->core__DOT___decoder_io_out_mem_write_type))
                                                                   ? 3U
                                                                   : 
                                                                  ((2U 
                                                                    == (IData)(vlSelf->core__DOT___decoder_io_out_mem_write_type))
                                                                    ? 0xfU
                                                                    : 0xffU))));
    } else {
        vlSelf->core__DOT__exu__DOT___mem_read_data = 0U;
    }
    vlSelf->core__DOT__exu__DOT___mem_read_result_sint_T_19 
        = (0xffffU & ((2U == (IData)(vlSelf->core__DOT___decoder_io_out_mem_read_type))
                       ? vlSelf->core__DOT__exu__DOT___mem_read_data
                       : ((0xff00U & ((- (IData)(((1U 
                                                   == (IData)(vlSelf->core__DOT___decoder_io_out_mem_read_type)) 
                                                  & (vlSelf->core__DOT__exu__DOT___mem_read_data 
                                                     >> 7U)))) 
                                      << 8U)) | ((1U 
                                                  == (IData)(vlSelf->core__DOT___decoder_io_out_mem_read_type))
                                                  ? 
                                                 (0xffU 
                                                  & vlSelf->core__DOT__exu__DOT___mem_read_data)
                                                  : 0U))));
    vlSelf->core__DOT___exu_io_out_n_pc = (((IData)(vlSelf->core__DOT___decoder_io_out_pc_jump) 
                                            | (((4U 
                                                 & (IData)(vlSelf->core__DOT___decoder_io_out_branch_type))
                                                 ? 
                                                ((2U 
                                                  & (IData)(vlSelf->core__DOT___decoder_io_out_branch_type))
                                                  ? 
                                                 ((1U 
                                                   & (~ (IData)(vlSelf->core__DOT___decoder_io_out_branch_type))) 
                                                  || (IData)(vlSelf->core__DOT__exu__DOT__comp__DOT___io_result_T_18))
                                                  : 
                                                 (~ (IData)(vlSelf->core__DOT___decoder_io_out_branch_type)))
                                                 : 
                                                ((1U 
                                                  & (~ 
                                                     ((IData)(vlSelf->core__DOT___decoder_io_out_branch_type) 
                                                      >> 1U))) 
                                                 && (IData)(vlSelf->core__DOT__exu__DOT__comp__DOT___io_result_T_18))) 
                                               & ((0xffU 
                                                   == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)) 
                                                  | (0xffU 
                                                     == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_40)))))
                                            ? ((IData)(vlSelf->core__DOT___decoder_io_out_mem_read_enable)
                                                ? (
                                                   (5U 
                                                    == (IData)(vlSelf->core__DOT___decoder_io_out_mem_read_type))
                                                    ? 
                                                   (0xffffU 
                                                    & vlSelf->core__DOT__exu__DOT___mem_read_data)
                                                    : 
                                                   ((4U 
                                                     == (IData)(vlSelf->core__DOT___decoder_io_out_mem_read_type))
                                                     ? 
                                                    (0xffU 
                                                     & vlSelf->core__DOT__exu__DOT___mem_read_data)
                                                     : 
                                                    ((3U 
                                                      == (IData)(vlSelf->core__DOT___decoder_io_out_mem_read_type))
                                                      ? vlSelf->core__DOT__exu__DOT___mem_read_data
                                                      : 
                                                     (((- (IData)(
                                                                  (1U 
                                                                   & ((IData)(vlSelf->core__DOT__exu__DOT___mem_read_result_sint_T_19) 
                                                                      >> 0xfU)))) 
                                                       << 0x10U) 
                                                      | (IData)(vlSelf->core__DOT__exu__DOT___mem_read_result_sint_T_19)))))
                                                : vlSelf->core__DOT__exu__DOT__alu__DOT__casez_tmp)
                                            : ((IData)(4U) 
                                               + vlSelf->core__DOT__ifu__DOT__pc));
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

VL_INLINE_OPT void Vcore___024root___nba_sequent__TOP__0(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___nba_sequent__TOP__0\n"); );
    // Body
    if (vlSelf->reset) {
        vlSelf->core__DOT__ifu__DOT__pc = 0x80000000U;
        vlSelf->core__DOT__reg_0__DOT__regs_11 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_10 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_9 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_7 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_6 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_4 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_2 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_1 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_0 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_8 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_12 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_13 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_3 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_14 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_15 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_5 = 0U;
    } else {
        vlSelf->core__DOT__ifu__DOT__pc = vlSelf->core__DOT___exu_io_out_n_pc;
        if (((IData)(vlSelf->core__DOT__reg_0__DOT___GEN) 
             & (0x580U == (0x780U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_11 
                = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT__reg_0__DOT___GEN) 
             & (0x500U == (0x780U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_10 
                = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT__reg_0__DOT___GEN) 
             & (0x480U == (0x780U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_9 = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT__reg_0__DOT___GEN) 
             & (0x380U == (0x780U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_7 = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT__reg_0__DOT___GEN) 
             & (0x300U == (0x780U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_6 = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT__reg_0__DOT___GEN) 
             & (0x200U == (0x780U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_4 = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT__reg_0__DOT___GEN) 
             & (0x100U == (0x780U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_2 = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT__reg_0__DOT___GEN) 
             & (0x80U == (0x780U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_1 = vlSelf->io_value;
        }
        vlSelf->core__DOT__reg_0__DOT__regs_0 = (((IData)(vlSelf->core__DOT__reg_0__DOT___GEN) 
                                                  & (0U 
                                                     == 
                                                     (0x780U 
                                                      & vlSelf->io_instr)))
                                                  ? vlSelf->io_value
                                                  : 0U);
        if (((IData)(vlSelf->core__DOT__reg_0__DOT___GEN) 
             & (0x400U == (0x780U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_8 = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT__reg_0__DOT___GEN) 
             & (0x600U == (0x780U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_12 
                = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT__reg_0__DOT___GEN) 
             & (0x680U == (0x780U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_13 
                = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT__reg_0__DOT___GEN) 
             & (0x180U == (0x780U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_3 = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT__reg_0__DOT___GEN) 
             & (0x700U == (0x780U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_14 
                = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT__reg_0__DOT___GEN) 
             & (0x780U == (0x780U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_15 
                = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT__reg_0__DOT___GEN) 
             & (0x280U == (0x780U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_5 = vlSelf->io_value;
        }
    }
    vlSelf->io_pc = vlSelf->core__DOT__ifu__DOT__pc;
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
    vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src1 
        = (((0x7fU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_8)) 
            | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)) 
               | ((0x7fU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_19)) 
                  | (0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_40)))))
            ? vlSelf->core__DOT__ifu__DOT__pc : vlSelf->core__DOT__reg_0__DOT__casez_tmp);
    vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src2 
        = (((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T)) 
            | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1)) 
               | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_2)) 
                  | ((0x7fU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_8)) 
                     | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_10)) 
                        | ((0x1ffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_17)) 
                           | ((0x7fU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_19)) 
                              | ((0xffffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_22)) 
                                 | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_28)) 
                                    | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_40)) 
                                       | ((0xffffU 
                                           == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_46)) 
                                          | (0x7fffU 
                                             == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_57)))))))))))))
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
    vlSelf->io_value = ((IData)(vlSelf->core__DOT___decoder_io_out_pc_jump)
                         ? ((IData)(4U) + vlSelf->core__DOT__ifu__DOT__pc)
                         : vlSelf->core__DOT__exu__DOT__alu__DOT__casez_tmp);
    if (vlSelf->core__DOT___decoder_io_out_mem_read_enable) {
        Vcore___024unit____Vdpiimwrap_pmem_read_TOP____024unit(vlSelf->core__DOT__exu__DOT__alu__DOT__casez_tmp, vlSelf->__Vfunc_pmem_read__1__Vfuncout);
        vlSelf->core__DOT__exu__DOT___mem_read_data 
            = vlSelf->__Vfunc_pmem_read__1__Vfuncout;
    }
    if (((0x1ffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_9)) 
         | (IData)(((0x23U == (0x3fU & vlSelf->io_instr)) 
                    & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_45))))) {
        Vcore___024unit____Vdpiimwrap_pmem_write_TOP____024unit(vlSelf->core__DOT__exu__DOT__alu__DOT__casez_tmp, vlSelf->core__DOT__reg_0__DOT__casez_tmp, 
                                                                ((0U 
                                                                  == (IData)(vlSelf->core__DOT___decoder_io_out_mem_write_type))
                                                                  ? 0U
                                                                  : 
                                                                 ((1U 
                                                                   == (IData)(vlSelf->core__DOT___decoder_io_out_mem_write_type))
                                                                   ? 3U
                                                                   : 
                                                                  ((2U 
                                                                    == (IData)(vlSelf->core__DOT___decoder_io_out_mem_write_type))
                                                                    ? 0xfU
                                                                    : 0xffU))));
    } else {
        vlSelf->core__DOT__exu__DOT___mem_read_data = 0U;
    }
    vlSelf->core__DOT__exu__DOT___mem_read_result_sint_T_19 
        = (0xffffU & ((2U == (IData)(vlSelf->core__DOT___decoder_io_out_mem_read_type))
                       ? vlSelf->core__DOT__exu__DOT___mem_read_data
                       : ((0xff00U & ((- (IData)(((1U 
                                                   == (IData)(vlSelf->core__DOT___decoder_io_out_mem_read_type)) 
                                                  & (vlSelf->core__DOT__exu__DOT___mem_read_data 
                                                     >> 7U)))) 
                                      << 8U)) | ((1U 
                                                  == (IData)(vlSelf->core__DOT___decoder_io_out_mem_read_type))
                                                  ? 
                                                 (0xffU 
                                                  & vlSelf->core__DOT__exu__DOT___mem_read_data)
                                                  : 0U))));
    vlSelf->core__DOT___exu_io_out_n_pc = (((IData)(vlSelf->core__DOT___decoder_io_out_pc_jump) 
                                            | (((4U 
                                                 & (IData)(vlSelf->core__DOT___decoder_io_out_branch_type))
                                                 ? 
                                                ((2U 
                                                  & (IData)(vlSelf->core__DOT___decoder_io_out_branch_type))
                                                  ? 
                                                 ((1U 
                                                   & (~ (IData)(vlSelf->core__DOT___decoder_io_out_branch_type))) 
                                                  || (IData)(vlSelf->core__DOT__exu__DOT__comp__DOT___io_result_T_18))
                                                  : 
                                                 (~ (IData)(vlSelf->core__DOT___decoder_io_out_branch_type)))
                                                 : 
                                                ((1U 
                                                  & (~ 
                                                     ((IData)(vlSelf->core__DOT___decoder_io_out_branch_type) 
                                                      >> 1U))) 
                                                 && (IData)(vlSelf->core__DOT__exu__DOT__comp__DOT___io_result_T_18))) 
                                               & ((0xffU 
                                                   == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)) 
                                                  | (0xffU 
                                                     == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_40)))))
                                            ? ((IData)(vlSelf->core__DOT___decoder_io_out_mem_read_enable)
                                                ? (
                                                   (5U 
                                                    == (IData)(vlSelf->core__DOT___decoder_io_out_mem_read_type))
                                                    ? 
                                                   (0xffffU 
                                                    & vlSelf->core__DOT__exu__DOT___mem_read_data)
                                                    : 
                                                   ((4U 
                                                     == (IData)(vlSelf->core__DOT___decoder_io_out_mem_read_type))
                                                     ? 
                                                    (0xffU 
                                                     & vlSelf->core__DOT__exu__DOT___mem_read_data)
                                                     : 
                                                    ((3U 
                                                      == (IData)(vlSelf->core__DOT___decoder_io_out_mem_read_type))
                                                      ? vlSelf->core__DOT__exu__DOT___mem_read_data
                                                      : 
                                                     (((- (IData)(
                                                                  (1U 
                                                                   & ((IData)(vlSelf->core__DOT__exu__DOT___mem_read_result_sint_T_19) 
                                                                      >> 0xfU)))) 
                                                       << 0x10U) 
                                                      | (IData)(vlSelf->core__DOT__exu__DOT___mem_read_result_sint_T_19)))))
                                                : vlSelf->core__DOT__exu__DOT__alu__DOT__casez_tmp)
                                            : ((IData)(4U) 
                                               + vlSelf->core__DOT__ifu__DOT__pc));
}
