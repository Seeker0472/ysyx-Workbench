package core

import chisel3._
import chisel3.util._
import os.stat
import Constants_Val.CVAL

// import os.write
// import chisel3.Output

class core extends Module {
  val io = IO(new Bundle {
    val pc    = Output(UInt(CVAL.DLEN.W))
    val value = Output(UInt(CVAL.DLEN.W))
    val addr  = Input(UInt(CVAL.DLEN.W))
    val instr = Input(UInt(CVAL.ILEN.W))
  })
  val pc = RegInit("h80000000".U(CVAL.DLEN.W))
  io.pc := pc

  val src1 = Wire(UInt(CVAL.DLEN.W))
  val src2 = Wire(UInt(CVAL.DLEN.W))
  val rd  = Wire(UInt(5.W))
  // val addi     = Reg(Bool())
  val write_en = false.B

  // val src1 = Wire(UInt(32.W))
  val res  = Wire(UInt(32.W))

  val decoder = Module(new Decoder())
  val alu     = Module(new ALU())
  val reg     = Module(new REG())
  val br_han  = Module(new ebreak_handler())

  decoder.io.instr := io.instr
  alu.io.in.src1       := decoder.io.out.src1
  alu.io.in.src2       := decoder.io.out.src2
  // rs1              := decoder.io.out.rs1
  rd               := decoder.io.out.rd
  // br_han.io.halt   := decoder.io.ebreak

  // reg.io.read_i := rs1
  src1          := reg.io.read

  // alu.io.src1 := src1  
  // alu.io.addi := addi
  // res      := alu.io
  io.value := res

  reg.io.write_i  := rd
  reg.io.write    := res
  reg.io.write_en := true.B
  pc    := pc + 4.U

  // //stages
  // val sFetch :: sDecode :: sRead :: sExecute :: sWriteBack :: Nil = Enum(5)
  // val state                                                       = RegInit(sFetch)
  // switch(state) {
  //   is(sFetch) {
  //     state := sDecode
  //   }
  //   is(sDecode) { // decode_stage!!!
  //     state := sRead
  //   }
  //   is(sRead) {
  //     // fetch_reg
  //     state := sExecute
  //   }
  //   is(sExecute) {
  //     //run!!
  //     state := sWriteBack
  //   }
  //   is(sWriteBack) {
  //     //update
  //     state := sExecute
  //   }
  // }
}
