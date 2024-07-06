package core

import chisel3._
import chisel3.util._
import Constants_Val.CVAL
import core.IO._

import chisel3.util.BitPat
import chisel3.util.experimental.decode.DecodeField
import chisel3.util.experimental.decode._
//TODO::Decoder API0

case class InstructionPattern(
  val func7:   BitPat = BitPat.dontCare(7),
  val func3:   BitPat = BitPat.dontCare(3),
  val name_in: String = "Not Implemented!",
  val opcode:  BitPat)
    extends DecodePattern {
  def bitPat: BitPat = func7 ## BitPat.dontCare(10) ## func3 ## BitPat.dontCare(5) ## opcode
  def name:   String = name_in
}

case class Field(
  val in_name: String = "Not Implemented!")
    extends BoolDecodeField[InstructionPattern] {
  def name: String = in_name
  def genTable(op: InstructionPattern): BitPat = {
    if (op.name == in_name) y else n
  }
}

object PatternFieldGenerator {
  def generatePatterns(patterns: Seq[(String, BitPat, BitPat, BitPat)]): Seq[InstructionPattern] = {
    patterns.map {
      case (name, func7, func3, opcode) =>
        InstructionPattern(func7, func3, name, opcode)
    }
  }

  def generateFields(patterns: Seq[(String, BitPat, BitPat, BitPat)]): Seq[BoolDecodeField[InstructionPattern]] = {
    patterns.map {
      case (in_name, func7, func3, opcode) =>
        new BoolDecodeField[InstructionPattern] {
          override def name: String = in_name
          override def genTable(op: InstructionPattern): BitPat = {
            if (op.name == in_name) BitPat("b1") else BitPat("b0")
          }
        }
    }
  }
}

class Decoder extends Module {
  val io = IO(new Bundle {
    val instr = Input(UInt((CVAL.XLEN).W))
    val out   = Output(new DecoderO)
  })
  val patternData = Seq(
    ("ebreak", BitPat("b0000000"), BitPat("b000"), BitPat("b1110011")),
    ("nop", BitPat("b0000000"), BitPat("b000"), BitPat("b0000000")),
    ("nop", BitPat("b0000000"), BitPat("b000"), BitPat("b0000000")),
  )
  val bind_sig = Seq(
    (Seq())
  )

  // 生成Patterns和Fields
  val possiblePatterns: Seq[InstructionPattern]                  = PatternFieldGenerator.generatePatterns(patternData)
  val allFields:        Seq[BoolDecodeField[InstructionPattern]] = PatternFieldGenerator.generateFields(patternData)

  // 创建DecodeTable
  val decodeTable = new DecodeTable(possiblePatterns, allFields)

  val decodeResult = decodeTable.decode(io.instr)

  
  //TODO:::::
  
  io.out.ebreak := decodeResult(Field("ebreak"))

  //Imms
  val immI = io.instr(31, 20)
  val immS = Cat(io.instr(31, 25), io.instr(11, 7))
  val immB = Cat(io.instr(31, 31), io.instr(7, 7), io.instr(11, 7), io.instr(30, 25), io.instr(11, 8), 0.U(1.W))
  val immU = Cat(io.instr(31, 12), 0.U(12.W))
  val immJ = Cat(io.instr(31, 31), io.instr(19, 12), io.instr(20, 20), io.instr(30, 21), 0.U(1.W))

  val opcode = io.instr(6, 0)
  //   val func3 = io.instr(14,12)
  //   val func7 = io.instr(31,25)

  io.out.rs1 := io.instr(19, 15)
  io.out.rs2 := io.instr(24, 20)
  io.out.rd  := io.instr(11, 7)

  io.out.imm := MuxLookup(opcode, 0.U)(
    Seq(
      "b0010011".U -> immI, // I-type-Normal
      "b0000011".U -> immI, // I-type-Load
      "b1100111".U -> immI, // I-type-jalr
      "b1110011".U -> immI, // I-type-jalr
      "b0100011".U -> immS, // S-type
      "b1100011".U -> immB, // B-type
      "b0110111".U -> immU, // U-type
      "b1101111".U -> immJ // J-type
    )
  )

//   val mask    = "b00000000000000000111000001111111".U
//   val addival = "b00000000000000000000000000010011".U
//   val ebreak  = "b00000000000100000000000001110011".U
//   io.addi   := (io.instr & mask) === addival
//   io.ebreak := io.instr === ebreak
}
