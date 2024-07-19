package core.IO

import chisel3._
import Constants_Val._

class RegReadIO extends Bundle {
  val addr = Output(UInt(CVAL.REG_ADDR_LEN.W))
  val data = Input(UInt(CVAL.DLEN.W))
}

class RegWriteIO extends Bundle {
  val write_enable = Output(Bool())
  val addr         = Output(UInt(CVAL.REG_ADDR_LEN.W))
  val data         = Output(UInt(CVAL.DLEN.W))
}

class CSRReadIO extends Bundle {
  val addr = Output(UInt(CVAL.CSR_ADDR_LEN.W))
  val data = Input(UInt(CVAL.DLEN.W))
}

class CSRWriteIO extends Bundle {
  val write_enable = Output(Bool())
  val addr         = Output(UInt(CVAL.CSR_ADDR_LEN.W))
  val data         = Output(UInt(CVAL.DLEN.W))
}
