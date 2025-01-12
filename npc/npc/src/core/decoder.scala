package core

import chisel3._
import chisel3.util._
import Constants_Val.CVAL
import core.IO._

import chisel3.util.BitPat
import chisel3.util.experimental.decode.DecodeField
import chisel3.util.experimental.decode._
import org.chipsalliance.rvdecoderdb

case class Insn(val inst: rvdecoderdb.Instruction) extends DecodePattern {
  override def bitPat: BitPat = BitPat("b" + inst.encoding.toString())
}

object Inst_Type_Enum extends ChiselEnum {
  val R_Type, I_Type, S_Type, B_Type, U_Type, J_Type, ERROR = Value
}

object ImmTypeEnum extends ChiselEnum {
  val immNone, immI, immS, immB, immU, immJ, immShamtD, immShamtW = Value
}

object Insn {
  implicit class addMethodsToInsn(i: Insn) {
    def hasArg(arg: String) = i.inst.args.map(_.name).contains(arg)

    lazy val opcode: BitPat = i.bitPat(6, 0)
    /*     lazy val Inst_Type: Inst_Type_Enum.Type = {
      if (rvdecoderdb.Utils.isR(i.inst))
      Inst_Type_Enum.R_Type
    else
      Inst_Type_Enum.R_Type
    } */
  }
}

class Decoder extends Module {
  val io = IO(new Bundle {
    val in             = Flipped(Decoupled(new IFUO))
    val lsu_w_addr     = Input(UInt(CVAL.REG_ADDR_LEN.W))
    val exu_w_addr     = Input(UInt(CVAL.REG_ADDR_LEN.W))
    val decoder_pc     = Decoupled(UInt(CVAL.DLEN.W))
    val flush_pipeline = Input(Bool())
    val reg1           = (new RegReadIO)
    val reg2           = (new RegReadIO)
    val csr            = (new CSRReadIO)
    val out            = Decoupled(new DecoderO)
    val forwarding     = Flipped(Decoupled(UInt(CVAL.DLEN.W)))
  })
  io.forwarding.ready := true.B

  //sig pass to hazard_unit
  io.decoder_pc.bits  := io.in.bits.pc
  io.decoder_pc.valid := io.in.valid

  //pass_through
  io.out.bits.pc := io.in.bits.pc

  // val Patterns = decodePatterns.Patterns
  val instTable  = rvdecoderdb.fromFile.instructions(os.pwd / "riscv-opcodes")
  val targetSets = Set("rv_i", "rv_m", "rv64_i", "rv64_m", "rv_zicsr", "rv_system")
  val instList = instTable
    .filter(instr => targetSets.contains(instr.instructionSet.name))
    .filter(_.pseudoFrom.isEmpty)
    .map(Insn(_))
    .toSeq

  //for debugs
  instList.foreach { insn =>
    // println(s"${insn.toString()}")
    // println(s"${insn.inst.args.contains("rd")}")
    val isEmpty    = insn.inst.args.isEmpty
    val containsRd = if (isEmpty) false else insn.inst.args.map(_.name).contains("rs1")
    println(s"args: ${insn.inst.args}, Is empty: $isEmpty, Contains 'rs1': $containsRd")
    println(s"args element types: ${insn.inst.args.map(_.getClass).mkString(", ")}")

  }

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

  val immJ       = Cat(Fill(11, imm_J_Raw(20)), imm_J_Raw)
  val imm_shamtd = Cat(Fill(26, 0.U), io.in.bits.instr(25, 20))

  // val opcode = io.in.bits.instr(6, 0)
  val rs1   = io.in.bits.instr(19, 15)
  val rs2   = io.in.bits.instr(24, 20)
  val rd    = io.in.bits.instr(11, 7)
  val func3 = io.in.bits.instr(14, 12)

  val decodedResults =
    new DecodeTable(
      // Patterns,
      instList,
      Seq(
        Use_rs1,
        Use_rs2,
        ImmType,
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
  val Typeimm = decodedResults(ImmType)

  val imm = MuxLookup(Typeimm, 0.U)(
    Seq(
      ImmTypeEnum.immI -> immI,
      ImmTypeEnum.immS -> immS,
      ImmTypeEnum.immB -> immB,
      ImmTypeEnum.immU -> immU,
      ImmTypeEnum.immJ -> immJ,
      ImmTypeEnum.immShamtD -> imm_shamtd
      // ImmTypeEnum.immShamtW -> imm_shamtw
    )
  )

  //data
  // reg conflict whith EXU/(LS+WB)
  val conflict_rs1 =
    (((io.lsu_w_addr === rs1) && rs1 =/= 0.U) || ((io.exu_w_addr === rs1) && rs1 =/= 0.U && ~io.forwarding.valid)) && decodedResults(
      Use_rs1
    )
  val conflict_rs2 =
    (((io.lsu_w_addr === rs2) && rs2 =/= 0.U) || ((io.exu_w_addr === rs2) && rs2 =/= 0.U && ~io.forwarding.valid)) && decodedResults(
      Use_rs2
    )
  val conflict = conflict_rs1 || conflict_rs2

  val use_forwarding_1 = (io.exu_w_addr === rs1 && rs1 =/= 0.U) && io.forwarding.valid
  val use_forwarding_2 = (io.exu_w_addr === rs2 && rs2 =/= 0.U) && io.forwarding.valid

  //fetch data in decode stage to inc freq
  io.reg1.addr         := rs1
  io.reg2.addr         := rs2
  io.csr.addr          := imm
  io.out.bits.src1     := Mux(use_forwarding_1, io.forwarding.bits, io.reg1.data)
  io.out.bits.src2     := Mux(use_forwarding_2, io.forwarding.bits, io.reg2.data)
  io.out.bits.csr_data := io.csr.data

  io.out.bits.rd    := rd
  io.out.bits.imm   := imm
  io.out.bits.func3 := func3

  //control signals
  //alu_select
  io.out.bits.alu_use_Imm_2 := decodedResults(Use_IMM_2)
  io.out.bits.alu_use_pc    := decodedResults(Use_PC_1)
  io.out.bits.alu_op_type   := decodedResults(ALUOp_Gen)

  io.out.bits.ebreak       := decodedResults(Is_Ebreak)
  io.out.bits.flush_icache := decodedResults(Is_fenceI)

  //mem_sig for lsu
  io.out.bits.mem_read_enable  := decodedResults(Read_En)
  io.out.bits.mem_write_enable := decodedResults(Write_En)

  //csrs
  io.out.bits.csrrw        := decodedResults(CSRRW)
  io.out.bits.csr_alu_type := decodedResults(CSRR_ALU_Type)

  //wbu_signals
  io.out.bits.is_branch        := decodedResults(Is_Branch)
  io.out.bits.pc_jump          := decodedResults(Is_Jump)
  io.out.bits.reg_write_enable := decodedResults(R_Write_Enable)
  io.out.bits.ecall            := decodedResults(Is_Ecall)
  io.out.bits.mret             := decodedResults(Is_Mret)

  //ready/valid sig
  io.in.ready  := io.out.ready && ~conflict
  io.out.valid := io.in.valid && ~io.flush_pipeline && ~conflict

  //Trace
  val trace_decoder = Module(new TRACE_DECODER)
  trace_decoder.io.clock := clock
  trace_decoder.io.mem_R := decodedResults(Read_En) //MEM_Read
  trace_decoder.io.mem_W := decodedResults(Write_En) //MEM_Write
  trace_decoder.io.calc  := decodedResults(ALUOp_Gen) =/= ALU_Op.inv //calc instr
  trace_decoder.io.csr   := decodedResults(CSRRW) //scrrw/scrrs/mert/ecall
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

object Use_rs1 extends BoolDecodeField[Insn] {
  def name: String = "Use_rs1"
  def genTable(inst: Insn) = {
    if (inst.inst.args.map(_.name).contains("rs1")) y else n
  }
}
object Use_rs2 extends BoolDecodeField[Insn] {
  def name: String = "Use_rs2"
  def genTable(inst: Insn) = {
    if (inst.inst.args.map(_.name).contains("rs2")) y else n
  }
}

object ImmType extends DecodeField[Insn, ImmTypeEnum.Type] {
  override def name = "imm_type"

  override def chiselType = ImmTypeEnum()

  override def genTable(i: Insn): BitPat = {
    val immType = i.inst.args
      .map(_.name match {
        case "imm12"                 => ImmTypeEnum.immI
        case "imm12hi" | "imm12lo"   => ImmTypeEnum.immS
        case "bimm12hi" | "bimm12lo" => ImmTypeEnum.immB
        case "imm20"                 => ImmTypeEnum.immU
        case "jimm20"                => ImmTypeEnum.immJ
        case "shamtd"                => ImmTypeEnum.immShamtD
        case "shamtw"                => ImmTypeEnum.immShamtW
        case "csr"                   => ImmTypeEnum.immI
        case _                       => ImmTypeEnum.immNone
      })
      .filterNot(_ == ImmTypeEnum.immNone)
      .headOption // different ImmType will not appear                   => ImmTypeEnum.immI in the Seq
      .getOrElse(ImmTypeEnum.immNone)

    // TODO: BitPat will accept ChiselEnum after #2327 has been merged
    BitPat(immType.litValue.U((immType.getWidth).W))
  }

}

//src2是否选择Imm--TODO same!
//typeISB/auipc/lui
object Use_IMM_2 extends BoolDecodeField[Insn] {
  def name: String = "Use_IMM"
  def genTable(inst: Insn) = {
    /*     if (
      rvdecoderdb.Utils.isI(inst.inst) || rvdecoderdb.Utils
        .isS(inst.inst) || rvdecoderdb.Utils.isB(inst.inst) || rvdecoderdb.Utils.isJ(inst.inst) || inst.inst.name
        .matches("auipc") || inst.inst.name.matches("lui")
    )
      y
    else n */
    if (
      (!inst.inst.args.map(_.name).contains("rs2")) || (rvdecoderdb.Utils.isB(inst.inst)) || (rvdecoderdb.Utils
        .isS(inst.inst))
    ) y
    else n
    // B-Type rs1,rs2,imm -> use imm!
  }
}

//src1是否选择PC -- J-Type & B-Type
//typeJB/auipc
object Use_PC_1 extends BoolDecodeField[Insn] {
  def name: String = "Use_PC_1"
  def genTable(inst: Insn) = {
    if (rvdecoderdb.Utils.isJ(inst.inst) || rvdecoderdb.Utils.isB(inst.inst) || inst.inst.name.matches("auipc")) //auipc
      y
    else n
  }
}

//是否是无条件跳转
//typeJ/opcode==1100111
object Is_Jump extends BoolDecodeField[Insn] {
  def name: String = "Is_Jump"
  def genTable(inst: Insn) = {
    if (rvdecoderdb.Utils.isJ(inst.inst) || inst.opcode.rawString.matches("1100111"))
      y
    else n
  }

}

//Reg_write_Enable
//!(NOT)typeS/B
object R_Write_Enable extends BoolDecodeField[Insn] {
  def name: String = "Reg_W_En"
  def genTable(inst: Insn) = {
    //ecall,ebreak有效因为rd为0
    if (rvdecoderdb.Utils.isS(inst.inst) || rvdecoderdb.Utils.isB(inst.inst)) //！！注意这里是if() n else y!!!!!!!!
      n
    else y
  }
}

//ebreak
object Is_Ebreak extends BoolDecodeField[Insn] {
  def name: String = "Is_Ebreak"
  def genTable(inst: Insn) = {
    // if(op.opcode===BitPat("b1110011")&&op.func3===BitPat("b000")&&op.func7===BitPat("b0000001"))
    if (inst.inst.name == "ebreak")
      y
    else n
  }
}

//mem
//
object Read_En extends BoolDecodeField[Insn] {
  def name: String = "Read_En"
  def genTable(inst: Insn) = {
    if (inst.opcode.rawString.matches("0000011"))
      y
    else n
  }
}

//mem
object Write_En extends BoolDecodeField[Insn] {
  def name: String = "Write_En"
  def genTable(inst: Insn) = {
    if (inst.opcode.rawString.matches("0100011"))
      y
    else n
  }
}

//fencei
object Is_fenceI extends BoolDecodeField[Insn] {
  def name: String = "Is_fencei"
  def genTable(inst: Insn) = {
    if (inst.inst.name == "fence.i")
      y
    else n
  }
}

//Branch
//typeB
object Is_Branch extends BoolDecodeField[Insn] {
  def name: String = "Is_Branch"
  def genTable(inst: Insn) = {
    if (rvdecoderdb.Utils.isB(inst.inst))
      y
    else n
  }
}

//csrs
//由于这部分指令都需要读取/写入csr存储器，所以就rw放一起了，同时这个信号也作用于Mux来选择写入存储器的数据
object CSRRW extends BoolDecodeField[Insn] {
  def name: String = "CSRRW"
  def genTable(inst: Insn) = {

    //NO
    if (
      inst.inst.name.matches("csrrw") || inst.inst.name
        .matches("csrrs") || inst.inst.name.matches("ecall") || inst.inst.name.matches("mret")
    )
      y
    else n
  }
}

object Is_Ecall extends BoolDecodeField[Insn] {
  def name: String = "Is_Ecall"
  def genTable(inst: Insn) = {
    if (inst.inst.name.matches("ecall"))
      y
    else n
  }
}

object Is_Mret extends BoolDecodeField[Insn] {
  def name: String = "Is_Mret"
  def genTable(inst: Insn) = {
    if (inst.inst.name.matches("mret"))
      y
    else n
  }
}

//目前csr指令的alu是独立于其他的alu
object CSRR_ALU_Type extends DecodeField[Insn, CSRALU_Type.Type] {
  def name: String = "CSRR_ALU_Type"
  override def chiselType = CSRALU_Type()
  def genTable(inst: Insn) = {
    val btype = inst.inst.name match {
      case "csrrs" => CSRALU_Type.or
      case _       => CSRALU_Type.passreg
    }
    BitPat(btype.litValue.U((btype.getWidth).W))
  }
}

//alu的运算类型
object ALUOp_Gen extends DecodeField[Insn, ALU_Op.Type] {
  def name: String = "ALUOp_Gen"
  override def chiselType = ALU_Op()
  def genTable(inst: Insn): BitPat = {
    val op_type = inst.inst.name match {
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
