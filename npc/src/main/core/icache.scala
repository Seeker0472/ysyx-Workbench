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


class icache extends Module{
    val io = IO(new Bundle{
        val axi = Flipped(new AXIReadIO())
        val inst = Output(UInt(32.W))
        val inst_valid = Output(Bool())
        val addr = Input(UInt(32.W))
        val addr_valid = Input(Bool())
    })

  val block_size = 4
  val block_num = 16
  //assume ifu will only get 32bit wide data!
  //tag_len=log2<block_size/4>+log2<block_num>=log2<block_num*block_size/4>
  //val tag_len = math.log(block_num*block_size/4)/math.log(2)
  val offset_len = (math.log(block_size/4)/math.log(2)).toInt
  val index_len = (math.log(block_num)/math.log(2)).toInt
  val tag_len = 32-offset_len-index_len 
  //calc cache_line size:[1(valid)][(tag_len)][block_size*8(data)]

  val cache = RegInit(Vec(block_num,VecInit(Seq.fill(block_size)(0.U((1+tag_len+block_size*8).W)))))
  
  //split the tag, index, offset from addr
  val addr_tag = io.addr(31,32-tag_len)
  val addr_index = io.addr(31-tag_len,31-tag_len-index_len)
  val addr_offset = 0//TODO

  //get the targeted cache block
  val target_block = cache(addr_index)
  val hit = target_block(tag_len+block_size*8,tag_len+block_size*8)&&(target_block(tag_len+block_size*8-1,block_size*8)===addr_tag)
  //if miss, firstly load data into cache,next cyc visit cache and resut into a hit.
  val data = target_block(block_size*8-1,0)
  io.inst := data

  //the state machine 
  val s_idle :: s_fetching :: s_wait_data :: s_valid :: s_error :: Nil = Enum(5)
  val state = RegInit(s_idle)
  state := MuxLookUp(state,s_idle)(Seq(
    s_idle -> Mux(io.addr_valid&&hit,s_valid,Mux(io.addr_valid,s_fetching,s_idle)),
    s_fetching -> Mux(io.axi.RA.ready,s_wait_data,s_fetching),
    s_wait_data -> Mux(io.axi.RD.valid,s_valid,s_wait_data),
    s_valid -> s_idle //Didn't stay
    ))
  //axi
  io.axi.RA.valid = state===s_fetching
  io.axi.RA.bits.addr:=io.addr
  io.axi.RA.bits.size := "b010".U
  io.axi.RD.ready     := true.B
  io.inst_valid := state===s_valid
  //miss,update  cache
  val data_read = io.RD.bits.data
  when(io.axi.RD.valid&&state===s_wait_data){
    target_block := Cat(1.U(1.W),Cat(addr_tag,data_read))
  }
}                
