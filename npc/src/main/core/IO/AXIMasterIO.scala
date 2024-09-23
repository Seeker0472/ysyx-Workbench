package core.IO

import chisel3._
import chisel3.util._
import Constants_Val._

class AXIMasterIO extends Bundle {
  val in = Flipped(Decoupled(new Bundle {
    val mem_read_enable = (Bool())
    val mem_read_type = (Load_Type())
    val mem_write_enable = (Bool())
    val mem_write_type = (Store_Type())
    val mem_read_addr = (UInt(CVAL.DLEN.W))
    val mem_write_addr = (UInt(CVAL.DLEN.W))
    val mem_write_data = (UInt(CVAL.DLEN.W))
  }))
  val out = Decoupled(new Bundle {
    val mem_read_result = (UInt(CVAL.DLEN.W))
  })
}

class AXIIO extends Bundle {
  val read = new AXIReadIO
  val write = new AXIWriteIO

  // def
  def RA = read.RA
  def RD = read.RD
  def WA = write.WA
  def WD = write.WD
  def WR = write.WR
}

class AXIReadIO extends Bundle {
  // Read address
  val RA = Flipped(Decoupled(new Bundle {
    val addr = (UInt(CVAL.DLEN.W))
    val size = (UInt(3.W))
    val len = UInt(8.W)
    val id = UInt(4.W)
    // arport-特权相关
  }))
  // Read data
  val RD = (Decoupled(new Bundle {
    val data = (UInt(CVAL.DLEN.W))
    val rresp = (UInt(2.W))
    val id = UInt(4.W)
    val last = Bool()
  }))
}
class AXIWriteIO extends Bundle {
  // Write address
  val WA = Flipped(Decoupled(new Bundle {
    val addr = (UInt(CVAL.DLEN.W))
    val size = (UInt(3.W))
    // awport-特权相关
  }))
  // Write data
  val WD = Flipped(Decoupled(new Bundle {
    val data = (UInt(CVAL.DLEN.W))
    val wstrb = (UInt(4.W)) // 掩码
  }))
  // Write response
  val WR = Decoupled(new Bundle {
    val bresp = Output(UInt(2.W))
  })
}
