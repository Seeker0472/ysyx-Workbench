package core.IO

import chisel3._
import Constants_Val._

class EXU_I extends Bundle {
  val src1          = UInt(Constants_Val.CVAL.DLEN.W)
  val src2          = UInt(Constants_Val.CVAL.DLEN.W)
  val imm           = UInt(Constants_Val.CVAL.DLEN.W)
  val pc            = UInt(Constants_Val.CVAL.DLEN.W)
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
}

class EXU_O extends Bundle {
  val reg_out = UInt(Constants_Val.CVAL.DLEN.W)
  val n_pc    = UInt(Constants_Val.CVAL.DLEN.W)
  //TODO:Write_ENABLE!!

}
