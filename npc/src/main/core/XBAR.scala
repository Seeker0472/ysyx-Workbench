package core

import chisel3._
import chisel3.util._
import core.IO._

import chisel3.util.experimental.decode.DecodeField
import chisel3.util.experimental.decode._

object MEM_Area extends ChiselEnum {
  val INV, SRAM, URAT = Value
}

class XBAR extends Module {
  val io = IO(new Bundle {
    val in = (new AXIIO)
    // val out = (new AXIIO)
  })
  val axi  = Module(new AXI)
  val urat = Module(new URAT)
  val clint=Module(new CLINT)

  val Table = TruthTable(
    Map(
      BitPat("b00010000000000000000????????????") -> BitPat("b001"),
      BitPat("b10000000????????????????????????") -> BitPat("b010"),
      BitPat("b00100000000010??????????????????") -> BitPat("b100"),
      BitPat("b0010000000000???????????????????") -> BitPat("b100"),
      //TODO
      // BitPat("b00010000000000000000????????????") -> BitPat(MEM_Area.URAT.asUInt),
      // BitPat("b10000000????????????????????????") -> BitPat(MEM_Area.SRAM.asUInt)
    ),
    BitPat("b000")
  )
  val mem_w_reg = RegInit(0.U(3.W))
  val mem_r_reg = RegInit(0.U(3.W))
  val mem_r_b   = decoder(io.in.RA.bits.addr, Table) //r_XBar行为
  val mem_w_b   = decoder(io.in.WA.bits.addr, Table) //w_XBar行为
  when(io.in.RA.valid) {
    mem_r_reg := mem_r_b
  }
  when(io.in.WA.valid) {
    mem_w_reg := mem_w_b
  }

  //选择设备(out)
  axi.io.WA.valid      := Mux(mem_w_b === BitPat("b010"), io.in.WA.valid, false.B) //如果选择sram，就开
  urat.io.WA.valid     := Mux(mem_w_b === BitPat("b001"), io.in.WA.valid, false.B)
  axi.io.WA.bits.addr  := io.in.WA.bits.addr
  urat.io.WA.bits.addr := io.in.WA.bits.addr
  io.in.WA.ready := Mux(
    mem_w_b === BitPat("b010") || mem_w_reg === BitPat("b010"),
    axi.io.WA.ready,
    urat.io.WA.ready
  ) //ready

  axi.io.WD.valid  := Mux(mem_w_reg === BitPat("b010"), io.in.WD.valid, false.B) //如果选择sram，就开
  urat.io.WD.valid := Mux(mem_w_b === BitPat("b001"), io.in.WD.valid, false.B)
  axi.io.WD.bits   := io.in.WD.bits
  urat.io.WD.bits  := io.in.WD.bits
  io.in.WD.ready := Mux(
    mem_w_b === BitPat("b010") || mem_w_reg === BitPat("b010"),
    axi.io.WD.ready,
    urat.io.WD.ready
  ) //ready

  axi.io.WR.ready     := Mux(mem_w_reg === BitPat("b010"), io.in.WR.ready, false.B) //如果选择sram，就开
  urat.io.WR.ready    := Mux(mem_w_b === BitPat("b001"), io.in.WR.ready, false.B)
  io.in.WR.bits.bresp := Mux(mem_w_reg === BitPat("b010"), axi.io.WR.bits.bresp, urat.io.WR.bits.bresp)
  io.in.WR.valid := Mux(
    mem_w_b === BitPat("b010") || mem_w_reg === BitPat("b010"),
    axi.io.WR.valid,
    urat.io.WR.valid
  ) //valid
  
  //选择设备(in)
  // axi.io.RA <> io.in.RA
  axi.io.RA.valid:=Mux(mem_r_b === BitPat("b010"), io.in.RA.valid, false.B) //如果选择sram，就开
  clint.io.RA.valid:=Mux(mem_r_b===BitPat("b100"),io.in.RA.valid,false.B)
  axi.io.RA.bits.addr:=io.in.RA.bits.addr
  clint.io.RA.bits.addr:=io.in.RA.bits.addr
    io.in.RA.ready := Mux(
    mem_r_b === BitPat("b010") || mem_r_reg === BitPat("b010"),
    axi.io.RA.ready,
    clint.io.RA.ready
  ) //ready
  // axi.io.RD <> io.in.RD

  axi.io.RD.ready:=Mux(mem_r_reg=== BitPat("b010"), io.in.RD.ready, false.B)
  clint.io.RD.ready:=Mux(mem_r_reg=== BitPat("b010"), io.in.RD.ready, false.B)
  io.in.RD.bits.data:=Mux(mem_r_reg=== BitPat("b010"), axi.io.RD.bits.data,clint.io.RD.bits.data)
  io.in.RD.bits.rresp:=Mux(mem_r_reg=== BitPat("b010"), axi.io.RD.bits.rresp,clint.io.RD.bits.rresp)
  io.in.RD.valid:=Mux(mem_r_reg===BitPat("b010"),axi.io.RD.valid,clint.io.RD.valid)

}
