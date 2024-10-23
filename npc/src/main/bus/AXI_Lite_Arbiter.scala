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
  val s_idle :: s_c1_wait :: s_c2_wait :: s_c1_busy :: s_c2_busy :: Nil = Enum(5)
  val state                                                             = RegInit(s_idle)
  val xbar                                                              = Module(new XBAR)
  //TODO:使用事物id来实现arbitor
  //c2 first!
  state := MuxLookup(state, s_idle)(
    List(
      s_idle -> Mux(
        io.c2.RA.valid,
        s_c2_wait,
        Mux(io.c1.RA.valid, s_c1_wait, s_idle)
      ),
      s_c1_wait -> Mux(xbar.io.in.RA.ready, s_c1_busy, s_c1_wait),
      s_c2_wait -> Mux(xbar.io.in.RA.ready, s_c2_busy, s_c2_wait),
      s_c1_busy -> Mux(xbar.io.in.RD.bits.last&&xbar.io.in.RD.valid, s_idle, s_c1_busy), 
      s_c2_busy -> Mux(xbar.io.in.RD.bits.last&&xbar.io.in.RD.valid, s_idle, s_c2_busy)
    )
  )

  //Read Channels
  io.c1.RA.ready := state === s_c1_wait && xbar.io.in.RA.ready
  io.c2.RA.ready := state === s_c2_wait && xbar.io.in.RA.ready

  xbar.io.in.RA.valid := Mux(state === s_c2_wait, io.c2.RA.valid, Mux(state === s_c1_wait, io.c1.RA.valid, false.B))
  xbar.io.in.RA.bits  := Mux(state === s_c2_wait, io.c2.RA.bits, io.c1.RA.bits)

  xbar.io.in.RD.ready := Mux(state === s_c1_busy || state === s_c1_wait, io.c1.RD.ready, io.c2.RD.ready)

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
