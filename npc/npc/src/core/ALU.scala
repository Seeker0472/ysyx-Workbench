package core

import chisel3._
import core.IO._
import chisel3.util.BitPat
import chisel3.util.MuxLookup
import Constants_Val._

class MULUnitIO extends Bundle {
  val src1     = Input(UInt(Constants_Val.CVAL.DLEN.W))
  val src2     = Input(UInt(Constants_Val.CVAL.DLEN.W))
  val unsigned = Input(Bool())
  val res      = Output(UInt(64.W))
}

class DIVUnitIO extends Bundle {
  val src1     = Input(UInt(Constants_Val.CVAL.DLEN.W))
  val src2     = Input(UInt(Constants_Val.CVAL.DLEN.W))
  val unsigned = Input(Bool())
  val res      = Output(UInt(32.W))
}

class ALU extends Module {
  val io = IO(new Bundle {
    val in     = Input(new ALU_I)
    val result = Output(UInt(Constants_Val.CVAL.DLEN.W))
  })
  val add_val  = io.in.src1.asSInt + io.in.src2.asSInt
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

  val unsigned =
    io.in.alu_op_type == ALU_Op.mulhu || io.in.alu_op_type == ALU_Op.mulhsu || io.in.alu_op_type == ALU_Op.divu || io.in.alu_op_type == ALU_Op.remu

  val mul_unit = Module(new MulUnit)
  val div_unit = Module(new DivUnit)
  val rem_unit = Module(new REMUnit)
  mul_unit.io.src1     := io.in.src1
  mul_unit.io.src2     := io.in.src2
  div_unit.io.src1     := io.in.src1
  div_unit.io.src2     := io.in.src2
  rem_unit.io.src1     := io.in.src1
  rem_unit.io.src2     := io.in.src2
  mul_unit.io.unsigned := unsigned.B
  div_unit.io.unsigned := unsigned.B
  rem_unit.io.unsigned := unsigned.B
  val mul  = mul_unit.io.res(31, 0)
  val mulh = mul_unit.io.res(63, 31)
  val div  = div_unit.io.res
  val rem  = rem_unit.io.res

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
      ALU_Op.pass_imm -> pass_imm,
      ALU_Op.mul -> mul,
      ALU_Op.mulh -> mulh,
      ALU_Op.mulhu -> mulh,
      ALU_Op.div -> div,
      ALU_Op.divu -> div,
      ALU_Op.rem -> rem,
      ALU_Op.remu -> rem

      // ALU_Op.slli.asUInt ->  slli
    )
  )
  io.result := res
}

class MulUnit extends Module {
  val io              = IO(new MULUnitIO)
  val result_unsigned = io.src1 * io.src2
  val result_signed   = (io.src1.asSInt * io.src2.asSInt).asUInt
  val result          = Mux(io.unsigned, result_unsigned, result_signed)
  io.res := result
}

class DivUnit extends Module {
  val io              = IO(new DIVUnitIO)
  val result_unsigned = io.src1 / io.src2
  val result_signed   = (io.src1.asSInt / io.src2.asSInt).asUInt
  val result          = Mux(io.unsigned, result_unsigned, result_signed)
  io.res := result
}

class REMUnit extends Module {
  val io              = IO(new DIVUnitIO)
  val result_unsigned = io.src1 % io.src2
  val result_signed   = (io.src1.asSInt % io.src2.asSInt).asUInt
  val result          = Mux(io.unsigned, result_unsigned, result_signed)
  io.res := result
}
