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
    val in             = Flipped(Decoupled(new IFUO))
    val lsu_w_addr     = Input(UInt(CVAL.REG_ADDR_LEN.W))
    val exu_w_addr = Input(UInt(CVAL.REG_ADDR_LEN.W))
    val decoder_pc     = Decoupled(UInt(CVAL.DLEN.W))
    val ebreak         = Output(Bool())
    val flush_icache   = Output(Bool())
    val flush_pipeline = Input(Bool())
    val reg1 = (new RegReadIO)
    val reg2 = (new RegReadIO)
    val csr  = (new CSRReadIO)
    val out            = Decoupled(new DecoderO)
  })
  //state_machine
  // val s_idle :: s_valid :: s_conflict :: Nil = Enum(3)//TODO:del valid

  // val state = RegInit(s_idle)

  io.decoder_pc.bits  := io.in.bits.pc
  // io.decoder_pc.valid := io.in.valid || state =/= s_idle
  io.decoder_pc.valid := io.in.valid 

  //in
  // io.in.ready := state === s_idle

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
  // io.out.bits.rs1 := rs1
  // io.out.bits.rs2 := rs2
  io.reg1.addr := rs1
  io.reg2.addr := rs2
  io.csr.addr  := imm
  io.out.bits.src1:= io.reg1.data
  io.out.bits.src2:=io.reg2.data
  io.out.bits.csr_data:=io.csr.data

  io.out.bits.rd  := rd
  io.out.bits.imm := imm

  //控制逻辑
  io.out.bits.alu_use_Imm_2 := decodedResults(Use_IMM_2)
  io.out.bits.alu_use_pc    := decodedResults(Use_PC_1)

  io.out.bits.alu_op_type      := decodedResults(ALUOp_Gen)
  io.out.bits.pc_jump          := decodedResults(Is_Jump)
  io.out.bits.reg_write_enable := decodedResults(R_Write_Enable)

  // io.ebreak := decodedResults(Is_Ebreak) && state === s_valid
  io.ebreak := decodedResults(Is_Ebreak) && io.in.valid

  // io.flush_icache := decodedResults(Is_fenceI) && state === s_valid
  io.flush_icache := decodedResults(Is_fenceI) && io.in.valid

  io.out.bits.mem_read_enable := decodedResults(Read_En)

  io.out.bits.mem_write_enable := decodedResults(Write_En)

  io.out.bits.func3 := func3

  io.out.bits.is_branch := decodedResults(Is_Branch)

  io.out.bits.csrrw        := decodedResults(CSRRW)
  io.out.bits.csr_alu_type := decodedResults(CSRR_ALU_Type)

  io.out.bits.ecall := decodedResults(Is_Ecall)
  io.out.bits.mret  := decodedResults(Is_Mret)
  // reg conflict whith EXU/(LS+WB) 
  val conflict = MuxLookup(Type, false.B)(
    Seq(
      Inst_Type_Enum.R_Type -> (((io.lsu_w_addr === rs1&&rs1 =/= 0.U) || (io.lsu_w_addr === rs2&&rs2 =/= 0.U)) || ((io.exu_w_addr === rs1&&rs1 =/= 0.U) || (io.exu_w_addr === rs2&&rs2 =/= 0.U))  ),
      Inst_Type_Enum.I_Type -> (((io.lsu_w_addr === rs1) && rs1 =/= 0.U)||((io.exu_w_addr === rs1) && rs1 =/= 0.U)),
      Inst_Type_Enum.S_Type -> (((io.lsu_w_addr === rs2) && rs2 =/= 0.U)||((io.exu_w_addr === rs2) && rs2 =/= 0.U)),
      Inst_Type_Enum.B_Type -> (((io.lsu_w_addr === rs1&&rs1 =/= 0.U) || (io.lsu_w_addr === rs2&&rs2 =/= 0.U)) || ((io.exu_w_addr === rs1&&rs1 =/= 0.U) || (io.exu_w_addr === rs2&&rs2 =/= 0.U))  )
    )
  )
  // val conflict = MuxLookup(Type, false.B)(
  //   Seq(
  //     Inst_Type_Enum.R_Type -> ((io.lsu_w_addr === rs1 || io.lsu_w_addr === rs2) && rs1 =/= 0.U && rs2 =/= 0.U),
  //     Inst_Type_Enum.I_Type -> ((io.lsu_w_addr === rs1) && rs1 =/= 0.U),
  //     Inst_Type_Enum.S_Type -> ((io.lsu_w_addr === rs2) && rs2 =/= 0.U),
  //     Inst_Type_Enum.B_Type -> ((io.lsu_w_addr === rs1 || io.lsu_w_addr === rs2) && rs1 =/= 0.U && rs2 =/= 0.U)
  //   )
  // )
  
  // io.out.valid := state === s_valid && ~conflict
  io.in.ready := io.out.ready && ~conflict
  io.out.valid := io.in.valid && ~io.flush_pipeline && ~conflict

  // state := MuxLookup(state, s_idle)(
  //   Seq(
  //     s_idle -> Mux(io.in.valid  && ~io.flush_pipeline, Mux(conflict,s_conflict,s_valid), s_idle),//TODO:这里有bug，如果一直conflict，会一直ready
  //     s_conflict -> Mux(io.flush_pipeline,s_idle,Mux(conflict,s_conflict,s_valid)),
  //     s_valid -> Mux(io.out.ready || io.flush_pipeline, s_idle, s_valid)
  //   )
  // )

  //Trace
  val trace_decoder = Module(new TRACE_DECODER)
  trace_decoder.io.clock := clock
  trace_decoder.io.mem_R := decodedResults(Read_En) //MEM_Read
  trace_decoder.io.mem_W := decodedResults(Write_En) //MEM_Write
  trace_decoder.io.calc  := decodedResults(ALUOp_Gen) =/= ALU_Op.inv //calc instr
  trace_decoder.io.csr   := decodedResults(CSRRW) //scrrw/scrrs/mert/ecall
  // trace_decoder.io.valid := state === s_valid && (io.out.ready || io.flush_pipeline)
  trace_decoder.io.valid := (io.out.ready || io.flush_pipeline)

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
      |always @(negedge clock) begin
      |   if (valid) begin
      |      trace_decoder(mem_R,mem_W,calc,csr);
      |  end
      | end
      |endmodule
    """.stripMargin
  )
}

//指令的类型
object InstType extends DecodeField[InsP, Inst_Type_Enum.Type] {
  def name: String = "InstType"
  override def chiselType = Inst_Type_Enum()
  def genTable(op: InsP): BitPat = {
    val immType = op.Inst_Type
    BitPat(immType.litValue.U((immType.getWidth).W))
  }
}
//src2是否选择Imm
object Use_IMM_2 extends BoolDecodeField[InsP] {
  def name: String = "Use_IMM"
  def genTable(op: InsP) = {
    if (
      op.Inst_Type == Inst_Type_Enum.I_Type || op.Inst_Type == Inst_Type_Enum.S_Type || op.Inst_Type == Inst_Type_Enum.B_Type || op.Inst_Type == Inst_Type_Enum.J_Type || op.name_in
        .matches("auipc") || op.name_in.matches("lui")
    )
      y
    else n
  }
}
//src1是否选择PC -- J-Type & B-Type
object Use_PC_1 extends BoolDecodeField[InsP] {
  def name: String = "Use_PC_1"
  def genTable(op: InsP) = {
    if (
      op.Inst_Type == Inst_Type_Enum.J_Type || op.Inst_Type == Inst_Type_Enum.B_Type || op.name_in.matches("auipc")
    ) //auipc
      y
    else n
  }
}

//是否是无条件跳转
object Is_Jump extends BoolDecodeField[InsP] {
  def name: String = "Is_Jump"
  def genTable(op: InsP) = {
    if (op.Inst_Type == Inst_Type_Enum.J_Type || op.opcode.rawString.matches("1100111"))
      y
    else n
  }

}

//Reg_write_Enable
object R_Write_Enable extends BoolDecodeField[InsP] {
  def name: String = "Reg_W_En"
  def genTable(op: InsP) = {
    //ecall,ebreak有效因为rd为0
    if (op.Inst_Type == Inst_Type_Enum.S_Type || op.Inst_Type == Inst_Type_Enum.B_Type) //！！注意这里是if() n else y!!!!!!!!
      n
    else y
  }
}

//ebreak
object Is_Ebreak extends BoolDecodeField[InsP] {
  def name: String = "Is_Ebreak"
  def genTable(op: InsP) = {
    // if(op.opcode===BitPat("b1110011")&&op.func3===BitPat("b000")&&op.func7===BitPat("b0000001"))
    if (op.name_in == "ebreak")
      y
    else n
  }
}

//mem
object Read_En extends BoolDecodeField[InsP] {
  def name: String = "Read_En"
  def genTable(op: InsP) = {
    if (op.opcode.rawString.matches("0000011"))
      y
    else n
  }
}

//fencei
object Is_fenceI extends BoolDecodeField[InsP] {
  def name: String = "Is_fencei"
  def genTable(op: InsP) = {
    if (op.name_in == "fence.i")
      y
    else n
  }
}

//读取内存的类型
// object Mem_LoadType extends DecodeField[InsP, Load_Type.Type] {
//   def name: String = "Mem_LoadType"
//   override def chiselType = Load_Type()
//   def genTable(op: InsP): BitPat = {
//     val load_type = op.func3.rawString match {
//       case "000" => Load_Type.lb
//       case "001" => Load_Type.lh
//       case "010" => Load_Type.lw
//       case "100" => Load_Type.lbu
//       case "101" => Load_Type.lhu
//       case _     => Load_Type.inv
//     }
//     BitPat(load_type.litValue.U((load_type.getWidth).W))
//   }
// }
// object Mem_WriteType extends DecodeField[InsP, Store_Type.Type] {
//   def name: String = "Mem_WriteType"
//   override def chiselType = Store_Type()
//   def genTable(op: InsP) = {
//     val stype = op.func3.rawString match {
//       case "000" => Store_Type.sb
//       case "001" => Store_Type.sh
//       case "010" => Store_Type.sw
//       case _     => Store_Type.inv
//     }
//     BitPat(stype.litValue.U((stype.getWidth).W))
//   }
// }
// object BranchType extends DecodeField[InsP, Branch_Type.Type] {
//   def name: String = "Branch_Type"
//   override def chiselType = Branch_Type()
//   def genTable(op: InsP) = {
//     val btype = op.func3.rawString match {
//       case "000" => Branch_Type.beq
//       case "001" => Branch_Type.bne
//       case "100" => Branch_Type.blt
//       case "101" => Branch_Type.bge
//       case "110" => Branch_Type.bltu
//       case "111" => Branch_Type.bgeu
//       case _     => Branch_Type.inv
//     }
//     BitPat(btype.litValue.U((btype.getWidth).W))
//   }
// }

//mem
object Write_En extends BoolDecodeField[InsP] {
  def name: String = "Write_En"
  def genTable(op: InsP) = {
    if (op.opcode.rawString.matches("0100011"))
      y
    else n
  }
}

//Branch
object Is_Branch extends BoolDecodeField[InsP] {
  def name: String = "Is_Branch"
  def genTable(op: InsP) = {
    if (op.Inst_Type == Inst_Type_Enum.B_Type)
      y
    else n
  }
}

//csrs
//由于这部分指令都需要读取/写入csr存储器，所以就rw放一起了，同时这个信号也作用于Mux来选择写入存储器的数据
object CSRRW extends BoolDecodeField[InsP] {
  def name: String = "CSRRW"
  def genTable(op: InsP) = {

    //NO
    if (
      op.name_in.matches("csrrw") || op.name_in.matches("csrrs") || op.name_in
        .matches("ecall") || op.name_in.matches("mret")
    )
      y
    else n
  }
}

object Is_Ecall extends BoolDecodeField[InsP] {
  def name: String = "Is_Ecall"
  def genTable(op: InsP) = {
    if (op.name_in.matches("ecall"))
      y
    else n
  }
}

object Is_Mret extends BoolDecodeField[InsP] {
  def name: String = "Is_Mret"
  def genTable(op: InsP) = {
    if (op.name_in.matches("mret"))
      y
    else n
  }
}
//目前csr指令的alu是独立于其他的alu
object CSRR_ALU_Type extends DecodeField[InsP, CSRALU_Type.Type] {
  def name: String = "CSRR_ALU_Type"
  override def chiselType = CSRALU_Type()
  def genTable(op: InsP) = {
    val btype = op.name_in match {
      case "csrrs" => CSRALU_Type.or
      case _       => CSRALU_Type.passreg
    }
    BitPat(btype.litValue.U((btype.getWidth).W))
  }
}

//alu的运算类型
object ALUOp_Gen extends DecodeField[InsP, ALU_Op.Type] {
  def name: String = "ALUOp_Gen"
  override def chiselType = ALU_Op()
  def genTable(op: InsP): BitPat = {
    val op_type = op.name_in match {
      case "add" | "addi" | "jal" | "jalr" | "auipc"               => ALU_Op.add
      case "lb" | "lh" | "lw" | "lbu" | "lhu" | "sb" | "sh" | "sw" => ALU_Op.add
      case "beq" | "bne" | "blt" | "bge" | "bltu" | "bgeu"         => ALU_Op.add
      case "sub"                                                   => ALU_Op.sub
      case "xor" | "xori"                                          => ALU_Op.xor
      case "or" | "ori"                                            => ALU_Op.or
      case "and" | "andi"                                          => ALU_Op.and
      case "sll" | "slli"                                          => ALU_Op.sll
      case "srl" | "srli"                                          => ALU_Op.srl
      case "sra" | "srai"                                          => ALU_Op.sra
      case "slt" | "slti"                                          => ALU_Op.slt
      case "sltu" | "sltiu"                                        => ALU_Op.sltu
      case "lui"                                                   => ALU_Op.pass_imm
      case _                                                       => ALU_Op.inv
    }
    BitPat(op_type.litValue.U((op_type.getWidth).W))
  }
}
