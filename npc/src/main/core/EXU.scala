package core

import chisel3._
import chisel3.util._

import Constants_Val._
import core.IO._
import chisel3.util.Mux1H
import chisel3.util.MuxLookup

class EXU extends Module {
  val io = IO(new Bundle {
    val in   = Flipped(Decoupled(new DecoderO))
    val reg1 = (new RegReadIO)
    val reg2 = (new RegReadIO)
    val csr  = (new CSRReadIO)
    // val csr_mstvec=Input(UInt(CVAL.DLEN.W))
    val out = (Decoupled(new EXU_O))
  })
  //in
  io.in.ready:=true.B
  val in_regbits = RegNext(io.in.bits)
  val in_regvalid = RegNext(io.in.valid)

  io.out.valid:=in_regvalid
  //pass_throughs
  io.out.bits.mem_read_enable  := in_regbits.mem_read_enable
  io.out.bits.mem_read_type    := in_regbits.mem_read_type
  io.out.bits.mem_write_enable := in_regbits.mem_write_enable
  io.out.bits.mem_write_type   := in_regbits.mem_write_type
  io.out.bits.pc               := in_regbits.pc //using!
  io.out.bits.ecall            := in_regbits.ecall
  io.out.bits.pc_jump          := in_regbits.pc_jump
  io.out.bits.is_branch        := in_regbits.is_branch
  io.out.bits.reg_w_addr       := in_regbits.rd
  io.out.bits.reg_w_enable     := in_regbits.reg_write_enable
  io.out.bits.mret             := in_regbits.mret
  io.out.bits.imm              := in_regbits.imm
  io.out.bits.csrrw            := in_regbits.csrrw

  io.reg1.addr := in_regbits.rs1
  io.reg2.addr := in_regbits.rs2
  io.csr.addr  := in_regbits.imm
  val src1 = io.reg1.data
  val src2 = io.reg2.data

  val alu_val1 = Mux(in_regbits.alu_use_pc, in_regbits.pc, src1)
  val alu_val2 = Mux(in_regbits.alu_use_Imm_2, in_regbits.imm, src2)

  val alu = Module(new ALU())

  val comp = Module(new Branch_comp())
//比较单元的输入
  comp.io.src1      := src1
  comp.io.src2      := src2
  comp.io.comp_type := in_regbits.branch_type
  val go_branch = comp.io.result
//alu的输入
  alu.io.in.src1        := alu_val1
  alu.io.in.src2        := alu_val2
  alu.io.in.alu_op_type := in_regbits.alu_op_type

  //csrr_alu
  val or = io.csr.data | src1
  val csr_alu_res = MuxLookup(in_regbits.csr_alu_type, or)(
    Seq(
      CSRALU_Type.or -> or,
      CSRALU_Type.passreg -> src1
    )
  )
  io.out.bits.alu_result  := alu.io.result //alu的运算结果
  io.out.bits.src2        := src2 //TODO:哪里需要？？
  io.out.bits.csr_alu_res := csr_alu_res
  io.out.bits.csr_val     := io.csr.data
  io.out.bits.go_branch   := go_branch

  //Trace
  val trace_exu = Module(new TRACE_EXU)
  trace_exu.io.clock:=clock
  trace_exu.io.valid:=in_regvalid
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

//TODO:exu完成计算-valid信号
class TRACE_EXU extends BlackBox with HasBlackBoxInline {
  val io = IO(new Bundle {
    val valid  = Input(Bool())
    val clock = Input(Clock())
  })
    setInline(
    "trace_exu.v",
    """import "DPI-C" function void trace_exu();
      |module TRACE_EXU(
      |  input valid,
      |  input clock
      |);
      | reg prev;
      | initial prev=1'b0;
      |always @(negedge clock) begin
      |   if (valid&&prev==1'b0) begin
      |      trace_exu();
      |  end
      | prev = valid;
      | end
      |endmodule
    """.stripMargin
  )
}