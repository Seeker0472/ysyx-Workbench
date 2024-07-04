package core

import chisel3._

class REG extends Module{
    val io=IO(new Bundle{
        val read_i = Input(UInt(5.W))
        val read = Output(UInt(32.W))
        val write_en = Input(Bool())
        val write_i = Input(UInt(5.W))
        val write = Input(UInt(32.W))
    })

    val regs = RegInit(VecInit(Seq.fill(32)(0.U(32.W))))
    io.read:=regs(io.read_i)

    when(io.write_en){
        regs(io.write_i):= io.write
    }

}