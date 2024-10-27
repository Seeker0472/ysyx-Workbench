package core

import chisel3._
import chisel3.util._

import Constants_Val._
import core.IO._
import chisel3.util.Mux1H
import chisel3.util.MuxLookup

class EXU extends Module {
  val io = IO(new Bundle {
    val in             = Flipped(Decoupled(new DecoderO))
    val reg_addr       = Output(UInt(5.W))
    val pc             = (Decoupled(UInt(CVAL.DLEN.W)))
    val flush_pipeline = Input(Bool())
    val out            = (Decoupled(new EXU_O))
    val forwarding     = Decoupled(UInt(CVAL.DLEN.W))
  })
  io.in.ready  := io.out.ready
  io.out.valid := io.in.valid && ~io.flush_pipeline
  //pass_throughs
  io.out.bits.mem_read_enable  := io.in.bits.mem_read_enable
  io.out.bits.mem_write_enable := io.in.bits.mem_write_enable
  io.out.bits.func3            := io.in.bits.func3
  io.out.bits.pc               := io.in.bits.pc //using!
  io.out.bits.ecall            := io.in.bits.ecall
  io.out.bits.pc_jump          := io.in.bits.pc_jump
  io.out.bits.reg_w_addr       := io.in.bits.rd
  io.out.bits.reg_w_enable     := io.in.bits.reg_write_enable
  io.out.bits.mret             := io.in.bits.mret
  io.out.bits.imm              := io.in.bits.imm
  io.out.bits.csrrw            := io.in.bits.csrrw
  io.out.bits.flush_icache:=io.in.bits.flush_icache
  io.out.bits.ebreak:=io.in.bits.ebreak

  //reg to write for this inst->pass to decoder to stall
  io.reg_addr := Mux(io.in.valid && io.in.bits.reg_write_enable, io.in.bits.rd, 0.U)

  //pc of this inst pass to hazard_unit
  io.pc.bits  := io.in.bits.pc
  io.pc.valid := io.in.valid

  val src1     = io.in.bits.src1
  val src2     = io.in.bits.src2
  val csr_data = io.in.bits.csr_data

  val alu_val1 = Mux(io.in.bits.alu_use_pc, io.in.bits.pc, src1)
  val alu_val2 = Mux(io.in.bits.alu_use_Imm_2, io.in.bits.imm, src2)

  //compare_unit
  val comp = Module(new Branch_comp())
  comp.io.src1  := src1
  comp.io.src2  := src2
  comp.io.func3 := io.in.bits.func3
  val go_branch = comp.io.result

  //alu_unit
  val alu = Module(new ALU())
  alu.io.in.src1        := alu_val1
  alu.io.in.src2        := alu_val2
  alu.io.in.alu_op_type := io.in.bits.alu_op_type

  //csrr_alu
  val or = csr_data | src1
  val csr_alu_res = MuxLookup(io.in.bits.csr_alu_type, or)(
    Seq(
      CSRALU_Type.or -> or,
      CSRALU_Type.passreg -> src1
    )
  )

  val result = Mux(io.in.bits.csrrw, csr_data, alu.io.result) //内存读取/csr操作/算数运算结果
  io.forwarding.bits  := result
  io.forwarding.valid := io.in.valid && ~io.in.bits.mem_read_enable

  //outputs
  // io.out.bits.alu_result  := alu.io.result //alu的运算结果
  io.out.bits.exu_result  := result
  io.out.bits.src2        := src2
  io.out.bits.csr_alu_res := csr_alu_res
  io.out.bits.csr_val     := csr_data
  io.out.bits.go_branch   := go_branch && io.in.bits.is_branch

  //Trace
  val trace_exu = Module(new TRACE_EXU)
  trace_exu.io.clock := clock
  trace_exu.io.valid := io.in.valid && io.out.ready
}

class Branch_comp extends Module {
  val io = IO(new Bundle {
    val src1   = Input(UInt(CVAL.DLEN.W))
    val src2   = Input(UInt(CVAL.DLEN.W))
    val func3  = Input(UInt(3.W))
    val result = Output(Bool())
  })
  io.result := MuxLookup(io.func3, false.B)(
    Seq(
      "b000".U -> (io.src1 === io.src2), //beq
      "b001".U -> (io.src1 =/= io.src2), //bne
      "b100".U -> (io.src1.asSInt < io.src2.asSInt), //blt
      "b101".U -> (io.src1.asSInt >= io.src2.asSInt), //bge
      "b110".U -> (io.src1 < io.src2), //bltu
      "b111".U -> (io.src1 >= io.src2) //bgeu
    )
  )
}

//:exu完成计算-valid信号--not used now
class TRACE_EXU extends BlackBox with HasBlackBoxInline {
  val io = IO(new Bundle {
    val valid = Input(Bool())
    val clock = Input(Clock())
  })
  setInline(
    "trace_exu.v",
    """import "DPI-C" function void trace_exu();
      |module TRACE_EXU(
      |  input valid,
      |  input clock
      |);
      |always @(negedge clock) begin
      |   if (valid) begin
      |      trace_exu();
      |  end
      | end
      |endmodule
    """.stripMargin
  )
}
