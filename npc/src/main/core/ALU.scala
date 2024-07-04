package core

import chisel3._

class ALU extends Module{
    val io=IO(new Bundle{
        val src1=Input(UInt(32.W))
        val imm = Input(UInt(32.W))
        val dst = Output(UInt(32.W))
        val addi = Input(Bool())
    })
// 默认情况下，dst 输出为 0
  io.dst := 0.U

  // 当 addi 信号为高时，执行加法运算
  when(io.addi) {
    io.dst := io.src1 + io.imm
  }
}