#include <stdio.h>
#include "../include/debug.h"
#include "svdpi.h"

#define OK(ITEM) (ITEM?"True":"False")

extern "C"  void trace_decoder(svBit mem_R, svBit mem_W, svBit calc, svBit csr);
extern "C"  void trace_exu();
extern "C"  void trace_ifu(int unsigned addr,svBit start_end);
extern "C"  void trace_lsu(int unsigned addr,svBit RW,svBit start_end);

extern "C"  void trace_decoder(svBit mem_R, svBit mem_W, svBit calc, svBit csr){
    Log("Decoded_result:   MEMR:%s,MEMW:%s,calc:%s,csr:%s\n",OK(mem_R),OK(mem_W),OK(calc),OK(csr));
}
extern "C"  void trace_exu(){
    Log("Trace_EXU\n");
}
extern "C"  void trace_ifu(int unsigned addr,svBit start_end){
    Log("IFU:addr = %x,start=%s",addr,OK(start_end));
}
extern "C"  void trace_lsu(int unsigned addr,svBit RW,svBit start_end){
    Log("LSU:addr = %x,start=%s,Read=%s",addr,OK(start_end),OK(RW));
}