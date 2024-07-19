package core

import chisel3._
import chisel3.util._
import os.stat
import Constants_Val.CVAL

// import os.write
// import chisel3.Output
//*******************************************************#
// TODO:重构这个模块，最好只包含实例化+连线
//*******************************************************#

class core extends Module {
  val io = IO(new Bundle {
    val pc       = Output(UInt(CVAL.DLEN.W))
    val value    = Output(UInt(CVAL.DLEN.W))
    val addr     = Input(UInt(CVAL.DLEN.W))
    val instr    = Input(UInt(CVAL.ILEN.W))
    val inst_now = Output(UInt(CVAL.DLEN.W))
  })

  io.inst_now := io.instr //输出当前指令到Debugger环境---可能以后需要Debug

  val decoder = Module(new Decoder())
  val reg     = Module(new REG())
  val br_han  = Module(new ebreak_handler())
  val ifu     = Module(new IFU())
  val exu     = Module(new EXU())
  val memau   = Module(new MEMAccess())
  val wbu     = Module(new WBU())
  // val mem     = Module(new MEM())

  io.pc          := ifu.io.pc
  ifu.io.instr_i := io.instr
//decode_stage
  decoder.io.instr := ifu.io.instr
//exc
  exu.io.in   := decoder.io.out
  exu.io.reg1 <> reg.io.Rread1
  exu.io.reg2 <> reg.io.Rread2
  exu.io.csr  := reg.io.CSRread
// exu.io.csr_mstvec:=reg.io.csr_mstvec
//mem_access
  memau.io.in := exu.io.out
//wb
  wbu.io.in         := memau.io.out
  wbu.io.csr_mstvec := reg.io.csr_mstvec
  reg.io.Rwrite     := wbu.io.Rwrite
  reg.io.CSRwrite   := wbu.io.CSR_write

  ifu.io.next_pc := wbu.io.out.n_pc

}
