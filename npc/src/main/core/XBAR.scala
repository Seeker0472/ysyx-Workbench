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
    val in  = (new AXIIO)
    // val out = (new AXIIO)
  })
  val axi                                     = Module(new AXI)
  val urat=Module(new URAT)

  val Table = TruthTable(
    Map(

      BitPat("b00010000000000000000????????????") -> BitPat("b001"),
      BitPat("b10000000????????????????????????") -> BitPat("b010")
            // BitPat("b00010000000000000000????????????") -> BitPat(MEM_Area.URAT.asUInt),
      // BitPat("b10000000????????????????????????") -> BitPat(MEM_Area.SRAM.asUInt)
    ),
    BitPat("b000")
  )
  val mem_w_reg = RegInit(("b000".asUInt))
  val mem_r_t    = decoder(io.in.WA.bits.addr, Table) //XBar行为
  val mem_w_b    = decoder(io.in.RA.bits.addr, Table) //w_XBar行为
  mem_w_reg:=mem_w_b
  

  //选择设备(out)
  axi.io.WA.valid:=Mux(mem_w_b===BitPat("b010"),io.in.WA.valid,false.B)//如果选择sram，就开
  urat.io.WA.valid:=Mux(mem_w_b===BitPat("b001"),io.in.WA.valid,false.B)
  axi.io.WA.bits.addr:=io.in.WA.bits.addr
  urat.io.WA.bits.addr:=io.in.WA.bits.addr
  io.in.WA.ready:=Mux(mem_w_b===BitPat("b010")||mem_w_reg===BitPat("b010"),io.in.WA.ready,urat.io.WA.ready)//ready

  axi.io.WD.valid:=Mux(mem_w_reg===BitPat("b010"),io.in.WD.valid,false.B)//如果选择sram，就开
  urat.io.WD.valid:=Mux(mem_w_b===BitPat("b001"),io.in.WD.valid,false.B)
  axi.io.WD.bits:=io.in.WD.bits
  urat.io.WD.bits:=io.in.WD.bits
  io.in.WD.ready:=Mux(mem_w_b===BitPat("b010")||mem_w_reg===BitPat("b010"),io.in.WD.ready,urat.io.WD.ready)//ready

  axi.io.WR.ready:=Mux(mem_w_reg===BitPat("b010"),io.in.WR.ready,false.B)//如果选择sram，就开
  urat.io.WR.ready:=Mux(mem_w_b===BitPat("b001"),io.in.WR.ready,false.B)
  io.in.WR.bits:=Mux(mem_w_reg===BitPat("b010"),io.in.WR.bits,urat.io.WR.bits)
  io.in.WR.valid:=Mux(mem_w_b===BitPat("b010")||mem_w_reg===BitPat("b010"),io.in.WR.valid,urat.io.WR.valid)//valid

  axi.io.RA<>io.in.RA
  axi.io.RD<>io.in.RD


}
