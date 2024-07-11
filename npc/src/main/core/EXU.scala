package core

import chisel3._
import Constants_Val._
import core.IO._
import chisel3.util.Mux1H
import chisel3.util.MuxLookup

class EXU extends Module {
  val io = IO(new Bundle {
    val in  = Input(new EXU_I)
    val out = Output(new EXU_O)
  })
  val alu_val1 = Mux(io.in.alu_use_pc, io.in.pc, io.in.src1)
  val alu_val2 = Mux(io.in.alu_use_Imm_2, io.in.imm, io.in.src1)

  val mem = Module(new MEM()) //TODO::::::把Mem模块放在执行单元是否科学？？？

  val alu = Module(new ALU)
  alu.io.in.src1        := alu_val1
  alu.io.in.src2        := alu_val2
  alu.io.in.alu_op_type := io.in.alu_op_type

  //mem R/W
  mem.io.read_enable  := io.in.mem_read_enable
  mem.io.write_enable := io.in.mem_write_enable
  //TODO: 这里需要设计两个信号吗
  mem.io.read_addr  := alu.io.result
  mem.io.write_addr := alu.io.result
  val mrres = mem.io.read_data

  //注意符号拓展！！！
  val mem_read_result_sint = MuxLookup(io.in.mem_read_type, 0.S)(
    Seq(
      Load_Type.lb -> mrres(7, 0).asSInt,
      Load_Type.lh -> mrres(15, 0).asSInt,
      Load_Type.lw -> mrres(31, 0).asSInt,
      Load_Type.lbu -> mrres(7, 0).zext,
      Load_Type.lhu -> mrres(15, 0).zext
    )
  )
  val mem_read_result = mem_read_result_sint.asUInt

  val mem_write_mask =MuxLookup(io.in.mem_write_type,0.U)(Seq(
    Store_Type.sb -> 0x000000ff.U(CVAL.DLEN.W),
    Store_Type.sh -> 0x0000ffff.U(CVAL.DLEN.W),
    Store_Type.sw -> 0xffffffff.U(CVAL.DLEN.W),
  ))
  mem.io.write_mask:=mem_write_mask
  mem.io.write_data :=io.in.src2

  //如果是store，Reg_Write_Enable应该是False
  // val result   = alu.io.result
  val result   = Mux(io.in.mem_read_enable, mem_read_result, alu.io.result)
  val pc_plus4 = io.in.pc + 4.U
  val next_pc  = Mux(io.in.pc_jump, result, pc_plus4)
  io.out.reg_out := Mux(io.in.pc_jump, pc_plus4, alu.io.result)
  io.out.n_pc    := next_pc
}
