package core.IO

import chisel3._
import Constants_Val._

class EXU_O extends Bundle {
  val mem_read_enable  = Output(Bool())
  val mem_write_enable = Output(Bool())
  val alu_result       = Output(UInt(CVAL.DLEN.W))
  val src2             = Output(UInt(CVAL.DLEN.W))
  val func3            = Output(UInt(3.W))

  val pc          = Output(UInt(CVAL.DLEN.W))
  val ecall       = Output(Bool())
  val csr_alu_res = Output(UInt(CVAL.DLEN.W))
  val csrrw       = Output(Bool())
  val csr_val     = Output(UInt(CVAL.DLEN.W))
  val pc_jump     = Output(Bool())
  val go_branch   = Output(Bool())

  val reg_w_addr   = Output(UInt(CVAL.REG_ADDR_LEN.W))
  val reg_w_enable = Output(Bool())
  val mret         = Output(Bool())
  val imm          = Output(UInt(CVAL.DLEN.W))
}
