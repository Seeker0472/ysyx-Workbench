package core

import chisel3._
import chisel3.util._
import Constants_Val._
import core.IO._
import Constants_Val.CVAL.DLEN
//目前取指需要从顶层模块(core)中取出，所以就直接连线了
//也许应该重构
//存放PC，负责取出指令
class IFU extends Module {
  val io = IO(new Bundle {
    // val next_pc = Input(UInt(CVAL.DLEN.W))
    val in      = Flipped(Decoupled(new WBU_O))
    val instr_i = Input(UInt(CVAL.ILEN.W))
    val pc      = Output(UInt(CVAL.DLEN.W))
    val out     = Decoupled(new IFUO())
  })
  val s_idle :: s_fetching :: s_valid :: Nil = Enum(3)
  val state                            = RegInit(s_idle)
  state := MuxLookup(state, s_idle)(
    List(
      s_idle -> Mux(true.B, s_fetching, s_idle),
      s_fetching -> Mux(true.B, s_valid, s_fetching), //1cycle,depends on memory
      s_valid -> Mux(io.in.valid, s_fetching, s_valid)
    )
  )
  io.out.valid := state === s_valid

  val sram_sim = Reg(UInt(CVAL.DLEN.W))
  sram_sim          := io.instr_i
  io.out.bits.instr := sram_sim

  // io.out.valid:=true.B
  io.in.ready := true.B

  val pc = RegInit("h80000000".U(CVAL.DLEN.W))
  io.out.bits.pc := pc
  io.pc          := pc

  when(io.in.valid) {
    pc := io.in.bits.n_pc
  }
}
