// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcore.h for the primary calling header

#include "Vcore__pch.h"
#include "Vcore___024root.h"

void Vcore___024root___ico_sequent__TOP__0(Vcore___024root* vlSelf);

void Vcore___024root___eval_ico(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___eval_ico\n"); );
    // Body
    if ((1ULL & vlSelf->__VicoTriggered.word(0U))) {
        Vcore___024root___ico_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[1U] = 1U;
    }
}

void Vcore___024root___eval_triggers__ico(Vcore___024root* vlSelf);

bool Vcore___024root___eval_phase__ico(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___eval_phase__ico\n"); );
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vcore___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelf->__VicoTriggered.any();
    if (__VicoExecute) {
        Vcore___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vcore___024root___eval_act(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___eval_act\n"); );
}

void Vcore___024root___nba_sequent__TOP__0(Vcore___024root* vlSelf);

void Vcore___024root___eval_nba(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___eval_nba\n"); );
    // Body
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vcore___024root___nba_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
}

VL_INLINE_OPT void Vcore___024root___nba_sequent__TOP__0(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___nba_sequent__TOP__0\n"); );
    // Body
    if (vlSelf->reset) {
        vlSelf->core__DOT__ifu__DOT__pc = 0x80000000U;
        vlSelf->core__DOT__reg_0__DOT__regs_27 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_26 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_25 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_24 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_23 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_22 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_21 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_20 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_19 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_18 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_17 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_16 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_15 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_14 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_13 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_12 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_8 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_0 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_2 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_4 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_1 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_5 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_6 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_3 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_9 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_10 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_7 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_11 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_28 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_29 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_30 = 0U;
        vlSelf->core__DOT__reg_0__DOT__regs_31 = 0U;
    } else {
        vlSelf->core__DOT__ifu__DOT__pc = vlSelf->core__DOT___exu_io_out_n_pc;
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0xd80U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_27 
                = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0xd00U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_26 
                = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0xc80U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_25 
                = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0xc00U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_24 
                = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0xb80U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_23 
                = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0xb00U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_22 
                = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0xa80U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_21 
                = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0xa00U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_20 
                = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0x980U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_19 
                = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0x900U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_18 
                = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0x880U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_17 
                = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0x800U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_16 
                = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0x780U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_15 
                = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0x700U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_14 
                = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0x680U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_13 
                = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0x600U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_12 
                = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0x400U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_8 = vlSelf->io_value;
        }
        vlSelf->core__DOT__reg_0__DOT__regs_0 = (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
                                                  & (0U 
                                                     == 
                                                     (0xf80U 
                                                      & vlSelf->io_instr)))
                                                  ? vlSelf->io_value
                                                  : 0U);
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0x100U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_2 = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0x200U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_4 = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0x80U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_1 = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0x280U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_5 = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0x300U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_6 = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0x180U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_3 = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0x480U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_9 = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0x500U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_10 
                = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0x380U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_7 = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0x580U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_11 
                = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0xe00U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_28 
                = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0xe80U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_29 
                = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0xf00U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_30 
                = vlSelf->io_value;
        }
        if (((IData)(vlSelf->core__DOT___decoder_io_out_reg_write_enable) 
             & (0xf80U == (0xf80U & vlSelf->io_instr)))) {
            vlSelf->core__DOT__reg_0__DOT__regs_31 
                = vlSelf->io_value;
        }
    }
    vlSelf->io_pc = vlSelf->core__DOT__ifu__DOT__pc;
    vlSelf->core__DOT__reg_0__DOT__casez_tmp = ((0x80000U 
                                                 & vlSelf->io_instr)
                                                 ? 
                                                ((0x40000U 
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
                                                     ? vlSelf->core__DOT__reg_0__DOT__regs_31
                                                     : vlSelf->core__DOT__reg_0__DOT__regs_30)
                                                    : 
                                                   ((0x8000U 
                                                     & vlSelf->io_instr)
                                                     ? vlSelf->core__DOT__reg_0__DOT__regs_29
                                                     : vlSelf->core__DOT__reg_0__DOT__regs_28))
                                                   : 
                                                  ((0x10000U 
                                                    & vlSelf->io_instr)
                                                    ? 
                                                   ((0x8000U 
                                                     & vlSelf->io_instr)
                                                     ? vlSelf->core__DOT__reg_0__DOT__regs_27
                                                     : vlSelf->core__DOT__reg_0__DOT__regs_26)
                                                    : 
                                                   ((0x8000U 
                                                     & vlSelf->io_instr)
                                                     ? vlSelf->core__DOT__reg_0__DOT__regs_25
                                                     : vlSelf->core__DOT__reg_0__DOT__regs_24)))
                                                  : 
                                                 ((0x20000U 
                                                   & vlSelf->io_instr)
                                                   ? 
                                                  ((0x10000U 
                                                    & vlSelf->io_instr)
                                                    ? 
                                                   ((0x8000U 
                                                     & vlSelf->io_instr)
                                                     ? vlSelf->core__DOT__reg_0__DOT__regs_23
                                                     : vlSelf->core__DOT__reg_0__DOT__regs_22)
                                                    : 
                                                   ((0x8000U 
                                                     & vlSelf->io_instr)
                                                     ? vlSelf->core__DOT__reg_0__DOT__regs_21
                                                     : vlSelf->core__DOT__reg_0__DOT__regs_20))
                                                   : 
                                                  ((0x10000U 
                                                    & vlSelf->io_instr)
                                                    ? 
                                                   ((0x8000U 
                                                     & vlSelf->io_instr)
                                                     ? vlSelf->core__DOT__reg_0__DOT__regs_19
                                                     : vlSelf->core__DOT__reg_0__DOT__regs_18)
                                                    : 
                                                   ((0x8000U 
                                                     & vlSelf->io_instr)
                                                     ? vlSelf->core__DOT__reg_0__DOT__regs_17
                                                     : vlSelf->core__DOT__reg_0__DOT__regs_16))))
                                                 : 
                                                ((0x40000U 
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
                                                     : vlSelf->core__DOT__reg_0__DOT__regs_0)))));
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

void Vcore___024root___eval_triggers__act(Vcore___024root* vlSelf);

bool Vcore___024root___eval_phase__act(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vcore___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vcore___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vcore___024root___eval_phase__nba(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vcore___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcore___024root___dump_triggers__ico(Vcore___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vcore___024root___dump_triggers__nba(Vcore___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vcore___024root___dump_triggers__act(Vcore___024root* vlSelf);
#endif  // VL_DEBUG

void Vcore___024root___eval(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelf->__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY((0x64U < __VicoIterCount))) {
#ifdef VL_DEBUG
            Vcore___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("build/core.sv", 698, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vcore___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelf->__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vcore___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("build/core.sv", 698, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vcore___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("build/core.sv", 698, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vcore___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vcore___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vcore___024root___eval_debug_assertions(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clock & 0xfeU))) {
        Verilated::overWidthError("clock");}
    if (VL_UNLIKELY((vlSelf->reset & 0xfeU))) {
        Verilated::overWidthError("reset");}
}
#endif  // VL_DEBUG
