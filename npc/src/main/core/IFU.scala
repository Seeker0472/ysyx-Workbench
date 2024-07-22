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
  })
  val s_idle :: s_fetching :: s_wait_data :: s_valid :: Nil = Enum(4)

  val axi = Module(new AXI_Master())

  val state = RegInit(s_idle)
  val pc    = RegInit("h80000000".U(CVAL.DLEN.W))
  val inst  = Reg(UInt(CVAL.DLEN.W))

  state := MuxLookup(state, s_idle)(
    List(
      s_idle -> Mux(true.B, s_fetching, s_idle), //Initial
      s_fetching -> Mux(axi.io.in.ready, s_wait_data, s_fetching), //1cycle,depends on memory
      s_wait_data -> Mux(axi.io.out.valid, s_valid, s_wait_data),
      s_valid -> Mux(io.in.valid, s_fetching, s_valid)
    )
  )
  io.out.valid := state === s_valid

  axi.io.in.bits.mem_write_enable := 0.B
  axi.io.in.bits.mem_write_addr   := 0.U
  axi.io.in.bits.mem_write_type   := Store_Type.inv
  axi.io.in.bits.mem_write_data   := 0.U
  axi.io.in.bits.mem_read_addr    := pc
  axi.io.in.bits.mem_read_type    := Load_Type.lw
  axi.io.in.bits.mem_read_enable  := state === s_fetching
  axi.io.in.valid                 := state === s_fetching
  axi.io.out.ready                := true.B

  when(axi.io.out.valid) {
    inst := axi.io.out.bits.mem_read_result

  }

  io.in.ready := true.B

  // io.pc          := pc
  io.inst_now := inst

  io.out.bits.pc    := pc
  io.out.bits.instr := inst

  when(io.in.valid) {
    pc := io.in.bits.n_pc
  }
}
