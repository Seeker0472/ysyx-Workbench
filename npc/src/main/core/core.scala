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
    val pc    = Output(UInt(CVAL.DLEN.W))
    val value = Output(UInt(CVAL.DLEN.W))
    val addr  = Input(UInt(CVAL.DLEN.W))
    val instr = Input(UInt(CVAL.ILEN.W))
  })

  val decoder = Module(new Decoder())
  val reg     = Module(new REG())
  val br_han  = Module(new ebreak_handler())
  val ifu     = Module(new IFU())
  val exu     = Module(new EXU())

  //fetch_inst
  io.pc          := ifu.io.pc
  ifu.io.instr_i := io.instr

  //decode
  decoder.io.instr := ifu.io.instr

  //r/w_reg
  reg.io.read_No_1 := decoder.io.out.rs1
  exu.io.in.src1   := reg.io.read_1
  reg.io.read_No_2 := decoder.io.out.rs1
  exu.io.in.src2   := reg.io.read_2
  reg.io.write_No  := decoder.io.out.rd

  exu.io.in.imm := decoder.io.out.imm
  exu.io.in.pc := ifu.io.pc

  //pass_cont_sig to EXU
  exu.io.in.alu_use_Imm_2 := decoder.io.out.alu_use_Imm_2
  exu.io.in.alu_use_pc    := decoder.io.out.alu_use_pc
  exu.io.in.alu_op_type   := decoder.io.out.alu_op_type
  exu.io.in.pc_jump       := decoder.io.out.pc_jump
  //Write_ENABLE!!
  reg.io.write_en := decoder.io.out.reg_write_enable
//ebreak
  br_han.io.halt:=decoder.io.out.ebreak


  io.value:=exu.io.out.reg_out

  //exu
  ifu.io.next_pc        := exu.io.out.n_pc
  reg.io.reg_write_data := exu.io.out.reg_out


}
