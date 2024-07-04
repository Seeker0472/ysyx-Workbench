package core

import chisel3._
//有点不知道应该怎么写，就先空着吧
class IFU extends Module{
    val io=IO(new Bundle{
        val pc = Input(UInt(32.W))
        val addr = Output(UInt(32.W))
        val instr = Input(UInt(32.W))
    })
    io.addr:=io.pc
    
}