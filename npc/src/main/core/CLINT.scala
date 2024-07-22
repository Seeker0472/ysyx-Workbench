package core

import chisel3._
import chisel3.util._
import _root_.core.IO.AXIReadIO
import Constants_Val._


class CLINT extends Module {
    val io=IO(new AXIReadIO)
  val s_r_idle :: s_r_read_data :: s_r_wait_data :: Nil = Enum(3)

  val r_state = RegInit(s_r_idle) //读状态
  val r_data = Reg(UInt(CVAL.DLEN.W))
  r_state := MuxLookup(r_state, s_r_idle)(
    List(
      s_r_idle -> Mux(io.RA.valid, s_r_read_data, s_r_idle), //等待地址
      // s_r_wait_data -> Mux(true.B, s_r_read_data, s_r_wait_data), //访问存储器
    //   s_r_wait_data -> Mux(true.B, s_r_read_data, s_r_wait_data), //访问存储器
      s_r_read_data -> Mux(io.RD.ready, s_r_idle, s_r_read_data) //返回数据
    )
  )
  when(io.RA.valid){
    //TODO:DPI-C->r_data
    r_data:=0.U
  }
  io.RD.bits.data:=r_data
  io.RD.bits.rresp:=true.B
  io.RD.valid:=r_state===s_r_read_data
  io.RA.ready:=true.B

}
