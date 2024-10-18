package core

import chisel3._
import chisel3.util._
import core.IO._
import Constants_Val.CVAL.DLEN
import scala.math

// 31    m+n m+n-1   m m-1    0
// +---------+---------+--------+
// |   tag   |  index  | offset |
// +---------+---------+--------+
//

object ICACHE_Const {
  val BLOCK_SIZE = 8
  val BLOCK_NUM  = 8
}

class icache extends Module {
  val io = IO(new Bundle {
    val axi          = Flipped(new AXIReadIO())
    val inst         = Output(UInt(32.W))
    val inst_valid   = Output(Bool())
    val addr         = Input(UInt(32.W))
    val addr_valid   = Input(Bool())
    val flush_icache = Input(Bool())
  })

  val block_size = ICACHE_Const.BLOCK_SIZE
  val block_num  = ICACHE_Const.BLOCK_NUM

  //calc the len
  val offset_len = (math.log(block_size) / math.log(2)).toInt
  val index_len  = (math.log(block_num) / math.log(2)).toInt
  val tag_len    = 32 - offset_len - index_len

  println(s"offset_len: $offset_len, index_len: $index_len, tag_len: $tag_len")

  // the state machine
  val s_idle :: s_fetching :: s_wait_data :: s_error :: Nil = Enum(4)
  val state                                                 = RegInit(s_idle)

  //Tag and cache
  val cachetag = RegInit(VecInit(Seq.fill(block_num)(0.U((1 + tag_len).W))))
  val cache    = RegInit(VecInit(Seq.fill(block_num)(0.U((block_size * 8).W))))
  //flush
  when(io.flush_icache) {
    cachetag := VecInit(Seq.fill(block_num)(0.U))
  }

  // split the tag, index, offset from addr
  val fetch_addr = RegEnable(io.addr, 0.U, state === s_idle)
  // val fetch_addr = io.addr

  val fetch_tag   = fetch_addr(31, 31 - tag_len + 1)
  val fetch_index = fetch_addr(31 - tag_len, 31 - tag_len - index_len + 1)

  val addr_tag    = io.addr(31, 31 - tag_len + 1)
  val addr_index  = io.addr(31 - tag_len, 31 - tag_len - index_len + 1)
  val addr_offset = io.addr(offset_len - 1, 0) << 3

  // get the targeted cache block
  val target_block_tag = cachetag(addr_index)
  val hit = target_block_tag(tag_len).asBool && (target_block_tag(
    tag_len - 1,
    0
  ) === addr_tag)

  // if miss, firstly load data into cache,next cyc visit cache and resut into a hit.

  //get the data
  val data = (cache(addr_index) >> (addr_offset))(31, 0)
  io.inst := data

  // the state machine

  state := MuxLookup(state, s_idle)(
    Seq(
      s_idle -> Mux(io.addr_valid && ~hit, s_fetching, s_idle),
      s_fetching -> Mux(io.axi.RA.ready, s_wait_data, s_fetching),
      s_wait_data -> Mux(io.axi.RD.bits.last, s_idle, s_wait_data)
    )
  )
  // axi
  io.axi.RA.valid     := state === s_fetching
  io.axi.RA.bits.addr := fetch_addr & ~(((1 << offset_len) - 1).U(32.W))
  io.axi.RA.bits.size := "b010".U
  io.axi.RD.ready     := true.B
  io.axi.RA.bits.id   := 0.U //TODO!!!!!
  io.axi.RA.bits.len  := (block_size / 4 - 1).U

  io.inst_valid := io.addr_valid && state === s_idle && hit //TODO : return the hit data instantly!!!!!!!
  // miss,update  cache
  val data_read = io.axi.RD.bits.data
  when(io.axi.RD.valid && state === s_wait_data) {
    cachetag(fetch_index) := Cat(1.U(1.W), fetch_tag)
    cache(fetch_index)    := Cat(data_read, cache(fetch_index)(block_size * 8 - 1, 32))
  }

  //Trace hit
  val hit_trace = Module(new TRACE_ICache)
  hit_trace.io.clock := clock
  hit_trace.io.valid := state === s_idle && io.addr_valid
  hit_trace.io.hit   := state === s_idle && hit
  hit_trace.io.reset := reset
  hit_trace.io.inst  := data
  hit_trace.io.addr  := io.addr

}

class TRACE_ICache extends BlackBox with HasBlackBoxInline {
  val io = IO(new Bundle {
    val clock = Input(Clock())
    val valid = Input(Bool())
    val hit   = Input(Bool())
    val reset = Input(Reset())
    val addr  = Input(UInt(32.W))
    val inst  = Input(UInt(32.W))
  })
  setInline(
    "trace_hit.v",
    """import "DPI-C" function void trace_hit(bit hit);
      |import "DPI-C" function void record_inst(int unsigned addr,int unsigned inst);
      |module TRACE_ICache(
      |  input valid,
      |  input clock,
      |  input hit,
      |  input reset,
      |  input[31:0] addr,
      |  input[31:0] inst
      |); 
      |always @(negedge clock) begin
      |   if (valid&&~reset) begin
      |      trace_hit(hit);
      |   if (hit) begin
      |      record_inst(addr,inst);
      |   end
      |  end
      | end
      |endmodule
    """.stripMargin
  )
}
