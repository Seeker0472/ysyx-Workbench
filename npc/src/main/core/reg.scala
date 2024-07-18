package core

import chisel3._
import chisel3.util._
import Constants_Val._

class REG extends Module {
  val io = IO(new Bundle {
    val read_No_1 = Input(UInt(CVAL.REG_ADDR_LEN.W))
    val read_1    = Output(UInt(CVAL.DLEN.W))
    val read_No_2 = Input(UInt(CVAL.REG_ADDR_LEN.W))
    val read_2    = Output(UInt(CVAL.DLEN.W))

    val write_en       = Input(Bool())
    val write_No       = Input(UInt(CVAL.REG_ADDR_LEN.W))
    val reg_write_data = Input(UInt(CVAL.DLEN.W))

    val csr_read_No = Input(UInt(CVAL.CSR_ADDR_LEN.W))
    val csr_read    = Output(UInt(CVAL.DLEN.W))

    val csr_write_en   = Input(Bool())
    val csr_write_No   = Input(UInt(CVAL.CSR_ADDR_LEN.W))
    val csr_write_data = Input(UInt(CVAL.DLEN.W))

    val csr_mstvec = Output(UInt(CVAL.DLEN.W))
  })

  val regs = RegInit(VecInit(Seq.fill(CVAL.REG_NUM)(0.U(CVAL.DLEN.W))))
  val csrs = RegInit(VecInit(Seq.fill(3)(0.U(CVAL.DLEN.W))))
  
  //TODO:暂时简化实现，这两个寄存器的值保持不动
  csrs(1.U):=0xb.U;//mcause
  csrs(2.U):=0x1800.U;//mstatus
  
  regs(0.U) := 0.U
  io.read_1 := regs(io.read_No_1)
  io.read_2 := regs(io.read_No_2)
//目前只实例化了这几个reg，使用mux来获取寄存器的数值,默认获取mepc
  val csr_r_ADDR = MuxLookup(io.csr_read_No, 3.U)(
    Seq(
      0x305.U -> 0.U,
      0x342.U -> 1.U,
      0x300.U -> 2.U,
      0x341.U -> 3.U,
    )
  )
  //默认写入mepc
  val csr_w_addr = MuxLookup(io.csr_write_No, 3.U)(
    Seq(
      0x305.U -> 0.U,
      0x342.U -> 1.U,
      0x300.U -> 2.U,
      0x341.U -> 3.U
    )
  )
  io.csr_read := csrs(csr_r_ADDR)
  io.csr_mstvec:=csrs(0.U)//mstvec--支持ecall

  when(io.write_en && io.write_No =/= 0.U) { //保证寄存器不被写入
    regs(io.write_No) := io.reg_write_data
  }
  when(io.csr_write_en) { 
    csrs(csr_r_ADDR) := io.csr_write_data
  }
}
