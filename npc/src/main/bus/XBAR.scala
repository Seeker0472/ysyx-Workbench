package bus

import chisel3._
import chisel3.util._
import core.IO._

import chisel3.util.experimental.decode.DecodeField
import chisel3.util.experimental.decode._
import _root_.circt.stage.CLI

object MEM_Area extends ChiselEnum {
  val INV, SRAM, URAT = Value
}
//TODO: refactor this module
class XBAR extends Module {
  val io = IO(new Bundle {
    val in  = (new AXIReadIO)
    val axi = Flipped(new AXIReadIO)
  })
  val Table = TruthTable(
    Map(
      //TODO：不能取消XBAR，访问非法地址ready信号会直接置低
      BitPat("b0000001000000000????????????????") -> BitPat("b1"), //CLINT
      // BitPat("b10000000????????????????????????") -> BitPat("b0"), //OLD
      // BitPat("b00001111????????????????????????") -> BitPat("b0"), //SRAM
      // BitPat("b00100000000000000000????????????") -> BitPat("b0"), //MROM
      // BitPat("b00010000000000000000????????????") -> BitPat("b0"), //URAT
      // BitPat("b0011????????????????????????????") -> BitPat("b0"), //FLASH
      // BitPat("b00010000000000000001????????????") -> BitPat("b0") //SPI_Master
    ),
    BitPat("b0") //TODO:暂时把所有地址打进总线
  )
  // store the status now
  val mem_r_reg = RegInit(0.U(1.W))
  val mem_r_b   = decoder(io.in.RA.bits.addr, Table) //r_XBar行为
  when(io.in.RA.valid) {
    mem_r_reg := mem_r_b
  }
  val clint = Module(new CLINT)

  //TODO:write请求不需要打进来！
  // io.axi.WA <> io.in.WA
  // io.axi.WD <> io.in.WD
  // io.axi.WR <> io.in.WR

  //选择设备(in),只负责选择valid，其他直接传送
  io.axi.RA.valid       := Mux(mem_r_b === BitPat("b0"), io.in.RA.valid, false.B) //如果选择sram，就开
  clint.io.RA.valid     := Mux(mem_r_b === BitPat("b1"), io.in.RA.valid, false.B)
  // io.axi.RA.bits.addr   := io.in.RA.bits.addr
  // io.axi.RA.bits.size   := io.in.RA.bits.size
  // io.axi.RA.bits.len    := io.in.RA.bits.len
  // io.axi.RA.bits.id     := io.in.RA.bits.id
  io.axi.RA.bits := io.in.RA.bits
  clint.io.RA.bits := io.in.RA.bits
  // clint.io.RA.bits.addr := io.in.RA.bits.addr
  // clint.io.RA.bits.size := io.in.RA.bits.size
  // clint.io.RA.bits.len  := io.in.RA.bits.len
  // clint.io.RA.bits.id   := io.in.RA.bits.id
  io.in.RA.ready := Mux(
    mem_r_b === BitPat("b0") || mem_r_reg === BitPat("b0"),
    io.axi.RA.ready,
    clint.io.RA.ready
  )

  io.axi.RD.ready     := Mux(mem_r_reg === BitPat("b0"), io.in.RD.ready, false.B)
  clint.io.RD.ready   := Mux(mem_r_reg === BitPat("b0"), io.in.RD.ready, false.B)
  // io.in.RD.bits.data  := Mux(mem_r_reg === BitPat("b0"), io.axi.RD.bits.data, clint.io.RD.bits.data)
  // io.in.RD.bits.rresp := Mux(mem_r_reg === BitPat("b0"), io.axi.RD.bits.rresp, clint.io.RD.bits.rresp)
  // io.in.RD.bits.id    := Mux(mem_r_reg === BitPat("b0"), io.axi.RD.bits.id, clint.io.RD.bits.id)
  // io.in.RD.bits.last  := Mux(mem_r_reg === BitPat("b0"), io.axi.RD.bits.last, clint.io.RD.bits.last)  
  io.in.RD.bits  := Mux(mem_r_reg === BitPat("b0"), io.axi.RD.bits, clint.io.RD.bits)

  io.in.RD.valid := Mux(
    mem_r_reg === BitPat("b0"),
    io.axi.RD.valid,
    Mux(mem_r_reg === BitPat("b1"), clint.io.RD.valid, false.B)
  )
}
