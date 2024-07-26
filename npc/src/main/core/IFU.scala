package core

import chisel3._
import chisel3.util._
import Constants_Val._
import core.IO._
import Constants_Val.CVAL.DLEN
import os.stat

//存放PC，负责取出指令
class IFU extends Module {
  val io = IO(new Bundle {
    val in       = Flipped(Decoupled(new WBU_O))
    val inst_now = Output(UInt(CVAL.DLEN.W))
    val out      = Decoupled(new IFUO())
    val axi = Flipped(new AXIReadIO())
    val rwerr = Input(Bool())
  })
  val s_idle :: s_fetching :: s_wait_data :: s_valid ::s_error:: Nil = Enum(5)

  // val axi = Module(new AXI_Master())

  val state = RegInit(s_idle)
  val pc    = RegInit("h20000000".U(CVAL.DLEN.W))
  val inst  = Reg(UInt(CVAL.DLEN.W))

  state := MuxLookup(state, s_idle)(
    List(
      s_idle -> Mux(true.B, s_fetching, s_idle), //Initial
      s_fetching -> Mux(io.axi.RA.ready, s_wait_data, s_fetching), //1cycle,depends on memory
      s_wait_data -> Mux(io.axi.RD.valid, s_valid, s_wait_data),
      s_valid -> Mux(io.in.valid, s_fetching, s_valid),
      s_error->s_error
    )
  )
  io.out.valid := state === s_valid
  io.axi.RA.bits.addr:=pc

  when(io.axi.RD.valid) {
    inst := io.axi.RD.bits.data//next - inst
  }
  io.axi.RA.valid:=state===s_fetching
  io.axi.RD.ready:=true.B

  io.in.ready := true.B

  // io.pc          := pc
  io.inst_now := inst

  io.out.bits.pc    := pc
  io.out.bits.instr := inst

  when(io.in.valid) {
    pc := Mux(state===s_error,0.U,io.in.bits.n_pc)
  }
  when(io.rwerr){
    // state:=s_error
  }
}
