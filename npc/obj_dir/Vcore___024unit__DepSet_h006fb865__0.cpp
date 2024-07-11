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

extern "C" int pmem_read(int read_addr);

VL_INLINE_OPT void Vcore___024unit____Vdpiimwrap_pmem_read_TOP____024unit(IData/*31:0*/ read_addr, IData/*31:0*/ &pmem_read__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vcore___024unit____Vdpiimwrap_pmem_read_TOP____024unit\n"); );
    // Body
    int read_addr__Vcvt;
    for (size_t read_addr__Vidx = 0; read_addr__Vidx < 1; ++read_addr__Vidx) read_addr__Vcvt = read_addr;
    int pmem_read__Vfuncrtn__Vcvt;
    pmem_read__Vfuncrtn__Vcvt = pmem_read(read_addr__Vcvt);
    pmem_read__Vfuncrtn = pmem_read__Vfuncrtn__Vcvt;
}

extern "C" void pmem_write(int write_addr, int write_data, char write_mask);

VL_INLINE_OPT void Vcore___024unit____Vdpiimwrap_pmem_write_TOP____024unit(IData/*31:0*/ write_addr, IData/*31:0*/ write_data, CData/*7:0*/ write_mask) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vcore___024unit____Vdpiimwrap_pmem_write_TOP____024unit\n"); );
    // Body
    int write_addr__Vcvt;
    for (size_t write_addr__Vidx = 0; write_addr__Vidx < 1; ++write_addr__Vidx) write_addr__Vcvt = write_addr;
    int write_data__Vcvt;
    for (size_t write_data__Vidx = 0; write_data__Vidx < 1; ++write_data__Vidx) write_data__Vcvt = write_data;
    char write_mask__Vcvt;
    for (size_t write_mask__Vidx = 0; write_mask__Vidx < 1; ++write_mask__Vidx) write_mask__Vcvt = write_mask;
    pmem_write(write_addr__Vcvt, write_data__Vcvt, write_mask__Vcvt);
}
