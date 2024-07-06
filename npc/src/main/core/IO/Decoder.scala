package core.IO
import chisel3._
import Constants_Val.CVAL

class DecoderO extends Bundle{
    val imm   = UInt(CVAL.XLEN.W)
    val rs1    = UInt(5.W)
    val rs2    = UInt(5.W)
    val rd     = UInt(5.W)
    val ebreak = Bool()
    // val addi   = Bool()
    // val ebreak = Bool()
}