package core

import chisel3._
import Constants_Val._
import core.IO._
import chisel3.util.Mux1H

class EXU extends Module {
  val io = IO(new Bundle {
    val in = Input(new EXU_I)
    val out = Output(new EXU_O)
  })
  val alu_val1 = Mux(io.in.alu_use_pc,io.in.pc,io.in.src1)
  val alu_val2 = Mux(io.in.alu_use_Imm_2,io.in.imm,io.in.src1)

  val alu = Module(new ALU)
  alu.io.in.src1        := alu_val1
  alu.io.in.src2        := alu_val2
  alu.io.in.alu_op_type := io.in.alu_op_type

  //如果要实现Memw，应该在这里加一个Mux和控制信号
  val result = alu.io.result
  val pc_plus4= io.in.pc+4.U
  val next_pc = Mux(io.in.pc_jump,result,pc_plus4)
  io.out.reg_out := Mux(io.in.pc_jump,pc_plus4,alu.io.result)
  io.out.n_pc := next_pc
//   val 

}
