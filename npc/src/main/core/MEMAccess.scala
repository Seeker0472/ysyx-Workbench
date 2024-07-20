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
  // io.in.ready:=true.B//TODO
  // // io.out.valid:=true.B
  // io.out.valid:=io.in.valid


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


  val s_idle :: s_busy ::Nil = Enum(2)
  val state= RegInit(s_idle)
  state:=MuxLookup(state,s_idle)(List(
    s_busy-> Mux(io.out.ready,s_idle,s_busy),
    s_idle-> Mux((io.in.bits.mem_write_enable||io.in.bits.mem_read_enable ) && io.in.valid,s_busy,s_idle)
  ))
  io.in.ready:=state===s_idle
  io.out.valid:=io.in.valid&&(!((io.in.bits.mem_write_enable||io.in.bits.mem_read_enable ) && io.in.valid && state===s_idle ))

  //TODO:不应该在这里实例化！！！
  val mem = Module(new MEM())
  mem.io.clock :=clock
  //mem R/W
  mem.io.read_enable  := io.in.bits.mem_read_enable && io.in.valid

  val sram_we_sim = Reg(Bool())//模拟延迟
  sram_we_sim:=io.in.bits.mem_write_enable && io.in.valid
  mem.io.write_enable:=sram_we_sim
  // mem.io.write_enable := io.in.bits.mem_write_enable && io.in.valid
  

  //TODO: 这里需要设计两个信号吗-感觉要的，每次读取内存都有开销
  mem.io.read_addr  := io.in.bits.alu_result
  mem.io.write_addr := io.in.bits.alu_result
  val mrres = mem.io.read_data
  val mrrm  = mrres >> ((io.in.bits.alu_result & (0x3.U)) << 3) // 读取内存,不对齐访问!!
  //vv注意符号拓展！！！
  val mem_read_result_sint = MuxLookup(io.in.bits.mem_read_type, 0.S)(
    Seq(
      Load_Type.lb -> mrrm(7, 0).asSInt,
      Load_Type.lh -> mrrm(15, 0).asSInt,
      Load_Type.lw -> mrrm(31, 0).asSInt,
      Load_Type.lbu -> mrrm(7, 0).zext,
      Load_Type.lhu -> mrrm(15, 0).zext
    )
  )
  val mem_read_result = mem_read_result_sint.asUInt

  val mem_write_mask = MuxLookup(io.in.bits.mem_write_type, 0.U)(
    Seq(
      Store_Type.sb -> "b00000011".U(8.W),
      Store_Type.sh -> "b00001111".U(8.W),
      Store_Type.sw -> "b11111111".U(8.W)
    )
  )
  mem.io.write_mask := mem_write_mask
  mem.io.write_data := io.in.bits.src2

  // io.out.bits.mem_read_result:=mem_read_result
  val sram_sim = Reg(UInt(CVAL.DLEN.W))//模拟延迟
  io.out.bits.mem_read_result:=sram_sim
  sram_sim:=mem_read_result


}
