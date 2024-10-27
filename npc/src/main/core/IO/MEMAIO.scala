package core.IO

import chisel3._
import Constants_Val._

class MEMA_O extends Bundle {
  val pc = Output(UInt(CVAL.DLEN.W))

  val ecall           = Output(Bool())
  val csr_alu_res     = Output(UInt(CVAL.DLEN.W))
  val mem_read_enable = Output(Bool())
  val mem_read_result = Output(UInt(CVAL.DLEN.W))
  val csrrw           = Output(Bool())
  val csr_val         = Output(UInt(CVAL.DLEN.W))
  // val alu_result      = Output(UInt(CVAL.DLEN.W))
  val exu_result      = Output(UInt(CVAL.DLEN.W))
  val pc_jump         = Output(Bool())
  val go_branch       = Output(Bool())

  val reg_w_addr   = Output(UInt(CVAL.REG_ADDR_LEN.W))
  val reg_w_enable = Output(Bool())
  val mret         = Output(Bool())
  val imm          = Output(UInt(CVAL.DLEN.W))
    val flush_icache   = Output(Bool())
   val ebreak         = Output(Bool())

}
