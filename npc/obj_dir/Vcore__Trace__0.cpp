// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vcore__Syms.h"


void Vcore___024root__trace_chg_0_sub_0(Vcore___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vcore___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root__trace_chg_0\n"); );
    // Init
    Vcore___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vcore___024root*>(voidSelf);
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vcore___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vcore___024root__trace_chg_0_sub_0(Vcore___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    (void)vlSelf;  // Prevent unused variable warning
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root__trace_chg_0_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[1U])) {
        bufp->chgIData(oldp+0,(vlSelf->core__DOT__pc),32);
        bufp->chgIData(oldp+1,(vlSelf->core__DOT__immI),32);
        bufp->chgCData(oldp+2,(vlSelf->core__DOT__rs1),5);
        bufp->chgCData(oldp+3,(vlSelf->core__DOT__rd),5);
        bufp->chgBit(oldp+4,(vlSelf->core__DOT__addi));
        bufp->chgIData(oldp+5,(vlSelf->core__DOT__src1),32);
        bufp->chgIData(oldp+6,(vlSelf->core__DOT__res),32);
        bufp->chgIData(oldp+7,(((IData)(vlSelf->core__DOT__addi)
                                 ? (vlSelf->core__DOT__immI 
                                    + vlSelf->core__DOT__src1)
                                 : 0U)),32);
        bufp->chgIData(oldp+8,(vlSelf->core__DOT__reg_0__DOT__casez_tmp),32);
        bufp->chgIData(oldp+9,(vlSelf->core__DOT__reg_0__DOT__regs_0),32);
        bufp->chgIData(oldp+10,(vlSelf->core__DOT__reg_0__DOT__regs_1),32);
        bufp->chgIData(oldp+11,(vlSelf->core__DOT__reg_0__DOT__regs_2),32);
        bufp->chgIData(oldp+12,(vlSelf->core__DOT__reg_0__DOT__regs_3),32);
        bufp->chgIData(oldp+13,(vlSelf->core__DOT__reg_0__DOT__regs_4),32);
        bufp->chgIData(oldp+14,(vlSelf->core__DOT__reg_0__DOT__regs_5),32);
        bufp->chgIData(oldp+15,(vlSelf->core__DOT__reg_0__DOT__regs_6),32);
        bufp->chgIData(oldp+16,(vlSelf->core__DOT__reg_0__DOT__regs_7),32);
        bufp->chgIData(oldp+17,(vlSelf->core__DOT__reg_0__DOT__regs_8),32);
        bufp->chgIData(oldp+18,(vlSelf->core__DOT__reg_0__DOT__regs_9),32);
        bufp->chgIData(oldp+19,(vlSelf->core__DOT__reg_0__DOT__regs_10),32);
        bufp->chgIData(oldp+20,(vlSelf->core__DOT__reg_0__DOT__regs_11),32);
        bufp->chgIData(oldp+21,(vlSelf->core__DOT__reg_0__DOT__regs_12),32);
        bufp->chgIData(oldp+22,(vlSelf->core__DOT__reg_0__DOT__regs_13),32);
        bufp->chgIData(oldp+23,(vlSelf->core__DOT__reg_0__DOT__regs_14),32);
        bufp->chgIData(oldp+24,(vlSelf->core__DOT__reg_0__DOT__regs_15),32);
        bufp->chgIData(oldp+25,(vlSelf->core__DOT__reg_0__DOT__regs_16),32);
        bufp->chgIData(oldp+26,(vlSelf->core__DOT__reg_0__DOT__regs_17),32);
        bufp->chgIData(oldp+27,(vlSelf->core__DOT__reg_0__DOT__regs_18),32);
        bufp->chgIData(oldp+28,(vlSelf->core__DOT__reg_0__DOT__regs_19),32);
        bufp->chgIData(oldp+29,(vlSelf->core__DOT__reg_0__DOT__regs_20),32);
        bufp->chgIData(oldp+30,(vlSelf->core__DOT__reg_0__DOT__regs_21),32);
        bufp->chgIData(oldp+31,(vlSelf->core__DOT__reg_0__DOT__regs_22),32);
        bufp->chgIData(oldp+32,(vlSelf->core__DOT__reg_0__DOT__regs_23),32);
        bufp->chgIData(oldp+33,(vlSelf->core__DOT__reg_0__DOT__regs_24),32);
        bufp->chgIData(oldp+34,(vlSelf->core__DOT__reg_0__DOT__regs_25),32);
        bufp->chgIData(oldp+35,(vlSelf->core__DOT__reg_0__DOT__regs_26),32);
        bufp->chgIData(oldp+36,(vlSelf->core__DOT__reg_0__DOT__regs_27),32);
        bufp->chgIData(oldp+37,(vlSelf->core__DOT__reg_0__DOT__regs_28),32);
        bufp->chgIData(oldp+38,(vlSelf->core__DOT__reg_0__DOT__regs_29),32);
        bufp->chgIData(oldp+39,(vlSelf->core__DOT__reg_0__DOT__regs_30),32);
        bufp->chgIData(oldp+40,(vlSelf->core__DOT__reg_0__DOT__regs_31),32);
    }
    bufp->chgBit(oldp+41,(vlSelf->clock));
    bufp->chgBit(oldp+42,(vlSelf->reset));
    bufp->chgIData(oldp+43,(vlSelf->io_pc),32);
    bufp->chgIData(oldp+44,(vlSelf->io_value),32);
    bufp->chgIData(oldp+45,(vlSelf->io_addr),32);
    bufp->chgIData(oldp+46,(vlSelf->io_instr),32);
    bufp->chgIData(oldp+47,(VL_SHIFTR_III(32,32,32, vlSelf->io_instr, 0x14U)),32);
    bufp->chgCData(oldp+48,((0x1fU & (vlSelf->io_instr 
                                      >> 0xfU))),5);
    bufp->chgCData(oldp+49,((0x1fU & (vlSelf->io_instr 
                                      >> 7U))),5);
    bufp->chgBit(oldp+50,((0x13U == ((0x380U & (vlSelf->io_instr 
                                                >> 5U)) 
                                     | (0x7fU & vlSelf->io_instr)))));
}

void Vcore___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcore___024root__trace_cleanup\n"); );
    // Init
    Vcore___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vcore___024root*>(voidSelf);
    Vcore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
}
