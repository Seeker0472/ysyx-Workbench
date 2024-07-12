package core

import chisel3._
import Constants_Val._
import core.IO._
import chisel3.util.Mux1H
import chisel3.util.MuxLookup

class EXU extends Module {
  val io = IO(new Bundle {
    val in  = Input(new EXU_I)
    val out = Output(new EXU_O)
  })
  val alu_val1 = Mux(io.in.alu_use_pc, io.in.pc, io.in.src1)
  val alu_val2 = Mux(io.in.alu_use_Imm_2, io.in.imm, io.in.src2)

  val mem = Module(new MEM()) //TODO::::::把Mem模块放在执行单元是否科学？？？
  mem.io.clock := clock  // 连接时钟信号
  val alu = Module(new ALU())

  val comp = Module(new Branch_comp())

  comp.io.src1      := io.in.src1
  comp.io.src2      := io.in.src2
  comp.io.comp_type := io.in.branch_type
  val go_branch = comp.io.result

  alu.io.in.src1        := alu_val1
  alu.io.in.src2        := alu_val2
  alu.io.in.alu_op_type := io.in.alu_op_type

  //mem R/W
  mem.io.read_enable  := io.in.mem_read_enable
  mem.io.write_enable := io.in.mem_write_enable
  //TODO: 这里需要设计两个信号吗
  mem.io.read_addr  := alu.io.result
  mem.io.write_addr := alu.io.result
  val mrres = mem.io.read_data
  val mrrm = mrres >>( (alu.io.result &(0x3.U))<<1)// 读取内存,不对齐访问!!
  //注意符号拓展！！！
  val mem_read_result_sint = MuxLookup(io.in.mem_read_type, 0.S)(
    Seq(
      Load_Type.lb -> mrrm(7, 0).asSInt,
      Load_Type.lh -> mrrm(15, 0).asSInt,
      Load_Type.lw -> mrrm(31, 0).asSInt,
      Load_Type.lbu -> mrrm(7, 0).zext,
      Load_Type.lhu -> mrrm(15, 0).zext
    )
  )
  val mem_read_result = mem_read_result_sint.asUInt


  val mem_write_mask = MuxLookup(io.in.mem_write_type, 0.U)(
    Seq(
      Store_Type.sb -> "b00000011".U(8.W),
      Store_Type.sh -> "b00001111".U(8.W),
      Store_Type.sw -> "b11111111".U(8.W)
    )
  )
  mem.io.write_mask := mem_write_mask
  mem.io.write_data := io.in.src2

  //如果是store，Reg_Write_Enable应该是False
  // val result   = alu.io.result
  val result   = Mux(io.in.mem_read_enable, mem_read_result, alu.io.result)
  val pc_plus4 = io.in.pc + 4.U

  val next_pc = Mux(io.in.pc_jump || (io.in.is_branch && go_branch), result, pc_plus4)
  io.out.reg_out := Mux(io.in.pc_jump, pc_plus4, result)
  io.out.n_pc    := next_pc
}

class Branch_comp extends Module {
  val io = IO(new Bundle {
    val src1      = Input(UInt(CVAL.DLEN.W))
    val src2      = Input(UInt(CVAL.DLEN.W))
    val comp_type = Input(Branch_Type())
    val result    = Output(Bool())
  })
  io.result := MuxLookup(io.comp_type, false.B)(
    Seq(
      Branch_Type.beq -> (io.src1 === io.src2),
      Branch_Type.bne -> (io.src1 =/= io.src2),
      Branch_Type.blt -> (io.src1.asSInt < io.src2.asSInt),
      Branch_Type.bge -> (io.src1.asSInt >= io.src2.asSInt),
      Branch_Type.bltu -> (io.src1 < io.src2),
      Branch_Type.bgeu -> (io.src1 >= io.src2)
    )
  )
}
