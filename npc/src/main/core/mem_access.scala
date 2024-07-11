package core

import chisel3._
import chisel3.util._

import Constants_Val._
import core.IO._

class MEM extends BlackBox with HasBlackBoxInline {
  val io = IO(new Bundle {
    val read_addr   = Input(UInt(CVAL.DLEN.W))
    val read_enable = Input(Bool())
    val read_data   = Output(UInt(CVAL.DLEN.W))

    val write_enable = Input(Bool())
    val write_addr   = Input(UInt(CVAL.DLEN.W))
    val write_data   = Input(UInt(CVAL.DLEN.W))
    val write_mask   = Input(UInt(CVAL.DLEN.W))
  })
  setInline(
    "mem_access.v",
    """import "DPI-C" function int pmem_read(input int raddr);
      |import "DPI-C" function void pmem_write(
      |input int waddr, input int wdata, input byte wmask);
      |reg [31:0] read_data;
      |always @(*) begin
      |  if (read_enable) begin // 有读写请求时
      |    read_data = pmem_read(read_addr);
      |    if (write_enable) begin // 有写请求时
      |      pmem_write(write_addr, write_data, write_mask);
      |    end
      |  end
      |  else begin
      |    read_data = 0;
      |  end
      |end
    """.stripMargin
  )
}
