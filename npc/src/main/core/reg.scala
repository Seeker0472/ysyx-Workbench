package core

import chisel3._
import chisel3.util._
import Constants_Val._
import core.IO._

class REG extends Module {
  val io = IO(new Bundle {
    val Rread1 = Flipped(new RegReadIO)
    val Rread2 = Flipped(new RegReadIO)
    val Rwrite = Flipped(new RegWriteIO)

    val CSRread  = Flipped(new CSRReadIO)
    val CSRwrite = Flipped(new CSRWriteIO)

    val csr_mstvec = Output(UInt(CVAL.DLEN.W))
  })

  val regs = RegInit(VecInit(Seq.fill(15)(0.U(CVAL.DLEN.W))))
  val csrs = RegInit(VecInit(Seq.fill(4)(0.U(CVAL.DLEN.W))))

  //TODO:暂时简化实现，这两个寄存器的值保持不动
  csrs(1.U) := 0xb.U; //mcause
  csrs(2.U) := 0x1800.U; //mstatus

  // regs(0.U)      := 0.U
  io.Rread1.data := Mux(io.Rread1.addr(3,0)===0.U,0.U,regs(io.Rread1.addr(3,0)-1.U))
  io.Rread2.data := Mux(io.Rread2.addr(3,0)===0.U,0.U,regs(io.Rread2.addr(3,0)-1.U))
//目前只实例化了这几个reg，使用mux来获取寄存器的数值,默认获取mepc
  val csr_r_ADDR = MuxLookup(io.CSRread.addr, 3.U)(
    Seq(
      0x305.U -> 0.U,
      0x342.U -> 1.U,
      0x300.U -> 2.U,
      0x341.U -> 3.U,
    )
  )
  //默认写入mepc
  val csr_w_addr = MuxLookup(io.CSRwrite.addr, 3.U)(
    Seq(
      0x305.U -> 0.U,
      0x342.U -> 1.U,
      0x300.U -> 2.U,
      0x341.U -> 3.U
    )
  )
  // io.CSRread.data := csrs(csr_r_ADDR)
  io.CSRread.data := MuxLookup(io.CSRread.addr,csrs(csr_r_ADDR))(Seq(
      0xF11.U -> 0x79737978.U,////ysyx
      0xF12.U -> 0x15fdf65.U,//学号
      )
  )

  io.csr_mstvec   := csrs(0.U) //mstvec--支持ecall

  when(io.Rwrite.write_enable && io.Rwrite.addr =/= 0.U) { //保证寄存器不被写入
    regs(io.Rwrite.addr(3,0)-1.U) := io.Rwrite.data
  }
  when(io.CSRwrite.write_enable) {
    csrs(csr_w_addr) := io.CSRwrite.data
  }
}
