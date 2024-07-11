// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Prototypes for DPI import and export functions.
//
// Verilator includes this file in all generated .cpp files that use DPI functions.
// Manually include this file where DPI .c import functions are declared to ensure
// the C functions match the expectations of the DPI imports.

#ifndef VERILATED_VCORE__DPI_H_
#define VERILATED_VCORE__DPI_H_  // guard

#include "svdpi.h"

#ifdef __cplusplus
extern "C" {
#endif


    // DPI IMPORTS
    // DPI import at build/core.sv:1434:30
    extern void call_ebreak();
    // DPI import at build/core.sv:1448:29
    extern int pmem_read(int read_addr);
    // DPI import at build/core.sv:1449:30
    extern void pmem_write(int write_addr, int write_data, char write_mask);

#ifdef __cplusplus
}
#endif

#endif  // guard
