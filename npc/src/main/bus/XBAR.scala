package bus

import chisel3._
import chisel3.util._
import core.IO._

import chisel3.util.experimental.decode.DecodeField
import chisel3.util.experimental.decode._
import _root_.circt.stage.CLI

object MEM_Area extends ChiselEnum {
  val INV, SRAM, URAT = Value
}

class XBAR extends Module {
  val io = IO(new Bundle {
    val in  = (new AXIIO)
    val axi = Flipped(new AXIIO)
  })
  val Table = TruthTable(
    Map(
      BitPat("b10000000????????????????????????") -> BitPat("b010"),//OLD
      BitPat("b00001111????????????????????????") -> BitPat("b010"),//SRAM
      BitPat("b00100000000000000000????????????") -> BitPat("b010"),//MROM
      BitPat("b0000001000000000????????????????") -> BitPat("b001"),//CLINT
      BitPat("b00010000000000000000111111111111") -> BitPat("b010"),//URAT
    ),
    BitPat("b000")//TODO:暂时把所有地址打进总线
  )
  // val mem_w_reg = RegInit(0.U(3.W))
  val mem_r_reg = RegInit(0.U(3.W))
  val mem_r_b   = decoder(io.in.RA.bits.addr, Table) //r_XBar行为
  // val mem_w_b   = decoder(io.in.WA.bits.addr, Table) //w_XBar行为
  when(io.in.RA.valid) {
    mem_r_reg := mem_r_b
  }
  val clint=Module(new CLINT)
  // when(io.in.WA.valid) {
  //   mem_w_reg := mem_w_b
  // }
  io.axi.WA<>io.in.WA
  io.axi.WD<>io.in.WD
  io.axi.WR<>io.in.WR

      //选择设备(in)
  // io.axi.RA <> io.in.RA
  io.axi.RA.valid      := Mux(mem_r_b === BitPat("b010"), io.in.RA.valid, false.B) //如果选择sram，就开
  clint.io.RA.valid     := Mux(mem_r_b === BitPat("b001"), io.in.RA.valid, false.B) //b100
  io.axi.RA.bits.addr  := io.in.RA.bits.addr
  clint.io.RA.bits.addr := io.in.RA.bits.addr
  io.in.RA.ready := Mux(
    mem_r_b === BitPat("b010") || mem_r_reg === BitPat("b010"),
    io.axi.RA.ready,
    clint.io.RA.ready
  ) //ready

  io.axi.RD.ready     := Mux(mem_r_reg === BitPat("b010"), io.in.RD.ready, false.B)
  clint.io.RD.ready    := Mux(mem_r_reg === BitPat("b010"), io.in.RD.ready, false.B)
  io.in.RD.bits.data  := Mux(mem_r_reg === BitPat("b010"), io.axi.RD.bits.data, clint.io.RD.bits.data)
  io.in.RD.bits.rresp := Mux(mem_r_reg === BitPat("b010"), io.axi.RD.bits.rresp, clint.io.RD.bits.rresp)

  io.in.RD.valid      := Mux(mem_r_reg === BitPat("b010"), io.axi.RD.valid, Mux(mem_r_reg===BitPat("b001"),clint.io.RD.valid,false.B))
}
