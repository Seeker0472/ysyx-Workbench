package core

import chisel3._
import chisel3.util._
import Constants_Val._

class AXI extends Module {
  val io    = IO((new AXIIO))
  val raddr = Reg(UInt(CVAL.ILEN.W))
  val waddr = Reg(UInt(CVAL.ILEN.W))

  val DPI_C_MEM = Module(new MEM)

  val s_r_idle :: s_r_read_data :: s_r_wait_data :: Nil = Enum(3)

  val r_state = RegInit(s_r_idle)
  val r_addr  = Reg(UInt(CVAL.DLEN.W))
  val r_data  = Reg(UInt(CVAL.DLEN.W))

  r_state := MuxLookup(r_state, s_r_idle)(
    Seq(
      s_r_idle -> Mux(io.RA.valid, s_r_read_data, s_r_idle), //等待地址
      s_r_wait_data -> Mux(true.B, s_r_read_data, s_r_wait_data), //要模拟延迟
      s_r_read_data -> Mux(io.RD.ready, s_r_idle, s_r_read_data) //返回数据
    )
  )
  io.RA.ready := r_state === s_r_idle
  io.RD.valid := r_state === s_r_read_data
  when(io.RA.valid) {
    r_addr := io.RA.bits.addr
  }
  //取数据
  DPI_C_MEM.io.clock       := clock
  DPI_C_MEM.io.read_addr   := r_addr
  DPI_C_MEM.io.read_enable := r_state === s_r_wait_data
  r_data                   := DPI_C_MEM.io.read_data
  //无关信号
  DPI_C_MEM.io.write_addr   := 0.U
  DPI_C_MEM.io.write_enable := false.B
  DPI_C_MEM.io.write_mask   := 0.U

  io.RD.bits.rresp:=false.B//异常-暂时不实现

  when(r_state === s_r_read_data) {
    io.RD.bits.data := r_data //取到的数据
  }

}

class AXIIO extends Bundle {
//   //Write address
//   val WA = Decoupled(new Bundle {
//     val addr = Input(UInt(CVAL.DLEN.W))
//     //awport-特权相关
//   })
//   //Write data
//   val WD = Decoupled(new Bundle {
//     val data  = Input(UInt(CVAL.DLEN.W))
//     val wstrb = Input(UInt(8.W)) //掩码
//   })
//   //Write response
//   val WR = Decoupled(new Bundle {
//     val bresp = Output(Bool())
//   })
  //Read address
  val RA = Flipped(Decoupled(new Bundle {
    val addr = (UInt(CVAL.DLEN.W))
    //arport-特权相关
  }))
  //Read data
  val RD = (Decoupled(new Bundle {
    val data  = (UInt(CVAL.DLEN.W))
    val rresp = (Bool())
  }))
}
