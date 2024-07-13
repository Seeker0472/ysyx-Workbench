// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vcore.h for the primary calling header

#ifndef VERILATED_VCORE___024UNIT_H_
#define VERILATED_VCORE___024UNIT_H_  // guard

#include "verilated.h"


class Vcore__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vcore___024unit final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    Vcore__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vcore___024unit(Vcore__Syms* symsp, const char* v__name);
    ~Vcore___024unit();
    VL_UNCOPYABLE(Vcore___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
