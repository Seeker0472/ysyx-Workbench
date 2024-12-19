package bus

import chisel3._
import chisel3.util._
import Constants_Val._

import core.IO._
//这个是slave
//TODO:数据和地址应该可以在同一个周期发送！！！！
class AXI_Slave extends Module {
  val io = IO((new AXIIO))
  // val raddr = Reg(UInt(CVAL.ILEN.W))
  // val waddr = Reg(UInt(CVAL.ILEN.W))

  val DPI_C_MEM = Module(new MEM)

  val s_r_idle :: s_r_read_data :: s_r_wait_data :: Nil                = Enum(3)
  val s_w_idle :: s_w_wait_data :: s_w_wait_result :: s_w_valid :: Nil = Enum(4)

  val r_state = RegInit(s_r_idle) //读状态
  val w_state = RegInit(s_w_idle) //写状态

  val r_addr = Reg(UInt(CVAL.DLEN.W))
  val r_data = Reg(UInt(CVAL.DLEN.W))
  val w_addr = Reg(UInt(CVAL.DLEN.W))
  val w_data = Reg(UInt(CVAL.DLEN.W))

  // val read_latency = RegInit(1.U(2.W))
  // read_latency := read_latency <<1|Cat(0.U(1.W),read_latency(1,1))//模拟延迟

  r_state := MuxLookup(r_state, s_r_idle)(
    List(
      s_r_idle -> Mux(io.RA.valid, s_r_wait_data, s_r_idle), //等待地址
      // s_r_wait_data -> Mux(true.B, s_r_read_data, s_r_wait_data), //访问存储器
      // s_r_wait_data -> Mux(read_latency===1.U, s_r_read_data, s_r_wait_data), //访问存储器
      s_r_wait_data -> Mux(true.B, Mux(io.RD.ready, s_r_idle, s_r_read_data), s_r_wait_data), //访问存储器
      s_r_read_data -> Mux(io.RD.ready, s_r_idle, s_r_read_data) //返回数据
    )
  )
  io.RA.ready := r_state === s_r_idle
  io.RD.valid := r_state === s_r_read_data || r_state === s_r_wait_data //单周期获取

  when(io.RA.valid && r_state === s_r_idle) {
    r_addr := io.RA.bits.addr
  }
  w_state := MuxLookup(w_state, s_w_idle)(
    List(
      s_w_idle -> Mux(io.WA.valid, s_w_wait_data, s_w_idle), //等待地址
      s_w_wait_data -> Mux(io.WD.valid, s_w_wait_result, s_w_wait_data), //等待数据(在这一周期直接调用DPI-C获取)
      s_w_wait_result -> Mux(true.B, Mux(io.WR.ready, s_w_idle, s_w_valid), s_w_wait_result), //访问存储器，其实是为了模拟延迟
      // s_w_wait_result -> Mux(read_latency===1.U, s_w_valid, s_w_wait_result), //访问存储器，其实是为了模拟延迟
      // s_w_wait_result -> Mux(true.B, s_w_valid, s_w_wait_result), //访问存储器，其实是为了模拟延迟
      s_w_valid -> Mux(io.WR.ready, s_w_idle, s_w_valid) //返回结果
    )
  )
  when(io.WA.valid && w_state === s_w_idle) {
    w_addr := io.WA.bits.addr
  }
  DPI_C_MEM.io.write_addr   := w_addr
  DPI_C_MEM.io.write_data   := io.WD.bits.data
  DPI_C_MEM.io.write_mask   := io.WD.bits.wstrb
  DPI_C_MEM.io.write_enable := w_state === s_w_wait_data && io.WD.valid //(在等待数据直接调用DPI-C获取)

  io.WR.bits.bresp := true.B //假设一直不出错

  io.WA.ready := w_state === s_w_idle
  io.WD.ready := w_state === s_w_wait_data
  io.WR.valid := w_state === s_w_valid || w_state === s_w_wait_result
  //取数据
  DPI_C_MEM.io.clock       := clock
  DPI_C_MEM.io.read_addr   := r_addr
  DPI_C_MEM.io.read_enable := r_state === s_r_wait_data
  r_data                   := DPI_C_MEM.io.read_data

  io.RD.bits.rresp := false.B //异常-暂时不实现
  io.RD.bits.data  := Mux(r_state === s_w_wait_result, DPI_C_MEM.io.read_data, r_data)

}
