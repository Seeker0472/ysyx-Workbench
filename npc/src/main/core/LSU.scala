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
  val s_idle :: s_r_busy :: s_w_busy :: s_valid :: s_r_wait_ready:: s_w_wait_result ::s_w_wait_ready :: Nil = Enum(7)
  val state                                                              = RegInit(s_idle)
  state := MuxLookup(state, s_idle)(
    List(
      s_idle -> Mux(
        (io.in.bits.mem_write_enable || io.in.bits.mem_read_enable) && io.in.valid,
        // Mux(io.in.bits.mem_read_enable, s_r_busy, s_w_busy),
        Mux(io.in.bits.mem_read_enable, Mux(io.axi.RA.ready, s_r_busy, s_r_wait_ready), Mux(io.axi.WA.ready,s_w_busy,s_w_wait_ready)),
        Mux(io.in.valid, s_valid, s_idle)
      ),
      s_r_wait_ready -> Mux(io.axi.RA.ready, s_r_busy, s_r_wait_ready),
      s_w_wait_ready -> Mux(io.axi.WA.valid,s_w_busy,s_w_wait_ready),
      s_r_busy -> Mux(io.axi.RD.valid, s_valid, s_r_busy),
      s_w_wait_result -> Mux(io.axi.WR.valid,s_valid,s_w_wait_result),
      s_w_busy -> Mux(io.axi.WD.ready, s_valid, s_w_busy), //不等返回值
      // s_w_busy -> Mux(io.axi.WD.ready, s_w_wait_result, s_w_busy), //等待返回值
      s_valid -> Mux(io.out.ready, s_idle, s_valid)
    )
  )
  io.in.ready  := true.B
  io.out.valid := state === s_valid
  val mem_read_size = MuxLookup(io.in.bits.mem_read_type, 0.U(3.W))(
    Seq(
      Load_Type.lb -> "b000".U(3.W),
      Load_Type.lh -> "b001".U(3.W),
      Load_Type.lw -> "b010".U(3.W),
      Load_Type.lbu -> "b000".U(3.W),
      Load_Type.lhu -> "b001".U(3.W)
    )
  )
  io.axi.RA.bits.size := mem_read_size

  io.axi.RA.valid     := io.in.bits.mem_read_enable && io.in.valid && (state === s_idle || state === s_r_wait_ready) //避免多次访存
  io.axi.RA.bits.addr := io.in.bits.alu_result
  io.axi.RD.ready     := true.B

  val mrres = io.axi.RD.bits.data

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

  val mem_write_mask = MuxLookup(io.in.bits.mem_write_type, 0.U(4.W))(
    Seq(
      Store_Type.sb -> "b0001".U(4.W),
      Store_Type.sh -> "b0011".U(4.W),
      Store_Type.sw -> "b1111".U(4.W)
    )
  )
  val mem_write_size = MuxLookup(io.in.bits.mem_write_type, 0.U(3.W))(
    Seq(
      Store_Type.sb -> "b000".U(3.W),
      Store_Type.sh -> "b001".U(3.W),
      Store_Type.sw -> "b010".U(3.W)
    )
  )
  val wd_move = io.in.bits.src2 << ((io.in.bits.alu_result(1, 0)) << 3)

  val mask_move = mem_write_mask << ((io.in.bits.alu_result)(1, 0))  
  
  io.axi.WA.valid      := io.in.bits.mem_write_enable && io.in.valid && (state === s_idle || state === s_w_wait_ready)//避免多次访存
  io.axi.WA.bits.addr  := io.in.bits.alu_result
  io.axi.WD.bits.data  := wd_move //移动
  io.axi.WD.bits.wstrb := mask_move //移动
  io.axi.WA.bits.size  := mem_write_size //写入数据的大小
  io.axi.WD.valid := state === s_w_busy
  io.axi.WR.ready := true.B
  //暂时忽略错误处理

  val read_res = Reg(UInt(CVAL.DLEN.W)) //读取的值
  io.out.bits.mem_read_result := read_res
  read_res                    := mem_read_result


  val check_mem=Module(new DPI_C_CHECK)
  check_mem.io.addr:=io.in.bits.alu_result
  check_mem.io.ren:=io.in.bits.mem_read_enable && io.in.valid  && state === s_idle
  check_mem.io.wdata:=wd_move
  check_mem.io.wmask:=mask_move
  check_mem.io.wen:=io.in.bits.mem_write_enable && io.in.valid && state === s_idle 
  check_mem.io.len:=mem_read_size
  check_mem.io.clock:=clock

  val trace_lsu = Module(new TRACE_LSU)
  trace_lsu.io.addr := io.in.bits.alu_result
  trace_lsu.io.w_start := io.in.bits.mem_write_enable && io.in.valid
  trace_lsu.io.w_end  := io.axi.WR.valid
  trace_lsu.io.r_start := io.in.bits.mem_read_enable && io.in.valid
  trace_lsu.io.r_end := io.axi.RD.valid
  trace_lsu.io.clock := clock
}

class DPI_C_CHECK extends BlackBox with HasBlackBoxInline {
  val io = IO(new Bundle {
    val addr  = Input(UInt(CVAL.DLEN.W))
    val wdata  = Input(UInt(CVAL.DLEN.W))
    val wmask  = Input(UInt(CVAL.DLEN.W))
    val len  = Input(UInt(CVAL.DLEN.W))
    val wen = Input(Bool())
    val ren = Input(Bool())
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
    val addr  = Input(UInt(CVAL.DLEN.W))
    val w_start = Input(Bool())
    val r_start = Input(Bool())
    val w_end = Input(Bool())
    val r_end = Input(Bool())
    val clock = Input(Clock())
  })
    setInline(
    "trace_lsu.v",
    """import "DPI-C" function void trace_lsu(int unsigned addr,bit RW,bit start_end);
      |module DPI_C_CHECK(
      |  input w_start,
      |  input r_start,      
      |  input w_end,
      |  input r_end,
      |  input [31:0] addr,
      |  input clock
      |);
      | reg w,r;
      |initial
      | w=r=1'b0;
      |always @(negedge clock) begin
      |   if (w_start) begin
      |      trace_lsu(addr,false,true);
      |     w=1'b1;
      |  end
      |   if (r_start) begin
      |      trace_lsu(addr,true,true);
      |     r=1'b1;
      |  end
      |   if (w_end && w==1'b1) begin
      |      trace_lsu(addr,false,false);
      |     w=1'b0;
      |  end
      |   if (r_end && r=1'b1) begin
      |      trace_lsu(addr,true,false);
      |     r=1'b0;
      |  end
      | end
      |endmodule
    """.stripMargin
  )
}
