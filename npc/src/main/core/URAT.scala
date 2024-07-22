package core

import chisel3._
import chisel3.util._
import Constants_Val._
import core.IO._

class URAT extends Module {
  val io = IO(new AXIWriteIO)
  //TODO:DPI_C
  val w_addr = Reg(UInt(CVAL.DLEN.W))
  val w_data = Reg(UInt(CVAL.DLEN.W))
  val s_w_idle :: s_w_wait_data :: s_w_wait_result :: s_w_valid :: Nil = Enum(4)

  val w_state = RegInit(s_w_idle) //写状态
  w_state := MuxLookup(w_state, s_w_idle)(
    List(
      s_w_idle -> Mux(io.WA.valid, s_w_wait_data, s_w_idle), //等待地址
      s_w_wait_data -> Mux(io.WD.valid, s_w_wait_result, s_w_wait_data), //等待数据(在这一周期直接调用DPI-C获取)
      s_w_wait_result -> Mux(true.B, s_w_valid, s_w_wait_result), //访问存储器，其实是为了模拟延迟
      // s_w_wait_result -> Mux(true.B, s_w_valid, s_w_wait_result), //访问存储器，其实是为了模拟延迟
      s_w_valid -> Mux(io.WR.ready, s_w_idle, s_w_valid) //返回结果
    )
  )
  io.WA.ready:=true.B
  io.WD.ready:=true.B
  io.WR.valid:=true.B
  val send=(w_state===s_w_wait_data)
  // io.WR.bits.bresp=true.B//TODO

      // BitPat("b00010000000000000000????????????") -> BitPat(MEM_Area.URAT.asUInt),
      // BitPat("b10000000????????????????????????") -> BitPat(MEM_Area.SRAM.asUInt)      
  
}
