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
        bufp->chgBit(oldp+0,((0x7fffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_57))));
        bufp->chgIData(oldp+1,(vlSelf->core__DOT__decoder__DOT__casez_tmp),32);
        bufp->chgBit(oldp+2,(((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T)) 
                              | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1)) 
                                 | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_2)) 
                                    | ((0x3fU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_6)) 
                                       | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_9)) 
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
                                                               == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_57)))))))))))))));
        bufp->chgCData(oldp+3,(vlSelf->core__DOT___decoder_io_out_alu_op_type),4);
        bufp->chgBit(oldp+4,(vlSelf->core__DOT___decoder_io_out_pc_jump));
        bufp->chgBit(oldp+5,(vlSelf->core__DOT___decoder_io_out_mem_read_enable));
        bufp->chgCData(oldp+6,(vlSelf->core__DOT___decoder_io_out_mem_read_type),3);
        bufp->chgCData(oldp+7,(vlSelf->core__DOT___decoder_io_out_mem_write_type),2);
        bufp->chgBit(oldp+8,(((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)) 
                              | (0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_40)))));
        bufp->chgCData(oldp+9,(vlSelf->core__DOT___decoder_io_out_branch_type),3);
        bufp->chgCData(oldp+10,(((0U == (IData)(vlSelf->core__DOT___decoder_io_out_mem_write_type))
                                  ? 0U : ((1U == (IData)(vlSelf->core__DOT___decoder_io_out_mem_write_type))
                                           ? 3U : (
                                                   (2U 
                                                    == (IData)(vlSelf->core__DOT___decoder_io_out_mem_write_type))
                                                    ? 0xfU
                                                    : 0xffU)))),8);
    }
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[2U])) {
        bufp->chgIData(oldp+11,(vlSelf->core__DOT__ifu__DOT__pc),32);
        bufp->chgIData(oldp+12,(vlSelf->core__DOT__reg_0__DOT__regs_0),32);
        bufp->chgIData(oldp+13,(vlSelf->core__DOT__reg_0__DOT__regs_1),32);
        bufp->chgIData(oldp+14,(vlSelf->core__DOT__reg_0__DOT__regs_2),32);
        bufp->chgIData(oldp+15,(vlSelf->core__DOT__reg_0__DOT__regs_3),32);
        bufp->chgIData(oldp+16,(vlSelf->core__DOT__reg_0__DOT__regs_4),32);
        bufp->chgIData(oldp+17,(vlSelf->core__DOT__reg_0__DOT__regs_5),32);
        bufp->chgIData(oldp+18,(vlSelf->core__DOT__reg_0__DOT__regs_6),32);
        bufp->chgIData(oldp+19,(vlSelf->core__DOT__reg_0__DOT__regs_7),32);
        bufp->chgIData(oldp+20,(vlSelf->core__DOT__reg_0__DOT__regs_8),32);
        bufp->chgIData(oldp+21,(vlSelf->core__DOT__reg_0__DOT__regs_9),32);
        bufp->chgIData(oldp+22,(vlSelf->core__DOT__reg_0__DOT__regs_10),32);
        bufp->chgIData(oldp+23,(vlSelf->core__DOT__reg_0__DOT__regs_11),32);
        bufp->chgIData(oldp+24,(vlSelf->core__DOT__reg_0__DOT__regs_12),32);
        bufp->chgIData(oldp+25,(vlSelf->core__DOT__reg_0__DOT__regs_13),32);
        bufp->chgIData(oldp+26,(vlSelf->core__DOT__reg_0__DOT__regs_14),32);
        bufp->chgIData(oldp+27,(vlSelf->core__DOT__reg_0__DOT__regs_15),32);
    }
    bufp->chgBit(oldp+28,(vlSelf->clock));
    bufp->chgBit(oldp+29,(vlSelf->reset));
    bufp->chgIData(oldp+30,(vlSelf->io_pc),32);
    bufp->chgIData(oldp+31,(vlSelf->io_value),32);
    bufp->chgIData(oldp+32,(vlSelf->io_addr),32);
    bufp->chgIData(oldp+33,(vlSelf->io_instr),32);
    bufp->chgIData(oldp+34,(vlSelf->io_inst_now),32);
    bufp->chgCData(oldp+35,((0x1fU & (vlSelf->io_instr 
                                      >> 0xfU))),5);
    bufp->chgCData(oldp+36,((0x1fU & (vlSelf->io_instr 
                                      >> 0x14U))),5);
    bufp->chgCData(oldp+37,((0x1fU & (vlSelf->io_instr 
                                      >> 7U))),5);
    bufp->chgBit(oldp+38,((1U & ((IData)((0x17U == 
                                          (0x7fU & vlSelf->io_instr))) 
                                 | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)) 
                                    | ((0x7fU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_19)) 
                                       | (0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_40))))))));
    bufp->chgBit(oldp+39,(((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T)) 
                           | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_1)) 
                              | ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_3)) 
                                 | ((0x3fU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_6)) 
                                    | ((0xffffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_11)) 
                                       | ((IData)((
                                                   (0x33U 
                                                    == 
                                                    (0x7fU 
                                                     & vlSelf->io_instr)) 
                                                   & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_36))) 
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
                                                            == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_57)))))))))))))));
    bufp->chgBit(oldp+40,(((0x1ffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_8)) 
                           | (IData)(((0x23U == (0x7fU 
                                                 & vlSelf->io_instr)) 
                                      & (IData)(vlSelf->core__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_59))))));
    bufp->chgIData(oldp+41,((0x3fffffffU & (~ (vlSelf->io_instr 
                                               >> 2U)))),30);
    bufp->chgIData(oldp+42,(vlSelf->core__DOT__reg_0__DOT__casez_tmp),32);
    bufp->chgIData(oldp+43,(vlSelf->core__DOT__reg_0__DOT__casez_tmp_0),32);
    bufp->chgIData(oldp+44,((((IData)(vlSelf->core__DOT___decoder_io_out_pc_jump) 
                              | (((4U & (IData)(vlSelf->core__DOT___decoder_io_out_branch_type))
                                   ? ((2U & (IData)(vlSelf->core__DOT___decoder_io_out_branch_type))
                                       ? ((1U & (IData)(vlSelf->core__DOT___decoder_io_out_branch_type))
                                           ? (IData)(vlSelf->core__DOT__exu__DOT__comp__DOT___io_result_T_18)
                                           : (vlSelf->core__DOT__reg_0__DOT__casez_tmp 
                                              >= vlSelf->core__DOT__reg_0__DOT__casez_tmp_0))
                                       : ((1U & (IData)(vlSelf->core__DOT___decoder_io_out_branch_type))
                                           ? (vlSelf->core__DOT__reg_0__DOT__casez_tmp 
                                              < vlSelf->core__DOT__reg_0__DOT__casez_tmp_0)
                                           : VL_GTES_III(32, vlSelf->core__DOT__reg_0__DOT__casez_tmp, vlSelf->core__DOT__reg_0__DOT__casez_tmp_0)))
                                   : ((2U & (IData)(vlSelf->core__DOT___decoder_io_out_branch_type))
                                       ? ((1U & (IData)(vlSelf->core__DOT___decoder_io_out_branch_type))
                                           ? VL_LTS_III(32, vlSelf->core__DOT__reg_0__DOT__casez_tmp, vlSelf->core__DOT__reg_0__DOT__casez_tmp_0)
                                           : (vlSelf->core__DOT__reg_0__DOT__casez_tmp 
                                              != vlSelf->core__DOT__reg_0__DOT__casez_tmp_0))
                                       : (IData)(vlSelf->core__DOT__exu__DOT__comp__DOT___io_result_T_18))) 
                                 & ((0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_16)) 
                                    | (0xffU == (IData)(vlSelf->core__DOT__decoder__DOT___decodedResults_andMatrixOutputs_T_40)))))
                              ? vlSelf->core__DOT__exu__DOT__result
                              : ((IData)(4U) + vlSelf->core__DOT__ifu__DOT__pc))),32);
    bufp->chgIData(oldp+45,(vlSelf->core__DOT__exu__DOT__result),32);
    bufp->chgIData(oldp+46,(vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src1),32);
    bufp->chgIData(oldp+47,(vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src2),32);
    bufp->chgIData(oldp+48,(vlSelf->core__DOT__exu__DOT__alu__DOT__casez_tmp),32);
    bufp->chgQData(oldp+49,((0x7fffffffffffffffULL 
                             & ((QData)((IData)(vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src1)) 
                                << (0x1fU & vlSelf->core__DOT__exu__DOT____Vcellinp__alu__io_in_src2)))),63);
    bufp->chgBit(oldp+51,(((4U & (IData)(vlSelf->core__DOT___decoder_io_out_branch_type))
                            ? ((2U & (IData)(vlSelf->core__DOT___decoder_io_out_branch_type))
                                ? ((1U & (IData)(vlSelf->core__DOT___decoder_io_out_branch_type))
                                    ? (IData)(vlSelf->core__DOT__exu__DOT__comp__DOT___io_result_T_18)
                                    : (vlSelf->core__DOT__reg_0__DOT__casez_tmp 
                                       >= vlSelf->core__DOT__reg_0__DOT__casez_tmp_0))
                                : ((1U & (IData)(vlSelf->core__DOT___decoder_io_out_branch_type))
                                    ? (vlSelf->core__DOT__reg_0__DOT__casez_tmp 
                                       < vlSelf->core__DOT__reg_0__DOT__casez_tmp_0)
                                    : VL_GTES_III(32, vlSelf->core__DOT__reg_0__DOT__casez_tmp, vlSelf->core__DOT__reg_0__DOT__casez_tmp_0)))
                            : ((2U & (IData)(vlSelf->core__DOT___decoder_io_out_branch_type))
                                ? ((1U & (IData)(vlSelf->core__DOT___decoder_io_out_branch_type))
                                    ? VL_LTS_III(32, vlSelf->core__DOT__reg_0__DOT__casez_tmp, vlSelf->core__DOT__reg_0__DOT__casez_tmp_0)
                                    : (vlSelf->core__DOT__reg_0__DOT__casez_tmp 
                                       != vlSelf->core__DOT__reg_0__DOT__casez_tmp_0))
                                : (IData)(vlSelf->core__DOT__exu__DOT__comp__DOT___io_result_T_18)))));
    bufp->chgIData(oldp+52,(vlSelf->core__DOT__exu__DOT___mem_read_data),32);
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
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
}
