package core

import chisel3._
import chisel3.util._
import Constants_Val._
import core.IO._
//目前取指需要从顶层模块(core)中取出，所以就直接连线了
//也许应该重构
//存放PC，负责取出指令
class IFU extends Module {
  val io = IO(new Bundle {
    // val next_pc = Input(UInt(CVAL.DLEN.W))
    val in = Flipped(Decoupled(new WBU_O))
    val instr_i = Input(UInt(CVAL.ILEN.W))
    val pc      = Output(UInt(CVAL.DLEN.W))
    val out     = Decoupled(new IFUO())
  })
  io.out.valid:=true.B
  io.in.ready:=true.B
  val pc = RegInit("h80000000".U(CVAL.DLEN.W))
  io.out.bits.pc := pc
  io.pc     := pc

  io.out.bits.instr := io.instr_i
  pc           := io.in.bits.n_pc
  // io.addr:=io.pc
}
