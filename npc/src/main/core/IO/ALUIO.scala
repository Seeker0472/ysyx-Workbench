package core.IO

import Constants_Val._
import chisel3._


class ALU_I extends Module {
    val src1 = UInt(CVAL.DLEN.W)
    val src2 = UInt(CVAL.DLEN.W)
    val operation = UInt(CVAL.DEC_RES_LRN.W)
}