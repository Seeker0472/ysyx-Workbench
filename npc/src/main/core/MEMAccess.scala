package core

import chisel3._
import chisel3.util._
import core.IO._

class MEMAccess extends Module {
  val io = IO(new Bundle {
    val in  = Flipped(new EXU_O)
    val out = (new MEMA_O)
  })
  //pass_throughs
  io.out.pc              := io.in.pc
  io.out.ecall           := io.in.ecall
  io.out.csr_alu_res     := io.in.csr_alu_res
  io.out.mem_read_enable := io.in.mem_read_enable //using
  io.out.csrrw           := io.in.csrrw
  io.out.csr_val         := io.in.csr_val
  io.out.alu_result      := io.in.alu_result //using!
  io.out.pc_jump         := io.in.pc_jump
  io.out.is_branch       := io.in.is_branch
  io.out.go_branch       := io.in.go_branch
  io.out.reg_w_addr      := io.in.reg_w_addr
  io.out.reg_w_enable    := io.in.reg_w_enable
  io.out.mret            := io.in.mret
  io.out.imm             := io.in.imm

  //TODO:不应该在这里实例化！！！
  val mem = Module(new MEM())

  mem.io.clock :=clock
  //mem R/W
  mem.io.read_enable  := io.in.mem_read_enable
  mem.io.write_enable := io.in.mem_write_enable
  //TODO: 这里需要设计两个信号吗-感觉要的，每次读取内存都有开销
  mem.io.read_addr  := io.in.alu_result
  mem.io.write_addr := io.in.alu_result
  val mrres = mem.io.read_data
  val mrrm  = mrres >> ((io.in.alu_result & (0x3.U)) << 3) // 读取内存,不对齐访问!!
  //vv注意符号拓展！！！
  val mem_read_result_sint = MuxLookup(io.in.mem_read_type, 0.S)(
    Seq(
      Load_Type.lb -> mrrm(7, 0).asSInt,
      Load_Type.lh -> mrrm(15, 0).asSInt,
      Load_Type.lw -> mrrm(31, 0).asSInt,
      Load_Type.lbu -> mrrm(7, 0).zext,
      Load_Type.lhu -> mrrm(15, 0).zext
    )
  )
  val mem_read_result = mem_read_result_sint.asUInt

  val mem_write_mask = MuxLookup(io.in.mem_write_type, 0.U)(
    Seq(
      Store_Type.sb -> "b00000011".U(8.W),
      Store_Type.sh -> "b00001111".U(8.W),
      Store_Type.sw -> "b11111111".U(8.W)
    )
  )
  mem.io.write_mask := mem_write_mask
  mem.io.write_data := io.in.src2

  io.out.mem_read_result:=mem_read_result

}
