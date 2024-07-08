package core.IO
import chisel3._
import Constants_Val._

class DecoderO extends Bundle{
    // val imm   = UInt(CVAL.DLEN.W)
    val src1    = UInt(CVAL.DLEN.W)
    val src2   = UInt(CVAL.DLEN.W)
    // val op     = UInt(5.W)
    val rd     = UInt(5.W)
    // val ebreak = Bool()
    // val operation = UInt(CVAL.DEC_RES_LRN.W)
    // val addi   = Bool()
    // val ebreak = Bool()
}

object Inst extends ChiselEnum {
  val inv, add, jal,sub,xor,or,and,sll,slli,srl,sra,slt,lh,lw,lbu,lhu,sb,sh,sw,beq,bne,blt,bltu,bueu,ebreak = Value
}
