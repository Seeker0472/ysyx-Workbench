package core

import chisel3._
import chisel3.util._
import os.stat
import Constants_Val.CVAL
import core.IO.StageConnect
import bus.AXI_Lite_Arbiter

class ypc extends Module {
  val io = IO(new Bundle {
    val master    = (new master_io)
    val slave     = Flipped(new master_io)
    val interrupt = Input(Bool()) // TODO
  })

  val decoder     = Module(new Decoder())
  val reg         = Module(new REG())
  val br_han      = Module(new ebreak_handler())
  val ifu         = Module(new IFU())
  val exu         = Module(new EXU())
  val lsu         = Module(new LSU())
  val wbu         = Module(new WBU())
  val axi_arbiter = Module(new AXI_Lite_Arbiter())
  val hazard_unit = Module(new HazardUnit())

  val flush_pipeline = hazard_unit.io.flush || wbu.io.flush_icache
  //ifu
  StageConnect(wbu.io.out, ifu.io.in, flush_pipeline, "pipeline")
  ifu.io.axi            <> axi_arbiter.io.c1
  hazard_unit.io.ifu_pc <> ifu.io.ifu_pc
  flush_pipeline        <> ifu.io.flush_pipeline
  //decode_stage
  StageConnect(ifu.io.out, decoder.io.in, flush_pipeline, "pipeline")
  // br_han.io.halt      := decoder.io.ebreak
  // ifu.io.flush_icache := decoder.io.flush_icache
  decoder.io.reg1           <> reg.io.Rread1
  decoder.io.reg2           <> reg.io.Rread2
  decoder.io.csr            <> reg.io.CSRread
  hazard_unit.io.decoder_pc <> decoder.io.decoder_pc
  flush_pipeline            <> decoder.io.flush_pipeline
  //exu
  StageConnect(decoder.io.out, exu.io.in, flush_pipeline, "pipeline")
  flush_pipeline        <> exu.io.flush_pipeline
  hazard_unit.io.exu_pc <> exu.io.pc
  decoder.io.forwarding <> exu.io.forwarding
  //lsu
  lsu.io.axi <> axi_arbiter.io.c2
  StageConnect(exu.io.out, lsu.io.in, flush_pipeline, "pipeline_state")
  // lsu.io.forwarding<>decoder.io.forwarding
  //pipeline of lsu inside the module with state machine

  //wbu
  StageConnect(lsu.io.out, wbu.io.in, flush_pipeline, "multi")
  wbu.io.csr_mstvec   := reg.io.csr_mstvec
  reg.io.Rwrite       <> wbu.io.Rwrite
  reg.io.CSRwrite     <> wbu.io.CSR_write
  hazard_unit.io.wbu  <> wbu.io.wbu_pc
  br_han.io.halt      := wbu.io.ebreak
  ifu.io.flush_icache := wbu.io.flush_icache

  //pipeline sig
  decoder.io.lsu_w_addr <> lsu.io.reg_addr
  decoder.io.exu_w_addr <> exu.io.reg_addr

  // axi_connection_master
  axi_arbiter.io.out.WA.ready := io.master.awready
  io.master.awvalid           := axi_arbiter.io.out.WA.valid
  io.master.awaddr            := axi_arbiter.io.out.WA.bits.addr
  io.master.awid              := 0.U
  io.master.awlen             := 0.U
  io.master.awsize            := axi_arbiter.io.out.WA.bits.size
  io.master.awburst           := 1.U

  axi_arbiter.io.out.WD.ready := io.master.wready
  io.master.wvalid            := axi_arbiter.io.out.WD.valid
  io.master.wdata             := axi_arbiter.io.out.WD.bits.data
  io.master.wstrb             := axi_arbiter.io.out.WD.bits.wstrb
  io.master.wlast             := true.B

  io.master.bready                 := true.B
  axi_arbiter.io.out.WR.valid      := io.master.bvalid
  axi_arbiter.io.out.WR.bits.bresp := io.master.bresp

  axi_arbiter.io.out.RA.ready := io.master.arready
  io.master.arvalid           := axi_arbiter.io.out.RA.valid
  io.master.araddr            := axi_arbiter.io.out.RA.bits.addr
  io.master.arid              := axi_arbiter.io.out.RA.bits.id
  io.master.arlen             := axi_arbiter.io.out.RA.bits.len
  io.master.arsize            := axi_arbiter.io.out.RA.bits.size
  io.master.arburst           := 1.U

  io.master.rready                 := axi_arbiter.io.out.RD.ready
  axi_arbiter.io.out.RD.valid      := io.master.rvalid
  axi_arbiter.io.out.RD.bits.data  := io.master.rdata
  axi_arbiter.io.out.RD.bits.rresp := io.master.rresp
  axi_arbiter.io.out.RD.bits.id    := io.master.rid
  axi_arbiter.io.out.RD.bits.last  := io.master.rlast

  // slave
  io.slave.awready := 0.U
  io.slave.wready  := 0.U
  io.slave.bvalid  := 0.U
  io.slave.bresp   := 0.U
  io.slave.bid     := 0.U
  io.slave.arready := 0.U
  io.slave.rvalid  := 0.U
  io.slave.rresp   := 0.U
  io.slave.rdata   := 0.U
  io.slave.rlast   := 0.U
  io.slave.rid     := 0.U

  ifu.io.rwerr := (io.master.bresp =/= 0.U && io.master.bvalid) || (io.master.rresp =/= 0.U && io.master.rvalid) // 出错跳转到0=

}

class master_io extends Bundle {
  val awready = Input(Bool())
  val awvalid = Output(Bool())
  val awaddr  = Output(UInt(32.W))
  val awid    = Output(UInt(4.W)) // Write ID
  val awlen   = Output(UInt(8.W)) // Burst length
  val awsize  = Output(UInt(3.W)) // Burst size---0b101---32
  val awburst = Output(UInt(2.W)) // Burst type

  val wready = Input(Bool())
  val wvalid = Output(Bool())
  val wdata  = Output(UInt(CVAL.DLEN.W))
  val wstrb  = Output(UInt(4.W)) // Write strobes
  val wlast  = Output(Bool()) // the last transfer in a write burst---set to 1

  val bready = Output(Bool())
  val bvalid = Input(Bool())
  val bresp  = Input(UInt(2.W)) // Write response
  val bid    = Input(UInt(4.W)) // Write ID

  val arready = Input(Bool())
  val arvalid = Output(Bool())
  val araddr  = Output(UInt(32.W))
  val arid    = Output(UInt(4.W))
  val arlen   = Output(UInt(8.W))
  val arsize  = Output(UInt(3.W))
  val arburst = Output(UInt(2.W))

  val rready = Output(Bool())
  val rvalid = Input(Bool())
  val rresp  = Input(UInt(2.W))
  val rdata  = Input(UInt(CVAL.DLEN.W))
  val rlast  = Input(Bool()) // for arbiter
  val rid    = Input(UInt(4.W))
}
