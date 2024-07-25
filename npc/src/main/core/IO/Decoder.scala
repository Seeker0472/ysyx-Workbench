package core.IO
import chisel3._
import Constants_Val._

object ALU_Op extends ChiselEnum {
  val inv, add, sub, xor, or, and, sll, srl, sra, slt, sltu,pass_imm = Value
}

object Load_Type extends ChiselEnum {
  val inv, lb, lh, lw, lbu, lhu = Value
}
object Store_Type extends ChiselEnum {
  val inv, sb, sh, sw = Value
}

object Branch_Type extends ChiselEnum {
  val inv, beq, bne, blt, bge, bltu, bgeu = Value
}

class DecoderO extends Bundle {
  val rs1 = UInt(5.W)
  val rs2 = UInt(5.W)
  val rd  = UInt(5.W)
  val imm = UInt(CVAL.DLEN.W)
  //选择alu的输入/输出
  val alu_use_Imm_2    = Bool()
  val alu_use_pc       = Bool()
  val alu_op_type      = ALU_Op()
  val pc_jump          = Bool()
  val reg_write_enable = Bool()
  val ebreak           = Bool()
  
  val mem_read_enable  = Bool()
  val mem_read_type    = Load_Type()
  val mem_write_enable = Bool()
  val mem_write_type   = Store_Type()

  val is_branch        = Bool()
  val branch_type      = Branch_Type()

}
