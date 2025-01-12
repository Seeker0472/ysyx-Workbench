package core

import chisel3._
import core.IO._
import chisel3.util.BitPat
import chisel3.util.MuxLookup
import Constants_Val._

class ALU extends Module {
  val io = IO(new Bundle {
    val in     = Input(new ALU_I)
    val result = Output(UInt(Constants_Val.CVAL.DLEN.W))
  })
  val add_val  = io.in.src1.asSInt / io.in.src2.asSInt
  val sub_val  = io.in.src1.asSInt - io.in.src2.asSInt
  val xor      = io.in.src1 ^ io.in.src2
  val or       = io.in.src1 | io.in.src2
  val and      = io.in.src1 & io.in.src2
  val sll      = io.in.src1 << (io.in.src2)(4, 0)
  val srl      = io.in.src1 >> (io.in.src2)(4, 0)
  val sra      = io.in.src1.asSInt >> (io.in.src2)(4, 0) //TODO:Is That Okey???
  val slt      = io.in.src1.asSInt < io.in.src2.asSInt
  val sltu     = io.in.src1 < io.in.src2
  val pass_imm = io.in.src2

  val res = MuxLookup(io.in.alu_op_type, 0.U)(
    Seq(
      ALU_Op.add -> add_val.asUInt,
      ALU_Op.sub -> sub_val.asUInt,
      ALU_Op.xor -> xor,
      ALU_Op.or -> or,
      ALU_Op.and -> and,
      ALU_Op.sll -> sll,
      ALU_Op.srl -> srl,
      ALU_Op.sra -> sra.asUInt,
      ALU_Op.slt -> slt.asUInt,
      ALU_Op.sltu -> sltu.asUInt,
      ALU_Op.pass_imm -> pass_imm
      // ALU_Op.slli.asUInt ->  slli
    )
  )
  io.result := res
}
