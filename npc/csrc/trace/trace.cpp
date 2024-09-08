#include <stdio.h>
#include "../include/debug.h"
#include "svdpi.h"

#define OK(ITEM) (ITEM?"True":"False")

void trace_decoder(svBit mem_R, svBit mem_W, svBit calc, svBit csr);
void trace_exu();
void trace_ifu(int unsigned addr,svBit start_end);
void trace_lsu(int unsigned addr,svBit RW,svBit start_end);

void trace_decoder(svBit mem_R, svBit mem_W, svBit calc, svBit csr){
    Log("Decoded_result:   MEMR:%s,MEMW:%s,calc:%s,csr:%s\n",OK(mem_R),OK(mem_W),OK(calc),OK(csr));
}
void trace_exu(){
    Log("Trace_EXU\n");
}
void trace_ifu(int unsigned addr,svBit start_end){
    Log("IFU:addr = %x,start=%s",addr,OK(start_end));
}
void trace_lsu(int unsigned addr,svBit RW,svBit start_end){
    Log("LSU:addr = %x,start=%s,Read=%s",addr,OK(start_end),OK(RW));
}