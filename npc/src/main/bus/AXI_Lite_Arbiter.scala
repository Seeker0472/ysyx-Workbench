package bus

import chisel3._
import chisel3.util._
import Constants_Val._
import core.IO._

class AXI_Lite_Arbiter extends Module {
  val io = IO(new Bundle {
    val c1  = (new AXIReadIO)
    val c2  = (new AXIIO)
    val out = Flipped(new AXIIO)
  })
  val s_idle :: s_c1_busy :: s_c2_busy :: Nil = Enum(3)
  val state                                   = RegInit(s_idle)
  val xbar                                    = Module(new XBAR)
  //TODO:使用事物id来实现arbitor
  //优先给c2？
  state := MuxLookup(state, s_idle)(
    List(
      s_idle -> Mux(
        io.c2.RA.valid && xbar.io.in.RA.ready,
        s_c2_busy,
        Mux(io.c1.RA.valid && xbar.io.in.RA.ready, s_c1_busy, s_idle)
      ),
      s_c1_busy -> Mux(xbar.io.in.RD.bits.last, s_idle, s_c1_busy), //TODO!!
      s_c2_busy -> Mux(xbar.io.in.RD.bits.last, s_idle, s_c2_busy)
    )
  )

  //Read Channels
  val c1_ready = state === s_idle && xbar.io.in.RA.ready
  val c2_ready = state === s_idle && xbar.io.in.RA.ready
  io.c1.RA.ready := c1_ready && ~c2_ready
  io.c2.RA.ready := c2_ready

  xbar.io.in.RA.valid := state === s_idle && (io.c1.RA.valid || io.c2.RA.valid)
  // xbar.io.in.RA.bits  := Mux((state === s_idle && (io.c1.RA.valid) || state === s_c2_busy), io.c1.RA.bits, io.c2.RA.bits)
  xbar.io.in.RA.bits  := Mux((state === s_idle && (io.c2.RA.valid) || state === s_c2_busy), io.c2.RA.bits, io.c1.RA.bits)

  xbar.io.in.RD.ready := Mux(state === s_c1_busy, io.c1.RD.ready, io.c2.RD.ready)

  io.c1.RD.bits := xbar.io.in.RD.bits
  io.c2.RD.bits := xbar.io.in.RD.bits

  io.c1.RD.valid := Mux(state === s_c1_busy, xbar.io.in.RD.valid, false.B)
  io.c2.RD.valid := Mux(state === s_c2_busy, xbar.io.in.RD.valid, false.B)

  //assign write channel to c2 Only
  io.out.WA <> io.c2.WA
  io.out.WD <> io.c2.WD
  io.out.WR <> io.c2.WR
  io.out.RA <> xbar.io.axi.RA
  io.out.RD <> xbar.io.axi.RD

}
