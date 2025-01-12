package core.IO

import Constants_Val._
import chisel3._

class ALU_I extends Bundle {
  val src1        = UInt(Constants_Val.CVAL.DLEN.W)
  val src2        = UInt(Constants_Val.CVAL.DLEN.W)
  val alu_op_type = ALU_Op()

}
