package bus

import chisel3._
import chisel3.util._
import _root_.core.IO.AXIReadIO
import Constants_Val._

class CLINT extends Module {
  val io                                                = IO(new AXIReadIO)
  val s_r_idle :: s_r_read_data :: s_r_wait_data :: Nil = Enum(3)

  val r_state = RegInit(s_r_idle) //读状态
  val counter = RegInit(0.U(64.W))
  r_state := MuxLookup(r_state, s_r_idle)(
    List(
      s_r_idle -> Mux(io.RA.valid, s_r_read_data, s_r_idle), //等待地址
      s_r_read_data -> Mux(io.RD.ready, s_r_idle, s_r_read_data) //返回数据
    )
  )
  counter := counter + 1.U

  io.RD.bits.data  := Mux(io.RA.bits.addr(2, 2) === 1.U, counter(63, 32), counter(31, 0))
  io.RD.bits.rresp := 0.U
  io.RD.valid      := r_state === s_r_read_data
  io.RD.bits.id    := 0.U //TODO!!!
  io.RD.bits.last  := r_state === s_r_read_data
  io.RA.ready      := true.B

}

// class CLINT extends Module {
//   val io                                                = IO(new AXIReadIO)
//   val s_r_idle :: s_r_read_data :: s_r_wait_data :: Nil = Enum(3)

//   val r_state = RegInit(s_r_idle) //读状态
//   val r_data  = Reg(UInt(CVAL.DLEN.W))
//   r_state := MuxLookup(r_state, s_r_idle)(
//     List(
//       s_r_idle -> Mux(io.RA.valid, s_r_read_data, s_r_idle), //等待地址
//       s_r_read_data -> Mux(io.RD.ready, s_r_idle, s_r_read_data) //返回数据
//     )
//   )
//   val raddr = Module(new DPI_C_ReadAddr)
//   raddr.io.enable := io.RA.valid
//   raddr.io.clock  := clock
//   raddr.io.read_addr:=io.RA.bits.addr
//   r_data           := raddr.io.read_data

//   io.RD.bits.data  := r_data
//   io.RD.bits.rresp := 0.U
//   io.RD.valid      := r_state === s_r_read_data
//   io.RA.ready      := true.B

// }

// class DPI_C_ReadAddr extends BlackBox with HasBlackBoxInline {
//   val io = IO(new Bundle {
//     val read_data = Output(UInt(CVAL.DLEN.W))
//     val read_addr = Input(UInt(CVAL.DLEN.W))
//     val enable    = Input(Bool())
//     val clock     = Input(Clock())
//   })
//   setInline(
//     "dpi_c_ra.v",
//     """import "DPI-C" function int get_time(input int read_addr);
//       |module DPI_C_ReadAddr(
//       |  input [31:0] read_addr,
//       |  output reg [31:0] read_data,
//       |  input enable,
//       |  input clock
//       |);
//       |always @(negedge clock) begin
//       |  if (enable) begin // 有读写请求时
//       |    read_data = get_time(read_addr);
//       |  end
//       |end
//       |endmodule
//     """.stripMargin
//   )
// }
// class DPI_C_ReadAddr extends Module {
//   val io = IO(new Bundle {
//     val read_data = Output(UInt(CVAL.DLEN.W))
//     val read_addr = Input(UInt(CVAL.DLEN.W))
//     val enable    = Input(Bool())
//     val clock     = Input(Clock())
//   })
//   io.read_data:=1.U

// }
