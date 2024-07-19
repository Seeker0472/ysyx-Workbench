package core.IO

import chisel3._
import Constants_Val._

class EXU_I extends Bundle {
  val src1 = UInt(CVAL.DLEN.W) //diff
  val src2 = UInt(CVAL.DLEN.W) //diff
//diff
  val imm           = UInt(CVAL.DLEN.W)
  val pc            = UInt(CVAL.DLEN.W) //diff
  val alu_use_Imm_2 = Bool()
  val alu_use_pc    = Bool()
  val alu_op_type   = ALU_Op()
  val pc_jump       = Bool()
//diff
  val mem_read_enable  = Bool()
  val mem_read_type    = Load_Type()
  val mem_write_enable = Bool()
  val mem_write_type   = Store_Type()

  val is_branch   = Bool()
  val branch_type = Branch_Type()
//TODO:宽度！！！！！！

//csr寄存器的值
  val csr_val = UInt(CVAL.DLEN.W) //diff
//允许写入csr寄存器
  val csrrw        = Bool()
  val csr_alu_type = CSRALU_Type()

  val ecall = Bool()
  val mret  = Bool()
//mstvec的值
  val csr_mstvec = UInt(CVAL.DLEN.W) //diff
}

class EXU_O extends Bundle {
  val mem_read_enable  = Output(Bool())
  val mem_read_type    = Output(Load_Type())
  val mem_write_enable = Output(Bool())
  val mem_write_type   = Output(Store_Type())
  val alu_result       = Output(UInt(CVAL.DLEN.W))
  val src2             = Output(UInt(CVAL.DLEN.W))

  val pc          = Output(UInt(CVAL.DLEN.W))
  val ecall       = Output(Bool())
  val csr_alu_res = Output(UInt(CVAL.DLEN.W))
  val csrrw       = Output(Bool())
  val csr_val     = Output(UInt(CVAL.DLEN.W))
  val pc_jump     = Output(Bool())
  val is_branch   = Output(Bool())
  val go_branch   = Output(Bool())

  val reg_w_addr   = Output(UInt(CVAL.REG_ADDR_LEN.W))
  val reg_w_enable = Output(Bool())
  val mret         = Output(Bool())
  val imm          = Output(UInt(CVAL.DLEN.W))
  //old
  // val reg_out = UInt(CVAL.DLEN.W)
  // val n_pc    = UInt(CVAL.DLEN.W)
  // val csr_res = UInt(CVAL.DLEN.W)
  //TODO:Write_ENABLE!!

}
