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
  // val axi                                     = Module(new AXI)
  val xbar = Module(new XBAR)
  //TODO:使用事物id来实现arbitor
  state := MuxLookup(state, s_idle)(
    List(
      s_idle -> Mux(
        io.c2.RA.valid && xbar.io.in.RA.ready,
        s_c2_busy,
        Mux(io.c1.RA.valid && xbar.io.in.RA.ready, s_c1_busy, s_idle)
      ),
      s_c1_busy -> Mux(xbar.io.in.RD.bits.last, s_idle, s_c1_busy),//TODO!!
      s_c2_busy -> Mux(xbar.io.in.RD.bits.last, s_idle, s_c2_busy)
      // s_c1_valid -> Mux(io.c1.RD.ready, s_idle, s_c1_valid),
      // s_c2_valid -> Mux(io.c2.RD.ready, s_idle, s_c2_valid)
    )
  )
  //写通道全部分配给c2
  io.out.WA <> io.c2.WA
  io.out.WD <> io.c2.WD
  io.out.WR <> io.c2.WR
  //读通道看状态
  io.c1.RA.ready          := state === s_idle && xbar.io.in.RA.ready
  io.c2.RA.ready          := state === s_idle && xbar.io.in.RA.ready
  xbar.io.in.RA.valid     := io.c1.RA.valid || io.c2.RA.valid
  xbar.io.in.RA.bits.addr := Mux(io.c1.RA.valid, io.c1.RA.bits.addr, io.c2.RA.bits.addr)
  xbar.io.in.RA.bits.size := Mux(io.c1.RA.valid, io.c1.RA.bits.size, io.c2.RA.bits.size)
  xbar.io.in.RA.bits.id   := Mux(io.c1.RA.valid, io.c1.RA.bits.id, io.c2.RA.bits.id)
  xbar.io.in.RA.bits.len   := Mux(io.c1.RA.valid, io.c1.RA.bits.len, io.c2.RA.bits.len)
  xbar.io.in.RD.ready     := Mux(state === s_c1_busy, io.c1.RD.ready, io.c2.RD.ready)
  io.c1.RD.bits.data      := xbar.io.in.RD.bits.data
  io.c2.RD.bits.data      := xbar.io.in.RD.bits.data
  io.c1.RD.bits.rresp     := xbar.io.in.RD.bits.rresp
  io.c2.RD.bits.rresp     := xbar.io.in.RD.bits.rresp
  //TODO: Is Necessary?
  io.c1.RD.bits.id   := xbar.io.in.RD.bits.id
  io.c2.RD.bits.id   := xbar.io.in.RD.bits.id
  io.c1.RD.bits.last := xbar.io.in.RD.bits.last
  io.c2.RD.bits.last := xbar.io.in.RD.bits.last
  io.c1.RD.valid     := Mux(state === s_c1_busy, xbar.io.in.RD.valid, false.B)
  io.c2.RD.valid     := Mux(state === s_c2_busy, xbar.io.in.RD.valid, false.B)

  //结果
  io.out <> xbar.io.axi

  // //似乎不需要XBAR了
  // state := MuxLookup(state, s_idle)(
  //   List(
  //     s_idle -> Mux(io.c2.RA.valid, s_c2_busy, Mux(io.c1.RA.valid, s_c1_busy, s_idle)),
  //     s_c1_busy -> Mux(io.out.RD.valid, s_idle, s_c1_busy),
  //     s_c2_busy -> Mux(io.out.RD.valid, s_idle, s_c2_busy)
  //     // s_c1_valid -> Mux(io.c1.RD.ready, s_idle, s_c1_valid),
  //     // s_c2_valid -> Mux(io.c2.RD.ready, s_idle, s_c2_valid)
  //   )
  // )
  // //写通道全部分配给c2
  // io.out.WA <> io.c2.WA
  // io.out.WD <> io.c2.WD
  // io.out.WR <> io.c2.WR
  // //读通道看状态
  // io.c1.RA.ready          := state === s_idle
  // io.c2.RA.ready          := state === s_idle
  // io.out.RA.valid     := io.c1.RA.valid || io.c2.RA.valid
  // io.out.RA.bits.addr := Mux(io.c1.RA.valid, io.c1.RA.bits.addr, io.c2.RA.bits.addr)
  // io.out.RD.ready     := Mux(state === s_c1_busy, io.c1.RD.ready, io.c2.RD.ready)
  // io.c1.RD.bits.data      := io.out.RD.bits.data
  // io.c2.RD.bits.data      := io.out.RD.bits.data
  // io.c1.RD.bits.rresp     := io.out.RD.bits.rresp
  // io.c2.RD.bits.rresp     := io.out.RD.bits.rresp
  // io.c1.RD.valid          := Mux(state === s_c1_busy, io.out.RD.valid, false.B)
  // io.c2.RD.valid          := Mux(state === s_c2_busy, io.out.RD.valid, false.B)
}
