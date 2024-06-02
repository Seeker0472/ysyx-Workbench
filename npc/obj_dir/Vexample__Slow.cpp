// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vexample.h for the primary calling header

#include "Vexample.h"
#include "Vexample__Syms.h"

//==========

VL_CTOR_IMP(Vexample) {
    Vexample__Syms* __restrict vlSymsp = __VlSymsp = new Vexample__Syms(this, name());
    Vexample* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vexample::__Vconfigure(Vexample__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-12);
    Verilated::timeprecision(-12);
}

Vexample::~Vexample() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void Vexample::_eval_initial(Vexample__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vexample::_eval_initial\n"); );
    Vexample* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vexample::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vexample::final\n"); );
    // Variables
    Vexample__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vexample* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vexample::_eval_settle(Vexample__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vexample::_eval_settle\n"); );
    Vexample* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

void Vexample::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vexample::_ctor_var_reset\n"); );
    // Body
    a = VL_RAND_RESET_I(1);
    b = VL_RAND_RESET_I(1);
    f = VL_RAND_RESET_I(1);
    { int __Vi0=0; for (; __Vi0<1; ++__Vi0) {
            __Vm_traceActivity[__Vi0] = VL_RAND_RESET_I(1);
    }}
}
