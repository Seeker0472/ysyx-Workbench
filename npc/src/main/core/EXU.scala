package core

import chisel3._
import Constants_Val._
import core.IO._
import chisel3.util.Mux1H
import chisel3.util.MuxLookup

class EXU extends Module {
  val io = IO(new Bundle {
    val in   = Flipped(new DecoderO)
    val reg1 = (new RegReadIO)
    val reg2 = (new RegReadIO)
    val csr  = (new CSRReadIO)
    // val csr_mstvec=Input(UInt(CVAL.DLEN.W))
    val out = Output(new EXU_O)
  })
  //pass_throughs
  io.out.mem_read_enable  := io.in.mem_read_enable
  io.out.mem_read_type    := io.in.mem_read_type
  io.out.mem_write_enable := io.in.mem_write_enable
  io.out.mem_write_type   := io.in.mem_write_type
  io.out.pc               := io.in.pc //using!
  io.out.ecall            := io.in.ecall
  io.out.pc_jump          := io.in.pc_jump
  io.out.is_branch        := io.in.is_branch
  io.out.reg_w_addr       := io.in.rd
  io.out.reg_w_enable     := io.in.reg_write_enable
  io.out.mret             := io.in.mret
  io.out.imm              := io.in.imm
  io.out.csrrw            := io.in.csrrw

  io.reg1.addr := io.in.rs1
  io.reg2.addr := io.in.rs2
  io.csr.addr  := io.in.imm
  val src1 = io.reg1.data
  val src2 = io.reg2.data

  val alu_val1 = Mux(io.in.alu_use_pc, io.in.pc, src1)
  val alu_val2 = Mux(io.in.alu_use_Imm_2, io.in.imm, src2)

  val alu = Module(new ALU())

  val comp = Module(new Branch_comp())
//比较单元的输入
  comp.io.src1      := src1
  comp.io.src2      := src2
  comp.io.comp_type := io.in.branch_type
  val go_branch = comp.io.result
//alu的输入
  alu.io.in.src1        := alu_val1
  alu.io.in.src2        := alu_val2
  alu.io.in.alu_op_type := io.in.alu_op_type

  //csrr_alu
  val or = io.csr.data | src1
  val csr_alu_res = MuxLookup(io.in.csr_alu_type, or)(
    Seq(
      CSRALU_Type.or -> or,
      CSRALU_Type.passreg -> src1
    )
  )
  io.out.alu_result  := alu.io.result //alu的运算结果
  io.out.src2        := src2 //TODO:哪里需要？？
  io.out.csr_alu_res := csr_alu_res
  io.out.csr_val     := io.csr.data
  io.out.go_branch   := go_branch
}

class Branch_comp extends Module {
  val io = IO(new Bundle {
    val src1      = Input(UInt(CVAL.DLEN.W))
    val src2      = Input(UInt(CVAL.DLEN.W))
    val comp_type = Input(Branch_Type())
    val result    = Output(Bool())
  })
  io.result := MuxLookup(io.comp_type, false.B)(
    Seq(
      Branch_Type.beq -> (io.src1 === io.src2),
      Branch_Type.bne -> (io.src1 =/= io.src2),
      Branch_Type.blt -> (io.src1.asSInt < io.src2.asSInt),
      Branch_Type.bge -> (io.src1.asSInt >= io.src2.asSInt),
      Branch_Type.bltu -> (io.src1 < io.src2),
      Branch_Type.bgeu -> (io.src1 >= io.src2)
    )
  )
}
