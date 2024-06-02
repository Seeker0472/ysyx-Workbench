// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vexample__Syms.h"


//======================

void Vexample::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addInitCb(&traceInit, __VlSymsp);
    traceRegister(tfp->spTrace());
}

void Vexample::traceInit(void* userp, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vexample__Syms* __restrict vlSymsp = static_cast<Vexample__Syms*>(userp);
    if (!Verilated::calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
                        "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->module(vlSymsp->name());
    tracep->scopeEscape(' ');
    Vexample::traceInitTop(vlSymsp, tracep);
    tracep->scopeEscape('.');
}

//======================


void Vexample::traceInitTop(void* userp, VerilatedVcd* tracep) {
    Vexample__Syms* __restrict vlSymsp = static_cast<Vexample__Syms*>(userp);
    Vexample* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceInitSub0(userp, tracep);
    }
}

void Vexample::traceInitSub0(void* userp, VerilatedVcd* tracep) {
    Vexample__Syms* __restrict vlSymsp = static_cast<Vexample__Syms*>(userp);
    Vexample* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    const int c = vlSymsp->__Vm_baseCode;
    if (false && tracep && c) {}  // Prevent unused
    // Body
    {
        tracep->declBit(c+1,"a", false,-1);
        tracep->declBit(c+2,"b", false,-1);
        tracep->declBit(c+3,"f", false,-1);
        tracep->declBit(c+1,"example a", false,-1);
        tracep->declBit(c+2,"example b", false,-1);
        tracep->declBit(c+3,"example f", false,-1);
    }
}

void Vexample::traceRegister(VerilatedVcd* tracep) {
    // Body
    {
        tracep->addFullCb(&traceFullTop0, __VlSymsp);
        tracep->addChgCb(&traceChgTop0, __VlSymsp);
        tracep->addCleanupCb(&traceCleanup, __VlSymsp);
    }
}

void Vexample::traceFullTop0(void* userp, VerilatedVcd* tracep) {
    Vexample__Syms* __restrict vlSymsp = static_cast<Vexample__Syms*>(userp);
    Vexample* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceFullSub0(userp, tracep);
    }
}

void Vexample::traceFullSub0(void* userp, VerilatedVcd* tracep) {
    Vexample__Syms* __restrict vlSymsp = static_cast<Vexample__Syms*>(userp);
    Vexample* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->fullBit(oldp+1,(vlTOPp->a));
        tracep->fullBit(oldp+2,(vlTOPp->b));
        tracep->fullBit(oldp+3,(vlTOPp->f));
    }
}
