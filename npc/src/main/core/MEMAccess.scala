package core

import chisel3._
import chisel3.util._
import core.IO._
import Constants_Val._

class MEMAccess extends Module {
  val io = IO(new Bundle {
    val in  = Flipped(Decoupled(new EXU_O))
    val out = Decoupled(new MEMA_O)
    val axi = Flipped(new AXIIO())
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
  
  //sigs and status
  val s_idle :: s_r_busy :: s_w_busy :: s_valid :: Nil = Enum(4)
  val state                                            = RegInit(s_idle)
  state := MuxLookup(state, s_idle)(
    List(
      s_idle -> Mux(
        (io.in.bits.mem_write_enable || io.in.bits.mem_read_enable) && io.in.valid,
        Mux(io.in.bits.mem_read_enable, s_r_busy, s_w_busy),
        Mux(io.in.valid, s_valid, s_idle)
      ),
      s_r_busy -> Mux(io.axi.RD.valid, s_valid, s_r_busy), //depends on the mem delay
      s_w_busy -> Mux(io.axi.WR.valid, s_valid, s_w_busy),
      s_valid -> Mux(io.out.ready, s_idle, s_valid)
    )
  )
  io.in.ready  := true.B
  io.out.valid := state === s_valid

  io.axi.RA.valid     := io.in.bits.mem_read_enable && io.in.valid && state =/= s_valid //避免多次访存
  io.axi.RA.bits.addr := io.in.bits.alu_result
  io.axi.RD.ready     := true.B

  val mrres = io.axi.RD.bits.data

  // mem.io.write_enable := io.in.bits.mem_write_enable && io.in.valid&&state===s_busy//由于读写延迟
  // mem.io.write_addr := io.in.bits.alu_result
  val mrrm = mrres >> ((io.in.bits.alu_result & (0x3.U)) << 3) // 读取内存,不对齐访问!!
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
  
//TODO:::::::::::::::::::::应该是没对齐
  val mem_write_mask = MuxLookup(io.in.bits.mem_write_type, 0.U(4.W))(
    Seq(
      Store_Type.sb -> "b0001".U(4.W),
      Store_Type.sh -> "b0011".U(4.W),
      Store_Type.sw -> "b1111".U(4.W)
    )
  )
val wd_move = io.in.bits.src2 << ((io.in.bits.alu_result(1,0)) << 3)


  val mask_move = mem_write_mask <<((io.in.bits.alu_result)(1,0)) 
  

  io.axi.WA.valid      := io.in.bits.mem_write_enable && io.in.valid && state =/= s_valid //避免多次访存
  io.axi.WA.bits.addr  := io.in.bits.alu_result 
  io.axi.WD.bits.data  := wd_move//移动
  io.axi.WD.bits.wstrb := mask_move//移动
  // io.axi.WD.valid      := true.B
  io.axi.WD.valid      := state===s_w_busy
  io.axi.WR.ready      := true.B
  //暂时忽略错误处理

  // io.out.bits.mem_read_result:=mem_read_result
  val read_res = Reg(UInt(CVAL.DLEN.W)) //读取的值
  io.out.bits.mem_read_result := read_res
  read_res                    := mem_read_result


}
