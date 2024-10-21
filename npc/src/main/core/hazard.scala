package core

import chisel3._
import chisel3.util._
import Constants_Val._

class HazardUnit extends Module {
  val io = IO(new Bundle {
    val ifu_pc     = Flipped(Decoupled(UInt(CVAL.DLEN.W)))
    val decoder_pc = Flipped(Decoupled(UInt(CVAL.DLEN.W)))
    val exu_pc = Flipped(Decoupled(UInt(CVAL.DLEN.W)))
    val wbu        = Flipped(Decoupled(UInt(CVAL.DLEN.W)))
    val flush      = Output(Bool())
  })
  val ifu_hazard     = (io.ifu_pc.bits =/= io.wbu.bits) && io.ifu_pc.valid
  val decoder_hazard = (io.decoder_pc.bits =/= io.wbu.bits) && io.decoder_pc.valid
  val exu_hazard =(io.exu_pc.bits=/= io.wbu.bits)&& io.exu_pc.valid
  io.ifu_pc.ready     := true.B
  io.exu_pc.ready     := true.B
  io.decoder_pc.ready := true.B
  io.wbu.ready        := true.B

  io.flush := Mux(io.exu_pc.valid,exu_hazard,Mux(io.decoder_pc.valid, decoder_hazard, ifu_hazard)) && io.wbu.valid
}
