// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcore.h for the primary calling header

#include "Vcore__pch.h"
#include "Vcore___024root.h"

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
        vlSelf->__Vm_traceActivity[1U] = 1U;
    }
}

extern const VlUnpacked<CData/*2:0*/, 8> Vcore__ConstPool__TABLE_hf9010b7d_0;

VL_INLINE_OPT void Vcore___024root___nba_sequent__TOP__0(Vcore___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root___nba_sequent__TOP__0\n"); );
    // Init
    CData/*2:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    IData/*31:0*/ __Vdly__core__DOT__pc;
    __Vdly__core__DOT__pc = 0;
    // Body
    __Vdly__core__DOT__pc = vlSelf->core__DOT__pc;
    if (vlSelf->reset) {
        __Vdly__core__DOT__pc = 0x80000000U;
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
        vlSelf->core__DOT__state = 0U;
    } else {
        if ((1U & (~ (((((0U == (IData)(vlSelf->core__DOT__state)) 
                         | (1U == (IData)(vlSelf->core__DOT__state))) 
                        | (2U == (IData)(vlSelf->core__DOT__state))) 
                       | (3U == (IData)(vlSelf->core__DOT__state))) 
                      | (4U != (IData)(vlSelf->core__DOT__state)))))) {
            __Vdly__core__DOT__pc = ((IData)(4U) + vlSelf->core__DOT__pc);
        }
        if ((0x1bU == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_27 
                = vlSelf->core__DOT__res;
        }
        if ((0x1aU == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_26 
                = vlSelf->core__DOT__res;
        }
        if ((0x19U == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_25 
                = vlSelf->core__DOT__res;
        }
        if ((0x18U == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_24 
                = vlSelf->core__DOT__res;
        }
        if ((0x17U == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_23 
                = vlSelf->core__DOT__res;
        }
        if ((0x16U == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_22 
                = vlSelf->core__DOT__res;
        }
        if ((0x15U == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_21 
                = vlSelf->core__DOT__res;
        }
        if ((0x14U == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_20 
                = vlSelf->core__DOT__res;
        }
        if ((0x13U == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_19 
                = vlSelf->core__DOT__res;
        }
        if ((0x12U == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_18 
                = vlSelf->core__DOT__res;
        }
        if ((0x11U == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_17 
                = vlSelf->core__DOT__res;
        }
        if ((0x10U == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_16 
                = vlSelf->core__DOT__res;
        }
        if ((0xfU == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_15 
                = vlSelf->core__DOT__res;
        }
        if ((0xeU == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_14 
                = vlSelf->core__DOT__res;
        }
        if ((0xdU == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_13 
                = vlSelf->core__DOT__res;
        }
        if ((0xcU == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_12 
                = vlSelf->core__DOT__res;
        }
        if ((8U == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_8 = vlSelf->core__DOT__res;
        }
        if ((0U == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_0 = vlSelf->core__DOT__res;
        }
        if ((2U == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_2 = vlSelf->core__DOT__res;
        }
        if ((4U == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_4 = vlSelf->core__DOT__res;
        }
        if ((1U == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_1 = vlSelf->core__DOT__res;
        }
        if ((5U == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_5 = vlSelf->core__DOT__res;
        }
        if ((6U == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_6 = vlSelf->core__DOT__res;
        }
        if ((3U == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_3 = vlSelf->core__DOT__res;
        }
        if ((9U == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_9 = vlSelf->core__DOT__res;
        }
        if ((0xaU == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_10 
                = vlSelf->core__DOT__res;
        }
        if ((7U == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_7 = vlSelf->core__DOT__res;
        }
        if ((0xbU == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_11 
                = vlSelf->core__DOT__res;
        }
        if ((0x1cU == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_28 
                = vlSelf->core__DOT__res;
        }
        if ((0x1dU == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_29 
                = vlSelf->core__DOT__res;
        }
        if ((0x1eU == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_30 
                = vlSelf->core__DOT__res;
        }
        if ((0x1fU == (IData)(vlSelf->core__DOT__rd))) {
            vlSelf->core__DOT__reg_0__DOT__regs_31 
                = vlSelf->core__DOT__res;
        }
        vlSelf->core__DOT__state = vlSelf->core__DOT__casez_tmp;
    }
    vlSelf->core__DOT__rs1 = (0x1fU & (vlSelf->io_instr 
                                       >> 0xfU));
    vlSelf->core__DOT__pc = __Vdly__core__DOT__pc;
    vlSelf->io_pc = vlSelf->core__DOT__pc;
    vlSelf->core__DOT__rd = (0x1fU & (vlSelf->io_instr 
                                      >> 7U));
    vlSelf->core__DOT__res = ((IData)(vlSelf->core__DOT__addi)
                               ? (vlSelf->core__DOT__immI 
                                  + vlSelf->core__DOT__src1)
                               : 0U);
    __Vtableidx1 = vlSelf->core__DOT__state;
    vlSelf->core__DOT__casez_tmp = Vcore__ConstPool__TABLE_hf9010b7d_0
        [__Vtableidx1];
    vlSelf->io_value = vlSelf->core__DOT__res;
    vlSelf->core__DOT__addi = (0x13U == ((0x380U & 
                                          (vlSelf->io_instr 
                                           >> 5U)) 
                                         | (0x7fU & vlSelf->io_instr)));
    vlSelf->core__DOT__immI = VL_SHIFTR_III(32,32,32, vlSelf->io_instr, 0x14U);
    vlSelf->core__DOT__src1 = vlSelf->core__DOT__reg_0__DOT__casez_tmp;
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
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vcore___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("build/core.sv", 343, "", "NBA region did not converge.");
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
                VL_FATAL_MT("build/core.sv", 343, "", "Active region did not converge.");
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
