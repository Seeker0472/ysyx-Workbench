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
    // four-stage pipeline's lsu don't need flush!
    // val flush_pipeline = Input(Bool())
    val reg_addr = Output(UInt(CVAL.REG_ADDR_LEN.W))
    // val forwarding = Decoupled(UInt(CVAL.DLEN.W))
  })
  //states
  val s_idle :: s_r_busy :: s_w_busy :: s_wait_valid :: s_valid :: Nil = Enum(5)
  //state_machine and axi_signals works as an implict state_machine
  val state       = RegInit(s_idle)
  val sig_awvalid = RegInit(false.B)
  val sig_arvalid = RegInit(false.B)
  val sig_wvalid  = RegInit(false.B)
  //mem write or mem read
  val mem_rw = io.in.bits.mem_read_enable || io.in.bits.mem_write_enable

  //the target reg to write-> send to decoder to stall the pipeline
  io.reg_addr := Mux(io.in.bits.reg_w_enable && state =/= s_idle, io.in.bits.reg_w_addr, 0.U)
  //ready and valid
  io.in.ready  := state === s_idle
  io.out.valid := (state === s_valid || (state === s_wait_valid && ~mem_rw))

  //pass_throughs
  io.out.bits.pc              := io.in.bits.pc
  io.out.bits.ecall           := io.in.bits.ecall
  io.out.bits.csr_alu_res     := io.in.bits.csr_alu_res
  io.out.bits.mem_read_enable := io.in.bits.mem_read_enable //using
  io.out.bits.csrrw           := io.in.bits.csrrw
  io.out.bits.csr_val         := io.in.bits.csr_val
  // io.out.bits.alu_result      := io.in.bits.alu_result //using!
  io.out.bits.pc_jump      := io.in.bits.pc_jump
  io.out.bits.go_branch    := io.in.bits.go_branch
  io.out.bits.reg_w_addr   := io.in.bits.reg_w_addr
  io.out.bits.reg_w_enable := io.in.bits.reg_w_enable
  io.out.bits.mret         := io.in.bits.mret
  io.out.bits.imm          := io.in.bits.imm

  //result of EXU
  // val result = Mux(io.in.bits.csrrw, io.in.bits.csr_val, io.in.bits.alu_result) //内存读取/csr操作/算数运算结果
  io.out.bits.exu_result := io.in.bits.exu_result
  // io.forwarding.bits := result
  // io.forwarding.valid := io.in.valid && ~io.out.bits.mem_read_enable && io.out.bits.reg_w_enable

  //state
  state := MuxLookup(state, s_idle)(
    List(
      s_idle -> Mux(io.in.valid, s_wait_valid, s_idle),
      s_r_busy -> Mux(io.axi.RD.valid, s_valid, s_r_busy),
      s_w_busy -> Mux(io.axi.WR.valid, s_valid, s_w_busy), //TODO:Maybe don't need to wait error result?
      s_wait_valid -> Mux(
        mem_rw,
        Mux(io.in.bits.mem_read_enable, s_r_busy, s_w_busy),
        Mux(io.out.ready, s_idle, s_valid)
      ),
      s_valid -> Mux(io.out.ready, s_idle, s_valid)
    )
  )

  //axi_signals
  sig_awvalid := MuxLookup(sig_awvalid, false.B) {
    Seq(
      false.B -> Mux(state === s_wait_valid && io.in.bits.mem_write_enable, true.B, false.B),
      true.B -> Mux(io.axi.WA.ready, false.B, true.B)
    )
  }
  sig_arvalid := MuxLookup(sig_arvalid, false.B) {
    Seq(
      false.B -> Mux(state === s_wait_valid && io.in.bits.mem_read_enable, true.B, false.B),
      true.B -> Mux(io.axi.RA.ready, false.B, true.B)
    )
  }
  sig_wvalid := MuxLookup(sig_wvalid, false.B) {
    Seq(
      false.B -> Mux(state === s_wait_valid && io.in.bits.mem_write_enable, true.B, false.B),
      true.B -> Mux(io.axi.WD.ready, false.B, true.B)
    )
  }

  //axi signals read
  val mem_read_size = Cat(0.U(1.W), io.in.bits.func3(1, 0))
  io.axi.RA.bits.size := mem_read_size
  io.axi.RA.bits.id   := 0.U //TODO!!!!!
  io.axi.RA.bits.len  := 0.U
  io.axi.RA.valid     := sig_arvalid
  io.axi.RA.bits.addr := io.in.bits.alu_result
  io.axi.RD.ready     := true.B

  val mem_read = (io.axi.RD.bits.data) >> ((io.in.bits.alu_result & (0x3.U)) << 3) // 读取内存,不对齐访问!!
  //vv sign extension!
  val mem_read_result_sint = MuxLookup(io.in.bits.func3, 0.S)(
    Seq(
      "b000".U -> mem_read(7, 0).asSInt, //lb
      "b001".U -> mem_read(15, 0).asSInt, //lh
      "b010".U -> mem_read(31, 0).asSInt, //lw
      "b100".U -> mem_read(7, 0).zext, //lbu
      "b101".U -> mem_read(15, 0).zext //lhu
    )
  )
  val mem_read_result = mem_read_result_sint.asUInt

  //mask and size
  val mem_write_mask = MuxLookup(io.in.bits.func3, 0.U(4.W))(
    Seq(
      "b000".U -> "b0001".U(4.W), //sb
      "b001".U -> "b0011".U(4.W), //sh
      "b010".U -> "b1111".U(4.W) //sw
    )
  )
  val mem_write_size = MuxLookup(io.in.bits.func3, 0.U(3.W))(
    Seq(
      "b000".U -> "b000".U(3.W), //sb
      "b001".U -> "b001".U(3.W), //sh
      "b010".U -> "b010".U(3.W) //sw
    )
  )
  val write_data_moved = (io.in.bits.src2) << ((io.in.bits.alu_result(1, 0)) << 3)

  val mask_moved = mem_write_mask << ((io.in.bits.alu_result)(1, 0))

  //axi_signals_write
  io.axi.WA.valid      := sig_awvalid
  io.axi.WA.bits.addr  := io.in.bits.alu_result
  io.axi.WD.bits.data  := write_data_moved
  io.axi.WD.bits.wstrb := mask_moved
  io.axi.WA.bits.size  := mem_write_size //写入数据的大小
  io.axi.WD.valid      := sig_wvalid
  io.axi.WR.ready      := true.B
  //暂时忽略错误处理

  // reg to hold read_result
  val read_res = Reg(UInt(CVAL.DLEN.W))
  io.out.bits.mem_read_result := read_res
  read_res                    := mem_read_result

  //signals for mem_trace and difftest
  val check_mem = Module(new DPI_C_CHECK)
  check_mem.io.addr  := io.in.bits.alu_result
  check_mem.io.ren   := io.in.bits.mem_read_enable && state === s_wait_valid
  check_mem.io.wdata := write_data_moved
  check_mem.io.wmask := mask_moved
  check_mem.io.wen   := io.in.bits.mem_write_enable && state === s_wait_valid
  check_mem.io.len   := mem_read_size
  check_mem.io.clock := clock

  //latency trace
  val trace_lsu = Module(new TRACE_LSU)
  trace_lsu.io.addr    := io.in.bits.alu_result
  trace_lsu.io.w_start := io.in.bits.mem_write_enable && state === s_wait_valid
  trace_lsu.io.w_end   := io.axi.WR.valid
  trace_lsu.io.r_start := io.in.bits.mem_read_enable && state === s_wait_valid
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
//:LSU 取到数据/写入数据--使用valid
//:LSU 延迟
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
