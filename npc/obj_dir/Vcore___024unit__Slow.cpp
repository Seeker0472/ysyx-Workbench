// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcore.h for the primary calling header

#include "Vcore__pch.h"
#include "Vcore__Syms.h"
#include "Vcore___024unit.h"

void Vcore___024unit___ctor_var_reset(Vcore___024unit* vlSelf);

Vcore___024unit::Vcore___024unit(Vcore__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vcore___024unit___ctor_var_reset(this);
}

void Vcore___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vcore___024unit::~Vcore___024unit() {
}
