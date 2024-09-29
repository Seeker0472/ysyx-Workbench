package core

import chisel3._
import chisel3.util._
import Constants_Val._
import core.IO._
import Constants_Val.CVAL.DLEN

//存放PC，负责取出指令
class IFU extends Module {
  val io = IO(new Bundle {
    val in = Flipped(Decoupled(new WBU_O))
    // val inst_now = Output(UInt(CVAL.DLEN.W))
    val out   = Decoupled(new IFUO())
    val axi   = Flipped(new AXIReadIO())
    val rwerr = Input(Bool())
  })
  // states
  val s_idle :: s_fetching :: s_valid :: s_error :: Nil = Enum(4)
  val state                                             = RegInit(s_fetching)

  // icache
  val icache = Module(new icache)
  icache.io.axi <> io.axi

  // pc
  println(s"PC_VALUE: ${scala.util.Properties.envOrElse("PC_VALUE", "Default:h30000000")}")
  val PC_VALUE = scala.util.Properties.envOrElse("PC_VALUE", "h30000000").U(CVAL.DLEN.W)
  val pc       = RegInit(PC_VALUE)
  icache.io.addr       := pc
  icache.io.addr_valid := state === s_fetching

  //out
  io.out.valid      := state === s_valid
  io.out.bits.pc    := pc
  io.out.bits.instr := icache.io.inst

  // in
  io.in.ready := true.B
  val in_regbits  = RegNext(io.in.bits)
  val in_regvalid = RegNext(io.in.valid)

  when(in_regvalid) {
    pc := Mux(state === s_error, 0.U, in_regbits.n_pc)
  }
  when(io.rwerr) {
    state := s_error
  }

  state := MuxLookup(state, s_idle)(
    Seq(
      s_idle -> Mux(in_regvalid, s_fetching, s_idle),
      s_fetching -> Mux(icache.io.inst_valid, s_valid, s_fetching),
      s_valid -> Mux(io.out.ready, s_idle, s_valid),
      s_error -> s_error
    )
  )

  //TRACE_IFU
  val trace_ifu = Module(new TRACE_IFU)
  trace_ifu.io.addr    := pc
  trace_ifu.io.f_start := state === s_fetching
  trace_ifu.io.f_end   := state === s_valid
  trace_ifu.io.clock   := clock

  //INST_TRACE
  val inst_trace = Module(new TRACE_INST)
  inst_trace.io.inst  := icache.io.inst
  inst_trace.io.clock := clock

}
//DONE:IFU取到指令-使用AXIRDvalid
//DONE:IFU延迟

/*
  addr,f/ffin
 */
class TRACE_IFU extends BlackBox with HasBlackBoxInline {
  val io = IO(new Bundle {
    val addr    = Input(UInt(CVAL.DLEN.W))
    val f_start = Input(Bool())
    val f_end   = Input(Bool())
    val clock   = Input(Clock())
  })
  setInline(
    "trace_ifu.v",
    """import "DPI-C" function void trace_ifu(int unsigned addr,bit start_end);
      |module TRACE_IFU(
      |  input f_start,
      |  input f_end,      
      |  input [31:0] addr,
      |  input clock
      |);
      | reg f;
      | initial f=1'b0;
      |always @(negedge clock) begin
      |   if (f_start&&f==1'b0) begin
      |      trace_ifu(addr,1'b1);
      |   f=1'b1;
      |  end
      |   if (f_end&&f==1'b1) begin
      |      trace_ifu(addr,1'b0);
      |  f=1'b0;
      |  end
      | end
      |endmodule
    """.stripMargin
  )
}
class TRACE_INST extends BlackBox with HasBlackBoxInline {
  val io = IO(new Bundle {
    val inst  = Input(UInt(CVAL.DLEN.W))
    val clock = Input(Clock())
  })
  setInline(
    "trace_inst.v",
    """import "DPI-C" function void trace_inst(int unsigned inst_now);
      |module TRACE_INST(
      |  input [31:0] inst,
      |  input clock
      |);
      |always @(negedge clock) begin
      |  trace_inst(inst);
      |end
      |endmodule
    """.stripMargin
  )
}
