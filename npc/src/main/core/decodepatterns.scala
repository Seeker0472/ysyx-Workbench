package core

import chisel3._
import chisel3.util._
import chisel3.util.BitPat
import chisel3.util.experimental.decode.DecodeField
import chisel3.util.experimental.decode._

case class InsP(
  val Inst_Type: Inst_Type_Enum.Type,
  val name_in:   String = "Not Implemented!",
  val func7:     BitPat = BitPat.dontCare(7),
  val rs2:       BitPat = BitPat.dontCare(5),
  val rs1:       BitPat = BitPat.dontCare(5),
  val func3:     BitPat = BitPat.dontCare(3),
  val rd:     BitPat = BitPat.dontCare(5),
  val opcode:    BitPat)
    extends DecodePattern {
  // def bitPat: BitPat = func7 ## rs2 ## rs1 ## func3 ## rd ## opcode
  def bitPat: BitPat = func7 ## rs2 ## rs1 ## func3 ## rd ## opcode
  // def pattern: BitPat = func7 ## BitPat.dontCare(10) ## func3 ## BitPat.dontCare(5) ## opcode
  def name: String = name_in
}

object decodePatterns {
  val Patterns = Seq(
    //block1
    InsP(
      name_in   = "add",
      Inst_Type = Inst_Type_Enum.R_Type,
      opcode    = BitPat("b0110011"),
      func3     = BitPat("b000"),
      func7     = BitPat("b0000000")
    ),
    InsP(
      name_in   = "sub",
      Inst_Type = Inst_Type_Enum.R_Type,
      opcode    = BitPat("b0110011"),
      func3     = BitPat("b000"),
      func7     = BitPat("b0100000")
    ),
    InsP(
      name_in   = "xor",
      Inst_Type = Inst_Type_Enum.R_Type,
      opcode    = BitPat("b0110011"),
      func3     = BitPat("b100"),
      func7     = BitPat("b0000000")
    ),
    InsP(
      name_in   = "or",
      Inst_Type = Inst_Type_Enum.R_Type,
      opcode    = BitPat("b0110011"),
      func3     = BitPat("b110"),
      func7     = BitPat("b0000000")
    ),
    InsP(
      name_in   = "and",
      Inst_Type = Inst_Type_Enum.R_Type,
      opcode    = BitPat("b0110011"),
      func3     = BitPat("b111"),
      func7     = BitPat("b0000000")
    ),
    InsP(
      name_in   = "sll",
      Inst_Type = Inst_Type_Enum.R_Type,
      opcode    = BitPat("b0110011"),
      func3     = BitPat("b001"),
      func7     = BitPat("b0000000")
    ),
    InsP(
      name_in   = "srl",
      Inst_Type = Inst_Type_Enum.R_Type,
      opcode    = BitPat("b0110011"),
      func3     = BitPat("b101"),
      func7     = BitPat("b0000000")
    ),
    InsP(
      name_in   = "sra",
      Inst_Type = Inst_Type_Enum.R_Type,
      opcode    = BitPat("b0110011"),
      func3     = BitPat("b101"),
      func7     = BitPat("b0100000")
    ),
    InsP(
      name_in   = "slt",
      Inst_Type = Inst_Type_Enum.R_Type,
      opcode    = BitPat("b0110011"),
      func3     = BitPat("b010"),
      func7     = BitPat("b0000000")
    ),
    InsP(
      name_in   = "sltu",
      Inst_Type = Inst_Type_Enum.R_Type,
      opcode    = BitPat("b0110011"),
      func3     = BitPat("b011"),
      func7     = BitPat("b0000000")
    ),
    //block2
    InsP(name_in = "addi", Inst_Type = Inst_Type_Enum.I_Type, opcode = BitPat("b0010011"), func3 = BitPat("b000")),
    InsP(name_in = "xori", Inst_Type = Inst_Type_Enum.I_Type, opcode = BitPat("b0010011"), func3 = BitPat("b100")),
    InsP(name_in = "ori", Inst_Type  = Inst_Type_Enum.I_Type, opcode = BitPat("b0010011"), func3 = BitPat("b110")),
    InsP(name_in = "andi", Inst_Type = Inst_Type_Enum.I_Type, opcode = BitPat("b0010011"), func3 = BitPat("b111")),
    InsP(
      name_in   = "slli",
      Inst_Type = Inst_Type_Enum.I_Type,
      opcode    = BitPat("b0010011"),
      func3     = BitPat("b001"),
      func7     = BitPat("b0000000")
    ),
    //imm[5:11]=0x00
    InsP(
      name_in   = "srli",
      Inst_Type = Inst_Type_Enum.I_Type,
      opcode    = BitPat("b0010011"),
      func3     = BitPat("b101"),
      func7     = BitPat("b0000000")
    ),
    //imm[5:11]=0x00
    InsP(
      name_in   = "srai",
      Inst_Type = Inst_Type_Enum.I_Type,
      opcode    = BitPat("b0010011"),
      func3     = BitPat("b101"),
      func7     = BitPat("b0100000")
    ),
    //imm[5:11]=0x20
    InsP(name_in = "slti", Inst_Type  = Inst_Type_Enum.I_Type, opcode = BitPat("b0010011"), func3 = BitPat("b010")),
    InsP(name_in = "sltiu", Inst_Type = Inst_Type_Enum.I_Type, opcode = BitPat("b0010011"), func3 = BitPat("b011")),
    //block3
    InsP(name_in = "lb", Inst_Type  = Inst_Type_Enum.I_Type, opcode = BitPat("b0000011"), func3 = BitPat("b000")),
    InsP(name_in = "lh", Inst_Type  = Inst_Type_Enum.I_Type, opcode = BitPat("b0000011"), func3 = BitPat("b001")),
    InsP(name_in = "lw", Inst_Type  = Inst_Type_Enum.I_Type, opcode = BitPat("b0000011"), func3 = BitPat("b010")),
    InsP(name_in = "lbu", Inst_Type = Inst_Type_Enum.I_Type, opcode = BitPat("b0000011"), func3 = BitPat("b100")),
    InsP(name_in = "lhu", Inst_Type = Inst_Type_Enum.I_Type, opcode = BitPat("b0000011"), func3 = BitPat("b101")),
    //block4
    InsP(name_in = "sb", Inst_Type = Inst_Type_Enum.S_Type, opcode = BitPat("b0100011"), func3 = BitPat("b000")),
    InsP(name_in = "sh", Inst_Type = Inst_Type_Enum.S_Type, opcode = BitPat("b0100011"), func3 = BitPat("b001")),
    InsP(name_in = "sw", Inst_Type = Inst_Type_Enum.S_Type, opcode = BitPat("b0100011"), func3 = BitPat("b010")),
    //block5
    InsP(name_in = "beq", Inst_Type  = Inst_Type_Enum.B_Type, opcode = BitPat("b1100011"), func3 = BitPat("b000")),
    InsP(name_in = "bne", Inst_Type  = Inst_Type_Enum.B_Type, opcode = BitPat("b1100011"), func3 = BitPat("b001")),
    InsP(name_in = "blt", Inst_Type  = Inst_Type_Enum.B_Type, opcode = BitPat("b1100011"), func3 = BitPat("b100")),
    InsP(name_in = "bge", Inst_Type  = Inst_Type_Enum.B_Type, opcode = BitPat("b1100011"), func3 = BitPat("b101")),
    InsP(name_in = "bltu", Inst_Type = Inst_Type_Enum.B_Type, opcode = BitPat("b1100011"), func3 = BitPat("b110")),
    InsP(name_in = "bgeu", Inst_Type = Inst_Type_Enum.B_Type, opcode = BitPat("b1100011"), func3 = BitPat("b111")),
    //block5
    InsP(name_in = "jal", Inst_Type  = Inst_Type_Enum.J_Type, opcode = BitPat("b1101111")),
    InsP(name_in = "jalr", Inst_Type = Inst_Type_Enum.I_Type, opcode = BitPat("b1100111"), func3 = BitPat("b000")),
    //block6
    InsP(name_in = "lui", Inst_Type   = Inst_Type_Enum.U_Type, opcode = BitPat("b0110111")),
    InsP(name_in = "auipc", Inst_Type = Inst_Type_Enum.U_Type, opcode = BitPat("b0010111")),
    //blocks
    InsP(
      name_in   = "ebreak",
      Inst_Type = Inst_Type_Enum.I_Type,
      opcode    = BitPat("b1110011"),
      func3     = BitPat("b000"),
      rs2       = BitPat("b00001"),
      func7     = BitPat("b0000000")
    ),
    //csrs
    InsP(
      name_in   = "ecall",
      Inst_Type = Inst_Type_Enum.I_Type,
      opcode    = BitPat("b1110011"),
      func3     = BitPat("b000"),
      func7     = BitPat("b0000000"),
      rs2       = BitPat("b00000")
    ),
    InsP(name_in = "csrrs", Inst_Type = Inst_Type_Enum.I_Type, opcode = BitPat("b1110011"), func3 = BitPat("b010")),
    InsP(name_in = "csrrw", Inst_Type = Inst_Type_Enum.I_Type, opcode = BitPat("b1110011"), func3 = BitPat("b001")),
    InsP(
      name_in   = "mret",
      Inst_Type = Inst_Type_Enum.R_Type,
      opcode    = BitPat("b1110011"),
      func3     = BitPat("b000"),
      func7     = BitPat("b0011000")
    ),
    InsP(
      name_in   = "fence.i",
      Inst_Type = Inst_Type_Enum.I_Type,
      opcode    = BitPat("b0001111"),
      func3     = BitPat("b001"),
      func7     = BitPat("b0000000"),
      // rs1       = BitPat("b00000"),
      rs2       = BitPat("b00000")
    )
    // InsP(name_in = "ebreak", opcode = BitPat("0010111"))
  )
}
