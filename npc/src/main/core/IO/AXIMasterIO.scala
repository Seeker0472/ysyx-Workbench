package core.IO

import chisel3._
import chisel3.util._
import Constants_Val._

class AXIMasterIO extends Bundle {
  val in = Flipped(Decoupled(new Bundle {
    val mem_read_enable  = (Bool())
    val mem_read_type    = (Load_Type())
    val mem_write_enable = (Bool())
    val mem_write_type   = (Store_Type())
    val mem_read_addr    = (UInt(CVAL.DLEN.W))
    val mem_write_addr   = (UInt(CVAL.DLEN.W))
    val mem_write_data   = (UInt(CVAL.DLEN.W))
  }))
  val out = Decoupled(new Bundle {
    val mem_read_result = (UInt(CVAL.DLEN.W))
    //TODO:异常信号！！！
  })
}
