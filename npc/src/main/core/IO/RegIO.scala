package core.IO

import chisel3._
import Constants_Val._

class RegReadIO extends Bundle {
  val en   = Output(Bool())
  val no = Output(UInt(CVAL.ILEN.W))
  val data = Input(UInt(CVAL.DLEN.W))
}

class RegWriteIO extends Bundle {
  val en   = Output(Bool())
  val no = Output(UInt(CVAL.ILEN.W))
  val data = Output(UInt(CVAL.DLEN.W))
}
