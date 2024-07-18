package core.IO

import chisel3._
import Constants_Val._

class EXU_I extends Bundle {
  val src1          = UInt(CVAL.DLEN.W)
  val src2          = UInt(CVAL.DLEN.W)
  val imm           = UInt(CVAL.DLEN.W)
  val pc            = UInt(CVAL.DLEN.W)
  val alu_use_Imm_2 = Bool()
  val alu_use_pc    = Bool()
  val alu_op_type   = ALU_Op()
  val pc_jump       = Bool()

  val mem_read_enable  = Bool()
  val mem_read_type    = Load_Type()
  val mem_write_enable = Bool()
  val mem_write_type   = Store_Type()

  val is_branch   = Bool()
  val branch_type = Branch_Type()
//TODO:宽度！！！！！！

//csr寄存器的值
  val csr_val = UInt(CVAL.DLEN.W)
//允许写入csr寄存器
  val csrrw        = Bool()
  val csr_alu_type = CSRALU_Type()

  val ecall = Bool()
  val mret  = Bool()
//mstvec的值
  val csr_mstvec   = UInt(CVAL.DLEN.W)
}

class EXU_O extends Bundle {
  val reg_out = UInt(CVAL.DLEN.W)
  val n_pc    = UInt(CVAL.DLEN.W)
  val csr_res = UInt(CVAL.DLEN.W)
  //TODO:Write_ENABLE!!

}
