package core.IO

import chisel3._
import Constants_Val._

class WBU_O extends Bundle {
  val n_pc = Output(UInt(CVAL.DLEN.W))
  val pc   = Output(UInt(CVAL.DLEN.W))
}
