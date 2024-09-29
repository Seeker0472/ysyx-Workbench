package core

import chisel3._
import chisel3.util._
import core.IO._
import Constants_Val._

class LSU extends Module {
  val io = IO(new Bundle {
    val in  = Flipped(Decoupled(new EXU_O))
    val out = Decoupled(new MEMA_O)
    val axi = Flipped(new AXIIO())
  })
  //sigs and status
  val s_idle :: s_r_busy :: s_w_busy :: s_valid :: Nil = Enum(4)
  val state                                            = RegInit(s_idle)
  val sig_awvalid                                      = RegInit(false.B)
  val sig_arvalid                                      = RegInit(false.B)
  val sig_wvalid                                       = RegInit(false.B)
  //
  io.in.ready := true.B
  val in_regbits  = Reg(new EXU_O)
  val in_regvalid = Reg(Bool())
  // 更新逻辑
  when(state===s_idle) {
    in_regbits := io.in.bits
    in_regvalid := io.in.valid
  }

  io.out.valid := state === s_valid
  //pass_throughs
  io.out.bits.pc              := in_regbits.pc
  io.out.bits.ecall           := in_regbits.ecall
  io.out.bits.csr_alu_res     := in_regbits.csr_alu_res
  io.out.bits.mem_read_enable := in_regbits.mem_read_enable //using
  io.out.bits.csrrw           := in_regbits.csrrw
  io.out.bits.csr_val         := in_regbits.csr_val
  io.out.bits.alu_result      := in_regbits.alu_result //using!
  io.out.bits.pc_jump         := in_regbits.pc_jump
  io.out.bits.is_branch       := in_regbits.is_branch
  io.out.bits.go_branch       := in_regbits.go_branch
  io.out.bits.reg_w_addr      := in_regbits.reg_w_addr
  io.out.bits.reg_w_enable    := in_regbits.reg_w_enable
  io.out.bits.mret            := in_regbits.mret
  io.out.bits.imm             := in_regbits.imm

  state := MuxLookup(state, s_idle)(
    List(
      s_idle -> Mux(
        (in_regbits.mem_write_enable || in_regbits.mem_read_enable) && in_regvalid,
        Mux(in_regbits.mem_write_enable, s_w_busy, s_r_busy),
        Mux(in_regvalid,s_valid,s_idle)
      ),
      s_r_busy -> Mux(io.axi.RD.valid, s_valid, s_r_busy),
      s_w_busy -> Mux(io.axi.WR.valid, s_valid, s_w_busy),
      s_valid -> Mux(io.out.ready, s_idle, s_valid)
    )
  )
  sig_awvalid := MuxLookup(sig_awvalid, false.B) {
    Seq(
      false.B -> Mux(state === s_idle && in_regbits.mem_write_enable && in_regvalid, true.B, false.B),
      true.B -> Mux(io.axi.WA.ready, false.B, true.B)
    )
  }
  sig_arvalid := MuxLookup(sig_arvalid, false.B) {
    Seq(
      false.B -> Mux(state === s_idle && in_regbits.mem_read_enable && in_regvalid, true.B, false.B),
      true.B -> Mux(io.axi.RA.ready, false.B, true.B)
    )
  }
  sig_wvalid := MuxLookup(sig_wvalid, false.B) {
    Seq(
      false.B -> Mux(state === s_idle && in_regbits.mem_write_enable && in_regvalid, true.B, false.B),
      true.B -> Mux(io.axi.WD.ready, false.B, true.B)
    )
  }

  val mem_read_size = MuxLookup(in_regbits.mem_read_type, 0.U(3.W))(
    Seq(
      Load_Type.lb -> "b000".U(3.W),
      Load_Type.lh -> "b001".U(3.W),
      Load_Type.lw -> "b010".U(3.W),
      Load_Type.lbu -> "b000".U(3.W),
      Load_Type.lhu -> "b001".U(3.W)
    )
  )
  io.axi.RA.bits.size := mem_read_size
  io.axi.RA.bits.id   := 0.U //TODO!!!!!
  io.axi.RA.bits.len  := 0.U

  io.axi.RA.valid     := sig_arvalid
  io.axi.RA.bits.addr := in_regbits.alu_result
  io.axi.RD.ready     := true.B

  val mrres = io.axi.RD.bits.data

  val mrrm = mrres >> ((in_regbits.alu_result & (0x3.U)) << 3) // 读取内存,不对齐访问!!
  //vv注意符号拓展！！！
  val mem_read_result_sint = MuxLookup(in_regbits.mem_read_type, 0.S)(
    Seq(
      Load_Type.lb -> mrrm(7, 0).asSInt,
      Load_Type.lh -> mrrm(15, 0).asSInt,
      Load_Type.lw -> mrrm(31, 0).asSInt,
      Load_Type.lbu -> mrrm(7, 0).zext,
      Load_Type.lhu -> mrrm(15, 0).zext
    )
  )

  val mem_read_result = mem_read_result_sint.asUInt

  val mem_write_mask = MuxLookup(in_regbits.mem_write_type, 0.U(4.W))(
    Seq(
      Store_Type.sb -> "b0001".U(4.W),
      Store_Type.sh -> "b0011".U(4.W),
      Store_Type.sw -> "b1111".U(4.W)
    )
  )
  val mem_write_size = MuxLookup(in_regbits.mem_write_type, 0.U(3.W))(
    Seq(
      Store_Type.sb -> "b000".U(3.W),
      Store_Type.sh -> "b001".U(3.W),
      Store_Type.sw -> "b010".U(3.W)
    )
  )
  val wd_move = in_regbits.src2 << ((in_regbits.alu_result(1, 0)) << 3)

  val mask_move = mem_write_mask << ((in_regbits.alu_result)(1, 0))

  io.axi.WA.valid      := sig_awvalid
  io.axi.WA.bits.addr  := in_regbits.alu_result
  io.axi.WD.bits.data  := wd_move //移动
  io.axi.WD.bits.wstrb := mask_move //移动
  io.axi.WA.bits.size  := mem_write_size //写入数据的大小
  io.axi.WD.valid      := sig_wvalid
  io.axi.WR.ready      := true.B
  //暂时忽略错误处理

  val read_res = Reg(UInt(CVAL.DLEN.W)) //读取的值
  io.out.bits.mem_read_result := read_res
  read_res                    := mem_read_result

  val check_mem = Module(new DPI_C_CHECK)
  check_mem.io.addr  := in_regbits.alu_result
  check_mem.io.ren   := in_regbits.mem_read_enable && in_regvalid && state === s_idle
  check_mem.io.wdata := wd_move
  check_mem.io.wmask := mask_move
  check_mem.io.wen   := in_regbits.mem_write_enable && in_regvalid && state === s_idle
  check_mem.io.len   := mem_read_size
  check_mem.io.clock := clock

  val trace_lsu = Module(new TRACE_LSU)
  trace_lsu.io.addr    := in_regbits.alu_result
  trace_lsu.io.w_start := in_regbits.mem_write_enable && in_regvalid && state === s_idle
  trace_lsu.io.w_end   := io.axi.WR.valid
  trace_lsu.io.r_start := in_regbits.mem_read_enable && in_regvalid && state === s_idle
  trace_lsu.io.r_end   := io.axi.RD.valid
  trace_lsu.io.clock   := clock
}

class DPI_C_CHECK extends BlackBox with HasBlackBoxInline {
  val io = IO(new Bundle {
    val addr  = Input(UInt(CVAL.DLEN.W))
    val wdata = Input(UInt(CVAL.DLEN.W))
    val wmask = Input(UInt(CVAL.DLEN.W))
    val len   = Input(UInt(CVAL.DLEN.W))
    val wen   = Input(Bool())
    val ren   = Input(Bool())
    val clock = Input(Clock())
  })
  setInline(
    "check_addr.v",
    """import "DPI-C" function void check_addr(int unsigned addr,bit access_type, int unsigned wmask,int unsigned wdata,int unsigned len);
      |module DPI_C_CHECK(
      |  input wen,
      |  input ren,
      |  input [31:0] addr,
      |  input [31:0] wmask,
      |  input [31:0] wdata,
      |  input [31:0] len,
      |  input clock
      |); 
      |always @(negedge clock) begin
      |   if (wen||ren) begin
      |      check_addr(addr,ren,wmask,wdata,len);
      |  end
      | end
      |endmodule
    """.stripMargin
  )
}
//判断input改变
//TODO:LSU 取到数据/写入数据--使用valid
//TODO:LSU 延迟
/*
  addr,w/wfin,r/rfin
  RW--R-True/W-False
  start_end--start-True/end-False
 */
class TRACE_LSU extends BlackBox with HasBlackBoxInline {
  val io = IO(new Bundle {
    val addr    = Input(UInt(CVAL.DLEN.W))
    val w_start = Input(Bool())
    val r_start = Input(Bool())
    val w_end   = Input(Bool())
    val r_end   = Input(Bool())
    val clock   = Input(Clock())
  })
  setInline(
    "trace_lsu.v",
    """import "DPI-C" function void trace_lsu(int unsigned addr,bit RW,bit start_end);
      |module TRACE_LSU(
      |  input w_start,
      |  input r_start,      
      |  input w_end,
      |  input r_end,
      |  input [31:0] addr,
      |  input clock
      |);
      | reg w,r;
      |initial begin
      | w=1'b0;
      | r=1'b0;
      |end
      |always @(negedge clock) begin
      |   if (w_start&&w==1'b0) begin
      |      trace_lsu(addr,1'b0,1'b1);
      |     w=1'b1;
      |  end
      |   if (r_start&&r==1'b0) begin
      |      trace_lsu(addr,1'b1,1'b1);
      |     r=1'b1;
      |  end
      |   if (w_end && w==1'b1) begin
      |      trace_lsu(addr,1'b0,1'b0);
      |     w=1'b0;
      |  end
      |   if (r_end && r==1'b1) begin
      |      trace_lsu(addr,1'b1,1'b0);
      |     r=1'b0;
      |  end
      | end
      |endmodule
    """.stripMargin
  )
}
