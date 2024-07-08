package core.IO
import chisel3._
import Constants_Val._

object ALU_Op extends ChiselEnum {
  val add, sub, xor, or, and, sll, srl, sra, slt, sltu = Value
}

class DecoderO extends Bundle {
  val rs1 = UInt(5.W)
  val rs2 = UInt(5.W)
  val rd  = UInt(5.W)
  val imm = UInt(Constants_Val.CVAL.DLEN.W)
  //选择alu的输入/输出
  val alu_use_Imm_2    = Bool()
  val alu_use_pc       = Bool()
  val alu_op_type      = ALU_Op()
  val pc_jump          = Bool()
  val reg_write_enable = Bool()
  val ebreak           = Bool()
}
