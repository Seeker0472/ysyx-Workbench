package core

import chisel3._
import chisel3.util._
import core.IO._
import Constants_Val._

class WBU extends Module {
  val io = IO(new Bundle {
    val in         = Flipped(Decoupled(new MEMA_O))
    val csr_mstvec = Input(UInt(CVAL.DLEN.W))
    val Rwrite     = (new RegWriteIO)
    val CSR_write  = (new CSRWriteIO)
    val out        = Decoupled(new WBU_O)
  })
  io.in.ready:=true.B
  val in_regbits = RegNext(io.in.bits)
  val in_regvalid = RegNext(io.in.valid)

  io.out.valid:=in_regvalid

  io.CSR_write.write_enable := in_regbits.csrrw && in_regvalid
//TODO:其实可以临时抽取？
  io.CSR_write.addr := in_regbits.imm

  io.CSR_write.data := Mux(in_regbits.ecall, in_regbits.pc, in_regbits.csr_alu_res) //ecall的时候保存pc寄存器/正常csr指令保存csr_alu的数据

//wb
  //如果是store，Reg_Write_Enable应该是False
  // val result   = alu.io.result
  // val result   = Mux(in_regbits.mem_read_enable, mem_read_result, alu.io.result)
  val result =
    Mux(
      in_regbits.mem_read_enable,
      in_regbits.mem_read_result,
      Mux(in_regbits.csrrw, in_regbits.csr_val, in_regbits.alu_result)
    ) //内存读取/csr操作/算数运算结果
  val pc_plus4 = in_regbits.pc + 4.U

  val next_pc = Mux(
    in_regbits.pc_jump || (in_regbits.is_branch && in_regbits.go_branch),
    result,
    Mux(in_regbits.ecall, io.csr_mstvec, pc_plus4)
  ) //跳转指令/ecall/正常pc+4
  io.Rwrite.data         := Mux(in_regbits.pc_jump, pc_plus4, result) //跳转指令保存寄存器
  io.Rwrite.addr         := in_regbits.reg_w_addr
  io.Rwrite.write_enable := in_regbits.reg_w_enable && in_regvalid
  // io.out.n_pc    := next_pc
  io.out.bits.n_pc := Mux(in_regbits.mret, in_regbits.csr_val, next_pc) //mret恢复pc
  // TODO：这个地方感觉会延迟很高？

}
