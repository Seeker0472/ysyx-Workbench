package core

import chisel3._
import chisel3.util._
import Constants_Val.CVAL
import core.IO._

import chisel3.util.BitPat
import chisel3.util.experimental.decode.DecodeField
import chisel3.util.experimental.decode._

object Inst_Type_Enum extends ChiselEnum {
  val R_Type, I_Type, S_Type, B_Type, U_Type, J_Type = Value
}

class Decoder extends Module {
  val io = IO(new Bundle {
    val in     = Flipped(Decoupled(new IFUO))
    val ebreak = Output(Bool())
    val flush  = Output(Bool())
    val out    = Decoupled(new DecoderO)
  })
  //state_machine
  val s_idle :: s_valid :: Nil = Enum(2)

  val state = RegInit(s_idle)

  state := MuxLookup(state, s_idle)(
    Seq(
      s_idle -> Mux(io.in.valid, s_valid, s_idle),
      s_valid -> Mux(io.out.ready, s_idle, s_valid)
    )
  )

  //in
  io.in.ready  := state === s_idle
  io.out.valid := state === s_valid

  //pass_through
  io.out.bits.pc := io.in.bits.pc

  val Patterns = decodePatterns.Patterns

  //Imms
  val imm_I_Raw = io.in.bits.instr(31, 20)
  val immI      = Cat(Fill(20, imm_I_Raw(11)), imm_I_Raw)
  val imm_S_Raw = Cat(io.in.bits.instr(31, 25), io.in.bits.instr(11, 7))
  val immS      = Cat(Fill(20, imm_S_Raw(11)), imm_S_Raw)
  val imm_B_Raw =
    Cat(io.in.bits.instr(31, 31), io.in.bits.instr(7, 7), io.in.bits.instr(30, 25), io.in.bits.instr(11, 8), 0.U(1.W))
  val immB      = Cat(Fill(19, imm_B_Raw(12)), imm_B_Raw)
  val imm_U_Raw = Cat(io.in.bits.instr(31, 12), 0.U(12.W))
  val immU      = imm_U_Raw
  val imm_J_Raw = Cat(
    io.in.bits.instr(31, 31),
    io.in.bits.instr(19, 12),
    io.in.bits.instr(20, 20),
    io.in.bits.instr(30, 21),
    0.U(1.W)
  )
  val immJ = Cat(Fill(11, imm_J_Raw(20)), imm_J_Raw)

  // val opcode = io.in.bits.instr(6, 0)
  val rs1   = io.in.bits.instr(19, 15)
  val rs2   = io.in.bits.instr(24, 20)
  val rd    = io.in.bits.instr(11, 7)
  val func3 = io.in.bits.instr(14, 12)

  val decodedResults =
    new DecodeTable(
      Patterns,
      Seq(
        InstType,
        Use_IMM_2,
        Use_PC_1,
        Is_Jump,
        R_Write_Enable,
        Is_Ebreak,
        ALUOp_Gen,
        Read_En,
        Write_En,
        Is_Branch,
        CSRRW,
        CSRR_ALU_Type,
        Is_Mret,
        Is_Ecall,
        Is_fenceI
      )
    )
      .decode(io.in.bits.instr)
  val Type = decodedResults(InstType)
  val imm = MuxLookup(Type, 0.U)(
    Seq(
      // Inst_Type_Enum.R_Type -> Rval2, // R-Type
      Inst_Type_Enum.I_Type -> immI, // I-type
      Inst_Type_Enum.S_Type -> immS, // S-type
      Inst_Type_Enum.B_Type -> immB, // B-type
      Inst_Type_Enum.U_Type -> immU, // U-type
      Inst_Type_Enum.J_Type -> immJ // J-type
    )
  )
  //数据
  io.out.bits.rs1 := rs1
  io.out.bits.rs2 := rs2
  io.out.bits.rd  := rd
  io.out.bits.imm := imm

  //控制逻辑
  io.out.bits.alu_use_Imm_2 := decodedResults(Use_IMM_2)
  io.out.bits.alu_use_pc    := decodedResults(Use_PC_1)

  io.out.bits.alu_op_type      := decodedResults(ALUOp_Gen)
  io.out.bits.pc_jump          := decodedResults(Is_Jump)
  io.out.bits.reg_write_enable := decodedResults(R_Write_Enable)

  io.ebreak := decodedResults(Is_Ebreak) && state === s_valid

  io.flush := decodedResults(Is_fenceI) && state === s_valid

  io.out.bits.mem_read_enable := decodedResults(Read_En)

  io.out.bits.mem_write_enable := decodedResults(Write_En)

  io.out.bits.func3 := func3

  io.out.bits.is_branch := decodedResults(Is_Branch)

  io.out.bits.csrrw        := decodedResults(CSRRW)
  io.out.bits.csr_alu_type := decodedResults(CSRR_ALU_Type)

  io.out.bits.ecall := decodedResults(Is_Ecall)
  io.out.bits.mret  := decodedResults(Is_Mret)

  //Trace
  val trace_decoder = Module(new TRACE_DECODER)
  trace_decoder.io.clock := clock
  trace_decoder.io.mem_R := decodedResults(Read_En) //MEM_Read
  trace_decoder.io.mem_W := decodedResults(Write_En) //MEM_Write
  trace_decoder.io.calc  := decodedResults(ALUOp_Gen) =/= ALU_Op.inv //calc instr
  trace_decoder.io.csr   := decodedResults(CSRRW) //scrrw/scrrs/mert/ecall
  trace_decoder.io.valid := state === s_valid //valid

}
//DONE:译码出来的指令类型
/*
1.访存RW
2.是否是运算-检测inv
3.csr-csrrw/mret
 */
class TRACE_DECODER extends BlackBox with HasBlackBoxInline {
  val io = IO(new Bundle {
    val clock = Input(Clock())
    val mem_R = Input(Bool())
    val mem_W = Input(Bool())
    val calc  = Input(Bool())
    val csr   = Input(Bool())
    val valid = Input(Bool())
  })
  setInline(
    "trace_decoder.v",
    """import "DPI-C" function void trace_decoder(bit mem_R,bit mem_W,bit calc,bit csr);
      |module TRACE_DECODER(
      |  input mem_R,
      |  input mem_W,
      |  input calc,
      |  input csr,
      |  input valid,
      |  input clock
      |); 
      | reg last_stat;
      | initial
      | last_stat = 1'b0;
      |always @(negedge clock) begin
      |   if (valid && !last_stat) begin
      |      trace_decoder(mem_R,mem_W,calc,csr);
      |  end
      | last_stat = valid;
      | end
      |endmodule
    """.stripMargin
  )
}
