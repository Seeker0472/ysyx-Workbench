package core

import chisel3._
import chisel3.util._
import core.IO._
import Constants_Val._
import javax.swing.InputMap

class WBU extends Module {
  val io = IO(new Bundle {
    val in           = Flipped(Decoupled(new MEMA_O))
    val csr_mstvec   = Input(UInt(CVAL.DLEN.W))
    val Rwrite       = (new RegWriteIO)
    val CSR_write    = (new CSRWriteIO)
    val out          = Decoupled(new WBU_O)
    val wbu_pc       = Decoupled(UInt(CVAL.DLEN.W))
    val ebreak       = Output(Bool())
    val flush_icache = Output(Bool())
  })
  io.in.ready     := io.out.ready
  io.out.valid    := io.in.valid
  io.wbu_pc.valid := io.in.valid

  io.ebreak       := io.in.bits.ebreak && io.in.valid
  io.flush_icache := io.in.bits.flush_icache && io.in.valid

  io.CSR_write.write_enable := io.in.bits.csrrw && io.in.valid

  io.CSR_write.addr := io.in.bits.imm

  io.CSR_write.data := Mux(
    io.in.bits.ecall,
    io.in.bits.pc,
    io.in.bits.csr_alu_res
  ) //ecall的时候保存pc寄存器/正常csr指令保存csr_alu的数据

//wb
  // //如果是store，Reg_Write_Enable应该是False
  // val result =
  //   Mux(
  //     io.in.bits.mem_read_enable,
  //     io.in.bits.mem_read_result,
  //     Mux(io.in.bits.csrrw, io.in.bits.csr_val, io.in.bits.alu_result)
  //   ) //内存读取/csr操作/算数运算结果

  //如果是store，Reg_Write_Enable应该是False
  val result =
    Mux(
      io.in.bits.mem_read_enable,
      io.in.bits.mem_read_result,
      io.in.bits.exu_result
    ) //内存读取/csr操作/算数运算结果
  val pc_plus4 = io.in.bits.pc + 4.U

  val next_pc = Mux(
    io.in.bits.pc_jump || io.in.bits.go_branch,
    result,
    Mux(io.in.bits.ecall, io.csr_mstvec, pc_plus4)
  ) //跳转指令/ecall/正常pc+4
  io.Rwrite.data         := Mux(io.in.bits.pc_jump, pc_plus4, result) //跳转指令保存寄存器
  io.Rwrite.addr         := io.in.bits.reg_w_addr
  io.Rwrite.write_enable := io.in.bits.reg_w_enable && io.in.valid

  val n_pc = Mux(io.in.bits.mret, io.in.bits.csr_val, next_pc) //mret恢复pc

  io.out.bits.n_pc := n_pc
  io.wbu_pc.bits   := n_pc
  io.out.bits.pc   := io.in.bits.pc

  //trace
  val wbu_trace = Module(new TRACE_WBU)
  wbu_trace.io.clock := clock
  wbu_trace.io.valid := io.in.valid && io.out.ready
  wbu_trace.io.pc    := io.in.bits.pc
  wbu_trace.io.n_pc  := n_pc

}

class TRACE_WBU extends BlackBox with HasBlackBoxInline {
  val io = IO(new Bundle {
    val clock = Input(Clock())
    val valid = Input(Bool())
    val pc    = Input(UInt(CVAL.DLEN.W))
    val n_pc  = Input(UInt(CVAL.DLEN.W))
  })
  setInline(
    "trace_wbu.v",
    """import "DPI-C" function void trace_wbu(int unsigned pc,int unsigned n_pc);
      |module TRACE_WBU(
      |  input valid,
      |  input clock,
      |  input [31:0] pc,
      |  input [31:0] n_pc
      |); 
      |always @(negedge clock) begin
      |   if (valid) begin
      |      trace_wbu(pc,n_pc);
      |  end
      | end
      |endmodule
    """.stripMargin
  )
}
