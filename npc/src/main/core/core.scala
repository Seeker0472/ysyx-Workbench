package core

import chisel3._
import chisel3.util._
import os.stat
import Constants_Val.CVAL
import _root_.core.IO.StageConnect

// import os.write
// import chisel3.Output

class core extends Module {
  val io = IO(new Bundle {
    val inst_now = Output(UInt(CVAL.DLEN.W))
  })

  val decoder     = Module(new Decoder())
  val reg         = Module(new REG())
  val br_han      = Module(new ebreak_handler())
  val ifu         = Module(new IFU())
  val exu         = Module(new EXU())
  val memau       = Module(new MEMAccess())
  val wbu         = Module(new WBU())
  val axi_arbiter = Module(new AXI_Lite_Arbiter())

  io.inst_now := ifu.io.inst_now //输出当前指令到Debugger环境---可能以后需要Debug

  ifu.io.axi <> axi_arbiter.io.c1
//decode_stage
  StageConnect(ifu.io.out, decoder.io.in)
  br_han.io.halt := decoder.io.ebreak
//exc
  StageConnect(decoder.io.out, exu.io.in)
  exu.io.reg1 <> reg.io.Rread1
  exu.io.reg2 <> reg.io.Rread2
  exu.io.csr <> reg.io.CSRread
//mem_access
  memau.io.axi <> axi_arbiter.io.c2
  StageConnect(exu.io.out, memau.io.in)

//wb
  StageConnect(memau.io.out, wbu.io.in)
  wbu.io.csr_mstvec := reg.io.csr_mstvec
  reg.io.Rwrite <> wbu.io.Rwrite
  reg.io.CSRwrite <> wbu.io.CSR_write

  StageConnect(wbu.io.out, ifu.io.in)

}
