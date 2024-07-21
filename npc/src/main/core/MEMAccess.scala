package core

import chisel3._
import chisel3.util._
import core.IO._
import Constants_Val._

class MEMAccess extends Module {
  val io = IO(new Bundle {
    val in  = Flipped(Decoupled(new EXU_O))
    val out = Decoupled(new MEMA_O)
  })
  //pass_throughs
  io.out.bits.pc              := io.in.bits.pc
  io.out.bits.ecall           := io.in.bits.ecall
  io.out.bits.csr_alu_res     := io.in.bits.csr_alu_res
  io.out.bits.mem_read_enable := io.in.bits.mem_read_enable //using
  io.out.bits.csrrw           := io.in.bits.csrrw
  io.out.bits.csr_val         := io.in.bits.csr_val
  io.out.bits.alu_result      := io.in.bits.alu_result //using!
  io.out.bits.pc_jump         := io.in.bits.pc_jump
  io.out.bits.is_branch       := io.in.bits.is_branch
  io.out.bits.go_branch       := io.in.bits.go_branch
  io.out.bits.reg_w_addr      := io.in.bits.reg_w_addr
  io.out.bits.reg_w_enable    := io.in.bits.reg_w_enable
  io.out.bits.mret            := io.in.bits.mret
  io.out.bits.imm             := io.in.bits.imm

  val axi=Module(new AXI_Master)
  axi.io.in.valid:=io.in.valid
  io.in.ready:=axi.io.in.ready//暂时全true
  axi.io.in.bits.mem_read_addr:=io.in.bits.alu_result
  axi.io.in.bits.mem_write_addr:=io.in.bits.alu_result 
  axi.io.in.bits.mem_read_enable:=io.in.bits.mem_read_enable
  axi.io.in.bits.mem_write_enable:=io.in.bits.mem_write_enable
  axi.io.in.bits.mem_write_data:=io.in.bits.src2
  axi.io.in.bits.mem_read_type:=io.in.bits.mem_read_type
  axi.io.in.bits.mem_write_type:=io.in.bits.mem_write_type

  io.out.bits.mem_read_result:=axi.io.out.bits.mem_read_result
  io.out.valid:=axi.io.out.valid
  axi.io.out.ready:=io.out.ready


}
