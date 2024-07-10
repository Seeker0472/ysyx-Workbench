// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcore.h for the primary calling header

#include "Vcore__pch.h"
#include "Vcore__Syms.h"
#include "Vcore___024unit.h"

extern "C" void call_ebreak();

VL_INLINE_OPT void Vcore___024unit____Vdpiimwrap_call_ebreak_TOP____024unit() {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vcore___024unit____Vdpiimwrap_call_ebreak_TOP____024unit\n"); );
    // Body
    call_ebreak();
}
