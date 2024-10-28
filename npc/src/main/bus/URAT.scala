package bus

import chisel3._
import chisel3.util._
import Constants_Val._
import core.IO._

class URAT extends Module {
  val io        = IO(new AXIIO)
  val dpi_c_out = Module(new DPI_C_WriteChar)
  val w_addr    = Reg(UInt(CVAL.DLEN.W))
  val w_data    = Reg(UInt(CVAL.DLEN.W))

  val s_w_idle :: s_w_wait_data :: s_w_wait_result :: s_w_valid :: Nil = Enum(4)

  //以下是时钟
  val clint = Module(new CLINT)
  clint.io.RA <> io.RA
  clint.io.RD <> io.RD

  // 以下是串口

  val w_state = RegInit(s_w_idle) //写状态
  val addr_ok = io.WA.bits.addr === 0x100003f8.U
  w_state := MuxLookup(w_state, s_w_idle)(
    List(
      s_w_idle -> Mux(io.WA.valid && addr_ok, s_w_wait_data, s_w_idle), //等待地址
      s_w_wait_data -> Mux(io.WD.valid, s_w_wait_result, s_w_wait_data), //等待数据(在这一周期直接调用DPI-C获取)
      s_w_wait_result -> Mux(true.B, s_w_valid, s_w_wait_result), //访问存储器，其实是为了模拟延迟
      // s_w_wait_result -> Mux(true.B, s_w_valid, s_w_wait_result), //访问存储器，其实是为了模拟延迟
      s_w_valid -> Mux(io.WR.ready, s_w_idle, s_w_valid) //返回结果
    )
  )
  io.WA.ready         := true.B
  io.WD.ready         := true.B
  io.WR.valid         := true.B
  dpi_c_out.io.enable := (w_state === s_w_wait_data)
  dpi_c_out.io.w_char := io.WD.bits.data(7, 0)
  dpi_c_out.io.clock  := clock
  io.WR.bits.bresp    := true.B //TODO

}

class DPI_C_WriteChar extends BlackBox with HasBlackBoxInline {
  val io = IO(new Bundle {
    val w_char = Input(UInt(8.W))
    val enable = Input(Bool())
    val clock  = Input(Clock())
  })
  setInline(
    "dpi_c_wc.v",
    """import "DPI-C" function void print_char(input byte w_char);
      |module DPI_C_WriteChar(
      |  input [7:0] w_char,
      |  input enable,
      |  input clock
      |);
      |always @(*) begin
      |  if (enable) begin // 有读写请求时
      |    print_char(w_char);
      |  end
      |end
      |endmodule
    """.stripMargin
  )
}

// class DPI_C_WriteChar  extends Module {
//   val io=IO(new Bundle{
//     val w_char = Input(UInt(8.W))
//     val enable = Input(Bool())
//     val clock  = Input(Clock())
//   })

// }
