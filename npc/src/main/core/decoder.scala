package core;

import chisel3._
//TODO:改成menu的形式！！！
//Decoder API0

class Decoder extends Module{
    val io=IO(new Bundle{
        val instr = Input(UInt(32.W))
        val immI = Output(UInt(32.W))
        val rs1 = Output(UInt(5.W))
        val rd = Output(UInt(5.W))
        val addi = Output(Bool())
        val ebreak = Output(Bool())
    })
    //only Addi
    io.immI := io.instr(31,20)
    io.rs1 := io.instr(19,15)
    io.rd := io.instr(11,7)

    val mask = "b00000000000000000111000001111111".U
    val addival = "b00000000000000000000000000010011".U
    val ebreak =  "b00000000000100000000000001110011".U
    io.addi := (io.instr&mask)===addival
    io.ebreak := io.instr===ebreak
}
