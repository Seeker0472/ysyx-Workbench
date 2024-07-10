package core

import chisel3._
import Constants_Val._

class REG extends Module{
    val io=IO(new Bundle{
        val read_No_1 = Input(UInt(CVAL.REG_ADDR_LEN.W))
        val read_1 = Output(UInt(CVAL.DLEN.W))
        val read_No_2 = Input(UInt(CVAL.REG_ADDR_LEN.W))
        val read_2 = Output(UInt(CVAL.DLEN.W))
        val write_en = Input(Bool())
        val write_No = Input(UInt(CVAL.REG_ADDR_LEN.W))
        val reg_write_data = Input(UInt(CVAL.DLEN.W))
    })

    val regs = RegInit(VecInit(Seq.fill(CVAL.REG_NUM)(0.U(CVAL.DLEN.W))))
    regs(0.U):=0.U
    io.read_1:=regs(io.read_No_1)
    io.read_2:=regs(io.read_No_2)

  when(io.write_en && io.write_No =/= 0.U) {
    regs(io.write_No) := io.reg_write_data
  }
}