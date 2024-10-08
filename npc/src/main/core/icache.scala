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

class icache extends Module {
  val io = IO(new Bundle {
    val axi        = Flipped(new AXIReadIO())
    val inst       = Output(UInt(32.W))
    val inst_valid = Output(Bool())
    val addr       = Input(UInt(32.W))
    val addr_valid = Input(Bool())
    val flush  = Input(Bool())
  })

  val block_size = 8
  val block_num  = 8

  //calc the len
  val offset_len = (math.log(block_size) / math.log(2)).toInt
  val index_len  = (math.log(block_num) / math.log(2)).toInt
  val tag_len    = 32 - offset_len - index_len

  println(s"offset_len: $offset_len, index_len: $index_len, tag_len: $tag_len")

  //Tag and cache
  val cachetag = RegInit(VecInit(Seq.fill(block_num)(0.U((1 + tag_len).W))))
  val cache    = RegInit(VecInit(Seq.fill(block_num)(0.U((block_size * 8).W))))
  //flush
  when(flush){
    cachetag := VecInit(Seq.fill(block_num)(0.U))
  }

  // split the tag, index, offset from addr
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
  val s_idle :: s_fetching :: s_wait_data :: s_valid :: s_error :: Nil = Enum(5)
  val state                                                            = RegInit(s_idle)
  state := MuxLookup(state, s_idle)(
    Seq(
      s_idle -> Mux(
        io.addr_valid && hit,
        s_valid,
        Mux(io.addr_valid, s_fetching, s_idle)
      ),
      s_fetching -> Mux(io.axi.RA.ready, s_wait_data, s_fetching),
      s_wait_data -> Mux(io.axi.RD.bits.last, s_valid, s_wait_data),
      s_valid -> s_idle // Didn't stay
    )
  )
  // axi
  io.axi.RA.valid     := state === s_fetching
  io.axi.RA.bits.addr := io.addr & ~(((1 << offset_len) - 1).U(32.W))
  io.axi.RA.bits.size := "b010".U
  io.axi.RD.ready     := true.B
  io.axi.RA.bits.id   := 0.U //TODO!!!!!
  io.axi.RA.bits.len  := (block_size / 4 - 1).U

  io.inst_valid := state === s_valid
  // miss,update  cache
  val data_read = io.axi.RD.bits.data
  when(io.axi.RD.valid && state === s_wait_data) {
    target_block_tag  := Cat(1.U(1.W), addr_tag)
    cache(addr_index) := Cat(data_read, cache(addr_index)(block_size * 8 - 1, 32))
  }

  //Trace hit
  val hit_trace = Module(new TRACE_ICache)
  hit_trace.io.clock := clock
  hit_trace.io.valid := state === s_idle && io.addr_valid && hit
}

class TRACE_ICache extends BlackBox with HasBlackBoxInline {
  val io = IO(new Bundle {
    val clock = Input(Clock())
    val valid = Input(Bool())
  })
  setInline(
    "trace_hit.v",
    """import "DPI-C" function void trace_hit();
      |module TRACE_ICache(
      |  input valid,
      |  input clock
      |); 
      | reg last_stat;
      | initial
      | last_stat = 1'b0;
      |always @(negedge clock) begin
      |   if (valid&&!last_stat) begin
      |      trace_hit();
      |  end
      | last_stat = valid;
      | end
      |endmodule
    """.stripMargin
  )
}
