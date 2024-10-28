package core

import chisel3._
import chisel3.util._

class BPU extends Module {
  val io = IO(new Bundle {
    val pc           = Input(UInt(32.W))
    val wbu_pc       = Input(UInt(32.W))
    val wbu_n_pc     = Input(UInt(32.W))
    val update_bpu   = Input(Bool())
    val n_pc_predict = Output(UInt(32.W))
  })
  val btb = new Bundle {
    val pc   = RegInit(VecInit(Seq.fill(2)(0.U(32.W))))
    val n_pc = RegInit(VecInit(Seq.fill(2)(0.U(32.W))))
  }
  // select whitch block to replace
  val tag = RegInit(0.U(1.W))

  //match logic
  val match_result = Wire(UInt(32.W))
  match_result := io.pc + 4.U

  // for (i <- 0 until 2) {
  //   when(btb.pc(i) === io.pc) {
  //     match_result := btb.n_pc(i)
  //     tag          := (i).U
  //   }
  // }

  io.n_pc_predict := match_result

  //replace logic
  val replace_addr = ~tag
  when(io.update_bpu) {
    btb.pc(replace_addr)   := io.wbu_pc
    btb.n_pc(replace_addr) := io.wbu_n_pc
    tag                    := replace_addr
  }

}
