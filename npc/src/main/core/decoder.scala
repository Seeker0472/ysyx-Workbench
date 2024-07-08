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
  val Inst_Type:Inst_Type_Enum.Type,
  val name_in: String = "Not Implemented!",
  val func7:   BitPat = BitPat.dontCare(7),
  val func3:   BitPat = BitPat.dontCare(3),
  val opcode:  BitPat)
    extends DecodePattern {
  def bitPat: BitPat = func7 ## BitPat.dontCare(10) ## func3 ## BitPat.dontCare(5) ## opcode
  def name:   String = name_in
}


object InstType extends DecodeField[InsP,Inst_Type_Enum.Type]{
  def name:String = "InstType"
  override def chiselType = Inst_Type_Enum()
  def genTable(op:InsP): BitPat={
    val immType = op.Inst_Type
    BitPat(immType.litValue.U((immType.getWidth).W))
    // op.opcode.toString() match {
    //  case "BitPat(0110011)" => Inst_Type_Enum.R_Type
    // //  case "0110011" => Inst_Type_Enum.R_Type
    // }
  }
}
class Decoder extends Module {
  val io = IO(new Bundle {
    val instr = Input(UInt((CVAL.ILEN).W))
    val Reg1  = new RegReadIO
    val Reg2  = new RegReadIO
    val out   = Output(new DecoderO)
  })
  val Patterns = Seq(
    //block1
    InsP(name_in = "add",Inst_Type=Inst_Type_Enum.R_Type, opcode  = BitPat("b0110011"), func3 = BitPat("b000"), func7 = BitPat("b0000000")),
    InsP(name_in = "sub",Inst_Type=Inst_Type_Enum.R_Type, opcode  = BitPat("b0110011"), func3 = BitPat("b000"), func7 = BitPat("b0100000")),
    InsP(name_in = "xor",Inst_Type=Inst_Type_Enum.R_Type, opcode  = BitPat("b0110011"), func3 = BitPat("b100"), func7 = BitPat("b0000000")),
    InsP(name_in = "or",Inst_Type=Inst_Type_Enum.R_Type, opcode   = BitPat("b0110011"), func3 = BitPat("b110"), func7 = BitPat("b0000000")),
    InsP(name_in = "and",Inst_Type=Inst_Type_Enum.R_Type, opcode  = BitPat("b0110011"), func3 = BitPat("b111"), func7 = BitPat("b0000000")),
    InsP(name_in = "sll",Inst_Type=Inst_Type_Enum.R_Type, opcode  = BitPat("b0110011"), func3 = BitPat("b001"), func7 = BitPat("b0000000")),
    InsP(name_in = "srl",Inst_Type=Inst_Type_Enum.R_Type, opcode  = BitPat("b0110011"), func3 = BitPat("b101"), func7 = BitPat("b0000000")),
    InsP(name_in = "sra",Inst_Type=Inst_Type_Enum.R_Type, opcode  = BitPat("b0110011"), func3 = BitPat("b101"), func7 = BitPat("b0100000")),
    InsP(name_in = "slt",Inst_Type=Inst_Type_Enum.R_Type, opcode  = BitPat("b0110011"), func3 = BitPat("b010"), func7 = BitPat("b0000000")),
    InsP(name_in = "sltu",Inst_Type=Inst_Type_Enum.R_Type, opcode = BitPat("b0110011"), func3 = BitPat("b011"), func7 = BitPat("b0000000")),
    //block2
    InsP(name_in = "addi",Inst_Type=Inst_Type_Enum.I_Type, opcode = BitPat("b0010011"), func3 = BitPat("b000")),
    InsP(name_in = "xori",Inst_Type=Inst_Type_Enum.I_Type, opcode = BitPat("b0010011"), func3 = BitPat("b100")),
    InsP(name_in = "ori",Inst_Type=Inst_Type_Enum.I_Type, opcode  = BitPat("b0010011"), func3 = BitPat("b110")),
    InsP(name_in = "andi",Inst_Type=Inst_Type_Enum.I_Type, opcode = BitPat("b0010011"), func3 = BitPat("b111")),
    InsP(name_in = "slli",Inst_Type=Inst_Type_Enum.I_Type, opcode = BitPat("b0010011"), func3 = BitPat("b001"), func7 = BitPat("b0000000")),
    //imm[5:11]=0x00
    InsP(name_in = "srli",Inst_Type=Inst_Type_Enum.I_Type, opcode = BitPat("b0010011"), func3 = BitPat("b101"), func7 = BitPat("b0000000")),
    //imm[5:11]=0x00
    InsP(name_in = "srai",Inst_Type=Inst_Type_Enum.I_Type, opcode = BitPat("b0010011"), func3 = BitPat("b101"), func7 = BitPat("b0100000")),
    //imm[5:11]=0x20
    InsP(name_in = "slti",Inst_Type=Inst_Type_Enum.I_Type, opcode  = BitPat("b0010011"), func3 = BitPat("b010")),
    InsP(name_in = "sltiu",Inst_Type=Inst_Type_Enum.I_Type, opcode = BitPat("b0010011"), func3 = BitPat("b011")),
    //block3
    InsP(name_in = "lb",Inst_Type=Inst_Type_Enum.I_Type, opcode  = BitPat("b0000011"), func3 = BitPat("b000")),
    InsP(name_in = "lh",Inst_Type=Inst_Type_Enum.I_Type, opcode  = BitPat("b0000011"), func3 = BitPat("b001")),
    InsP(name_in = "lw",Inst_Type=Inst_Type_Enum.I_Type, opcode  = BitPat("b0000011"), func3 = BitPat("b010")),
    InsP(name_in = "lbu",Inst_Type=Inst_Type_Enum.I_Type, opcode = BitPat("b0000011"), func3 = BitPat("b100")),
    InsP(name_in = "lhu",Inst_Type=Inst_Type_Enum.I_Type, opcode = BitPat("b0000011"), func3 = BitPat("b101")),
    //block4
    InsP(name_in = "sb",Inst_Type=Inst_Type_Enum.S_Type ,opcode = BitPat("b0100011"), func3 = BitPat("b000")),
    InsP(name_in = "sh",Inst_Type=Inst_Type_Enum.S_Type , opcode = BitPat("b0100011"), func3 = BitPat("b001")),
    InsP(name_in = "sw",Inst_Type=Inst_Type_Enum.S_Type ,opcode = BitPat("b0100011"), func3 = BitPat("b010")),
    //block5
    InsP(name_in = "beq",Inst_Type=Inst_Type_Enum.B_Type , opcode  = BitPat("b1100011"), func3 = BitPat("b000")),
    InsP(name_in = "bne",Inst_Type=Inst_Type_Enum.B_Type , opcode  = BitPat("b1100011"), func3 = BitPat("b001")),
    InsP(name_in = "blt",Inst_Type=Inst_Type_Enum.B_Type , opcode  = BitPat("b1100011"), func3 = BitPat("b100")),
    InsP(name_in = "bge",Inst_Type=Inst_Type_Enum.B_Type , opcode  = BitPat("b1100011"), func3 = BitPat("b101")),
    InsP(name_in = "blut",Inst_Type=Inst_Type_Enum.B_Type , opcode = BitPat("b1100011"), func3 = BitPat("b110")),
    InsP(name_in = "bgeu", Inst_Type=Inst_Type_Enum.B_Type ,opcode = BitPat("b1100011"), func3 = BitPat("b111")),
    //block5
    InsP(name_in = "jal",Inst_Type=Inst_Type_Enum.J_Type , opcode  = BitPat("b1101111")),
    InsP(name_in = "jalr",Inst_Type=Inst_Type_Enum.I_Type, opcode = BitPat("b1100111"), func3 = BitPat("b000")),
    //block6
    InsP(name_in = "lui",Inst_Type=Inst_Type_Enum.U_Type, opcode   = BitPat("b0110111")),
    InsP(name_in = "auipc",Inst_Type=Inst_Type_Enum.U_Type,  opcode = BitPat("b0010111")),
    //blocks
    InsP(name_in = "ecall/break",Inst_Type=Inst_Type_Enum.I_Type, opcode = BitPat("b1110011"))
    // InsP(name_in = "ebreak", opcode = BitPat("0010111"))
  )

  //Imms
  val immI = io.instr(31, 20)
  val immS = Cat(io.instr(31, 25), io.instr(11, 7))
  val immB = Cat(io.instr(31, 31), io.instr(7, 7), io.instr(11, 7), io.instr(30, 25), io.instr(11, 8), 0.U(1.W))
  val immU = Cat(io.instr(31, 12), 0.U(12.W))
  val immJ = Cat(io.instr(31, 31), io.instr(19, 12), io.instr(20, 20), io.instr(30, 21), 0.U(1.W))

  val opcode = io.instr(6, 0)
  //   val func3 = io.instr(14,12)
  //   val func7 = io.instr(31,25)

  io.Reg1.no := io.instr(19, 15)
  io.Reg2.no := io.instr(24, 20)
  val Rval1 = io.Reg1.data
  val Rval2 = io.Reg2.data
  val rd    = io.instr(11, 7)
  
  val decoder =  new DecodeTable(Patterns,Seq(InstType)).decode(io.instr)
  val Type = decoder(InstType)
    val src2 = MuxLookup(Type, 0.U)(
    Seq(
      Inst_Type_Enum.R_Type -> Rval2, // R-Type
       Inst_Type_Enum.I_Type -> immI, // I-type
       Inst_Type_Enum.S_Type -> immS, // S-type
       Inst_Type_Enum.B_Type -> immB, // B-type
       Inst_Type_Enum.U_Type -> immU, // U-type
       Inst_Type_Enum.J_Type -> immJ // J-type
    )
  )


  // val src2 = MuxLookup(opcode, 0.U)(
  //   Seq(
  //     "b0110011".U -> Rval2, // R-Type
  //     "b0010011".U -> immI, // I-type-Normal
  //     "b0000011".U -> immI, // I-type-Load
  //     "b1100111".U -> immI, // I-type-jalr
  //     "b1110011".U -> immI, // I-type-ecall/break
  //     "b0100011".U -> immS, // S-type
  //     "b1100011".U -> immB, // B-type
  //     "b0110111".U -> immU, // U-type
  //     "b1101111".U -> immJ // J-type
  //   )
  // )
  val src1 = MuxLookup(opcode, Rval1) {
    Seq(
      "b1101111".U -> 0.U //J-Type Set0
    )
  }
  io.out.src1 := src1
  io.out.src2 := src2
  io.out.rd   := rd

}
