package core

import chisel3._
import chisel3.util._
import os.stat
// import os.write
// import chisel3.Output

class core extends Module {
  val io = IO(new Bundle {
    val pc    = Output(UInt(32.W))
    val addr  = Input(UInt(32.W))
    val instr = Input(UInt(32.W))
  })
  val pc = RegInit("h80000000".U(32.W))
  io.pc := pc

  //stages
  val sFetch :: sDecode :: sRead :: sExecute :: sWriteBack :: Nil = Enum(5)
  val state                                              = RegInit(sFetch)

  val immI     = Reg(UInt(32.W))
  val rs1      = Reg(UInt(5.W))
  val rd       = Reg(UInt(5.W))
  val addi     = Reg(Bool())
  val write_en = false.B

  val src1 = Reg(UInt(32.W))
  val res  = Reg(UInt(32.W))

  val decoder = Module(new Decoder())
  val alu     = Module(new ALU())
  val reg     = Module(new REG())

  switch(state) {
    is(sFetch){
      state            := sDecode
    }
    is(sDecode) { // decode_stage!!!
      decoder.io.instr := io.instr
      immI             := decoder.io.immI
      rs1              := decoder.io.rs1
      addi             := decoder.io.addi
      rd               := decoder.io.rd
      state            := sRead
    }
    is(sRead) {
      // fetch_reg
      reg.io.read_i := rs1
      src1          := reg.io.read
      state         := sExecute
    }
    is(sExecute) {
      //run!!
      alu.io.src1 := src1
      alu.io.imm  := immI
      alu.io.addi := addi
      res         := alu.io.dst
      state       := sWriteBack
    }
    is(sWriteBack) {
      //update
      reg.io.write_i  := rd
      reg.io.write    := res
      reg.io.write_en := true.B
      pc              := pc + 4.U
      state           := sFetch
    }
  }

}
