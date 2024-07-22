package core

import chisel3._
import chisel3.util._
import Constants_Val._
import core.IO._

class AXI_Lite_Arbiter extends Module {
  val io = IO(new Bundle {
    val c1 = (new AXIReadIO)
    val c2 = (new AXIIO)
  })
  val s_idle :: s_c1_busy :: s_c2_busy :: Nil = Enum(3)
  val state                                   = RegInit(s_idle)
  // val axi                                     = Module(new AXI)
  val xbar=Module(new XBAR)
  val xb

  state := MuxLookup(state, s_idle)(
    List(
      s_idle -> Mux(io.c2.RA.valid, s_c2_busy, Mux(io.c1.RA.valid, s_c1_busy, s_idle)),
      s_c1_busy -> Mux(axi.io.RD.valid, s_idle, s_c1_busy),
      s_c2_busy -> Mux(axi.io.RD.valid, s_idle, s_c2_busy)
      // s_c1_valid -> Mux(io.c1.RD.ready, s_idle, s_c1_valid),
      // s_c2_valid -> Mux(io.c2.RD.ready, s_idle, s_c2_valid)
    )
  )
  //写通道全部分配给c2
  axi.io.WA <> io.c2.WA
  axi.io.WD <> io.c2.WD
  axi.io.WR <> io.c2.WR
  //读通道看状态
  io.c1.RA.ready      := state === s_idle
  io.c2.RA.ready      := state === s_idle
  axi.io.RA.valid     := io.c1.RA.valid || io.c2.RA.valid
  axi.io.RA.bits.addr := Mux(io.c1.RA.valid, io.c1.RA.bits.addr, io.c2.RA.bits.addr)
  axi.io.RD.ready     := Mux(state === s_c1_busy, io.c1.RD.ready, io.c2.RD.ready)
  io.c1.RD.bits.data  := axi.io.RD.bits.data
  io.c2.RD.bits.data  := axi.io.RD.bits.data
  io.c1.RD.bits.rresp := axi.io.RD.bits.rresp
  io.c2.RD.bits.rresp := axi.io.RD.bits.rresp
  io.c1.RD.valid      := Mux(state === s_c1_busy, axi.io.RD.valid, false.B)
  io.c2.RD.valid      := Mux(state === s_c2_busy, axi.io.RD.valid, false.B)

}
