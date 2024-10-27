package core.IO
import chisel3._
import Constants_Val._

object ALU_Op extends ChiselEnum {
  val inv, add, sub, xor, or, and, sll, srl, sra, slt, sltu, pass_imm = Value
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

object CSRALU_Type extends ChiselEnum {
  val passreg, or = Value
}

class DecoderO extends Bundle {
  val pc = Output(UInt(CVAL.DLEN.W))

  val src1     = Output(UInt(32.W))
  val src2     = Output(UInt(32.W))
  val csr_data = Output(UInt(32.W))
  val rd       = Output(UInt(5.W))
  val func3    = Output(UInt(3.W))
  val imm      = Output(UInt(CVAL.DLEN.W))
  //选择alu的输入/输出
  val alu_use_Imm_2    = Output(Bool())
  val alu_use_pc       = Output(Bool())
  val alu_op_type      = Output(ALU_Op())
  val pc_jump          = Output(Bool())
  val reg_write_enable = Output(Bool())
  // val ebreak           = Bool()

  val mem_read_enable  = Output(Bool())
  val mem_write_enable = Output(Bool())

  val is_branch = Output(Bool())

  val csrrw        = Output(Bool())
  val csr_alu_type = Output(CSRALU_Type())

  val ecall = Output(Bool())
  val mret  = Output(Bool())
  val flush_icache   = Output(Bool())
   val ebreak         = Output(Bool())
}
