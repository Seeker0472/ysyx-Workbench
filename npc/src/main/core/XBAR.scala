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
    val out = (new AXIIO)
  })
  val Table = TruthTable(
    Map(
      BitPat("h10000???") -> BitPat(MEM_Area.URAT.asUInt),
      BitPat("h80??????") -> BitPat(MEM_Area.SRAM.asUInt)
    ),
    BitPat(MEM_Area.INV.asUInt)
  )
  val mem_Type = RegInit(MEM_Area.INV.asUInt)
  val mem_t    = decoder(io.in.WA.bits.addr, Table) //XBar行为
  
}
