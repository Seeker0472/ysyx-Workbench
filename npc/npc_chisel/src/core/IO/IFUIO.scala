package core.IO

import chisel3._
import Constants_Val._

class IFUO extends Bundle {
  val pc    = Output(UInt(CVAL.DLEN.W))
  val instr = Output(UInt(CVAL.ILEN.W))
}
