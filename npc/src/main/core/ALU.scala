package core

import chisel3._
import core.IO._
import chisel3.util.BitPat
import chisel3.util.MuxLookup
import Constants_Val._

class ALU extends Module {
  val io = IO(new Bundle {
    val in = Input(new ALU_I)
    val result = Output(UInt(Constants_Val.CVAL.DLEN.W))
  })
// // 默认情况下，dst 输出为 0
//   io.dst := 0.U

//   // 当 addi 信号为高时，执行加法运算
//   when(io.addi) {
//     io.dst := io.src1 + io.imm
//   }
  val add_val = io.in.src1 + io.in.src2
  val sub_val = io.in.src1 - io.in.src2
  val xor     = io.in.src1 ^ io.in.src2
  val or      = io.in.src1 | io.in.src2
  val and     = io.in.src1 & io.in.src2
  val sll     = io.in.src1 & io.in.src2
  val slli    = io.in.src1 & (io.in.src2 & "B1111".U)
  val res = MuxLookup(io.in.alu_op_type, 0.U)(
    Seq(
      ALU_Op.add -> add_val,
      ALU_Op.sub -> sub_val,
      ALU_Op.xor -> xor,
      ALU_Op.or -> or,
      ALU_Op.and -> and,
      ALU_Op.sll -> sll
      // ALU_Op.slli.asUInt ->  slli
    )
  )
  io.result := res
}
