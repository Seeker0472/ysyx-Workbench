package core

import chisel3._
import chisel3.util._
import Constants_Val.CVAL
import core.IO._

import chisel3.util.BitPat
import chisel3.util.experimental.decode.DecodeField
import chisel3.util.experimental.decode._
//TODO::Decoder API0
object Inst extends ChiselEnum {
  val inv, add, jal, sub, xor, or, and, sll, srl, sra, slt, lh = Value
}
object Inst_Type_Enum extends ChiselEnum {
  val R_Type, I_Type, S_Type, B_Type, U_Type, J_Type = Value
}

case class InsP(
  val Inst_Type: Inst_Type_Enum.Type,
  val name_in:   String = "Not Implemented!",
  val func7:     BitPat = BitPat.dontCare(7),
  val func3:     BitPat = BitPat.dontCare(3),
  val opcode:    BitPat)
    extends DecodePattern {
  def bitPat: BitPat = func7 ## BitPat.dontCare(10) ## func3 ## BitPat.dontCare(5) ## opcode
  def name:   String = name_in
}

object InstType extends DecodeField[InsP, Inst_Type_Enum.Type] {
  def name: String = "InstType"
  override def chiselType = Inst_Type_Enum()
  def genTable(op: InsP): BitPat = {
    val immType = op.Inst_Type
    BitPat(immType.litValue.U((immType.getWidth).W))
  }
}
//src2是否选择Imm
object Use_IMM_2 extends BoolDecodeField[InsP] {
  def name: String = "Use_IMM"
  // override def chiselType = Inst_Type_Enum()
  def genTable(op: InsP)= {
    if(op.Inst_Type==Inst_Type_Enum.I_Type||op.Inst_Type==Inst_Type_Enum.S_Type||op.Inst_Type==Inst_Type_Enum.J_Type)
      y else n
  }
}
//src1是否选择PC -- J-Type & B-Type
object Use_PC_1 extends BoolDecodeField[InsP] {
  def name: String = "Use_PC_1"
  // override def chiselType = Inst_Type_Enum()
  def genTable(op: InsP)= {
    if(op.Inst_Type==Inst_Type_Enum.J_Type||op.Inst_Type==Inst_Type_Enum.B_Type)
      y else n
  }
}

//是否是无条件跳转
object Is_Jump extends BoolDecodeField[InsP] {
  def name: String = "Is_Jump"
  // override def chiselType = Inst_Type_Enum()
  def genTable(op: InsP)= {
    if(op.Inst_Type==Inst_Type_Enum.J_Type||op.opcode==BitPat("b1100111"))
      y else n
  }

}

//Reg_write_Enable
object R_Write_Enable extends BoolDecodeField[InsP] {
  def name: String = "Reg_W_En"
  // override def chiselType = Inst_Type_Enum()
  def genTable(op: InsP)= {
    if(op.Inst_Type==Inst_Type_Enum.S_Type||op.Inst_Type==Inst_Type_Enum.B_Type)
      n else y
  }
}

object Is_Ebreak extends BoolDecodeField[InsP] {
  def name: String = "Is_Ebreak"
  // override def chiselType = Inst_Type_Enum()
  def genTable(op: InsP)= {
    // if(op.opcode===BitPat("b1110011")&&op.func3===BitPat("b000")&&op.func7===BitPat("b0000001"))
      // y else n
    if(op.bitPat==BitPat("b??????????????000?????1110011"))
      y else n
    // if(op.name=="ecall/break")
    //   y else n

  }
}



class Decoder extends Module {
  val io = IO(new Bundle {
    val instr = Input(UInt((CVAL.ILEN).W))
    // val Reg1  = new RegReadIO
    // val Reg2  = new RegReadIO
    val out = Output(new DecoderO)
  })
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
    InsP(name_in = "blut", Inst_Type = Inst_Type_Enum.B_Type, opcode = BitPat("b1100011"), func3 = BitPat("b110")),
    InsP(name_in = "bgeu", Inst_Type = Inst_Type_Enum.B_Type, opcode = BitPat("b1100011"), func3 = BitPat("b111")),
    //block5
    InsP(name_in = "jal", Inst_Type  = Inst_Type_Enum.J_Type, opcode = BitPat("b1101111")),
    InsP(name_in = "jalr", Inst_Type = Inst_Type_Enum.I_Type, opcode = BitPat("b1100111"), func3 = BitPat("b000")),
    //block6
    InsP(name_in = "lui", Inst_Type   = Inst_Type_Enum.U_Type, opcode = BitPat("b0110111")),
    InsP(name_in = "auipc", Inst_Type = Inst_Type_Enum.U_Type, opcode = BitPat("b0010111")),
    //blocks
    InsP(name_in = "ecall/break", Inst_Type = Inst_Type_Enum.I_Type, opcode = BitPat("b1110011"))
    // InsP(name_in = "ebreak", opcode = BitPat("0010111"))
  )

  //Imms
  val imm_I_Raw = io.instr(31, 20)
  val immI = Cat(Fill(20, imm_I_Raw(11)), imm_I_Raw)
  val imm_S_Raw = Cat(io.instr(31, 25), io.instr(11, 7))
  val immS  = Cat(Fill(20, imm_S_Raw(11)), imm_S_Raw)
  val imm_B_Raw = Cat(io.instr(31, 31), io.instr(7, 7), io.instr(11, 7), io.instr(30, 25), io.instr(11, 8), 0.U(1.W))
  val immB = Cat(Fill(19, imm_B_Raw(12)), imm_B_Raw)
  val imm_U_Raw = Cat(io.instr(31, 12), 0.U(12.W))
  val immU = imm_U_Raw
  val imm_J_Raw = Cat(io.instr(31, 31), io.instr(19, 12), io.instr(20, 20), io.instr(30, 21), 0.U(1.W))
  val immJ = Cat(Fill(11, imm_J_Raw(20)), imm_J_Raw)

  // val opcode = io.instr(6, 0)
  val rs1 = io.instr(19, 15)
  val rs2 = io.instr(24, 20)
  val rd  = io.instr(11, 7)

  val decodedResults = new DecodeTable(Patterns, Seq(InstType,Use_IMM_2,Use_PC_1,Is_Jump,R_Write_Enable,Is_Ebreak)).decode(io.instr)
  val Type    = decodedResults(InstType)
  val imm = MuxLookup(Type, 0.U)(
    Seq(
      // Inst_Type_Enum.R_Type -> Rval2, // R-Type
      Inst_Type_Enum.I_Type -> immI, // I-type
      Inst_Type_Enum.S_Type -> immS, // S-type
      Inst_Type_Enum.B_Type -> immB, // B-type
      Inst_Type_Enum.U_Type -> immU, // U-type
      Inst_Type_Enum.J_Type -> immJ // J-type
    )
  )
  io.out.rs1 := rs1
  io.out.rs2 := rs2
  io.out.rd  := rd
  io.out.imm := imm

  //控制逻辑
  io.out.alu_use_Imm_2 := decodedResults(Use_IMM_2)
  io.out.alu_use_pc := decodedResults(Use_PC_1)
  
  //目前只用实现加法
  io.out.alu_op_type := ALU_Op.add
  io.out.pc_jump := decodedResults(Is_Jump)
  io.out.reg_write_enable := decodedResults(R_Write_Enable)
  
  io.out.ebreak:=decodedResults(Is_Ebreak)

}
