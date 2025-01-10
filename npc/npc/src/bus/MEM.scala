package bus

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
    val write_mask   = Input(UInt(8.W))
    val clock        = Input(Clock())
  })

  setInline(
    "mem_access.v",
    """import "DPI-C" function int pmem_read(input int read_addr);
      |import "DPI-C" function void pmem_write(
      |input int write_addr, input int write_data, input byte write_mask);
      |module MEM(
      |  input [31:0] read_addr,
      |  output reg [31:0] read_data,
      |  input [31:0] write_addr,
      |  input [31:0] write_data,
      |  input [7:0] write_mask,
      |  input  write_enable,
      |  input  read_enable,
      |input clock
      |);
      |always @(negedge clock) begin
      |  if (read_enable) begin // 有读写请求时
      |    read_data = pmem_read(read_addr);
      |  end
      |  else begin
      |    read_data = 0;
      |  end
      |    if (write_enable) begin // 有写请求时
      |      pmem_write(write_addr, write_data, write_mask);
      |    end
      |end
      |endmodule
    """.stripMargin
  )
}

// class MEM extends Module{
//   val io = IO(new Bundle {
//     val read_addr   = Input(UInt(CVAL.DLEN.W))
//     val read_enable = Input(Bool())
//     val read_data   = Output(UInt(CVAL.DLEN.W))

//     val write_enable = Input(Bool())
//     val write_addr   = Input(UInt(CVAL.DLEN.W))
//     val write_data   = Input(UInt(CVAL.DLEN.W))
//     val write_mask   = Input(UInt(8.W))
//     val clock        = Input(Clock())

//   })
//   //   // 创建一个256x32位的同步读写内存
//   // val mem = SyncReadMem(256, UInt(32.W))

//   // // 写操作
//   // when(io.write_enable) {
//   //   mem.write(io.write_addr, io.write_data&io.write_mask)
//   // }

//   // // 读操作
//   // io.read_data := mem.read(io.read_addr, (!io.write_enable)&&io.read_enable)

// }
