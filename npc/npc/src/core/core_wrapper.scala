package core

import chisel3._
import chisel3.util._

class raw_core extends Module {

  val ypc = Module(new ypc())

  //states
  val s_r_idle :: s_r_fetching :: s_r_fin :: Nil = Enum(3)
  val s_w_idle :: s_w_fin :: Nil                 = Enum(2)

  val rstate = RegInit(s_r_idle)
  val wstate = RegInit(s_w_idle)
  val rlen   = Reg(UInt(8.W))
  val rdata  = RegInit(0.U(32.W))
  val raddr  = RegInit(0.U(32.W))
  val waddr  = RegInit(0.U(32.W))
  val memrw = Module(new DPIC_MEMRW)

  //split the write_state and read_state to support write and read at same cycle!
  //states
  rstate := MuxLookup(rstate, s_r_idle)(
    Seq(
      s_r_idle -> Mux(ypc.io.master.arvalid, s_r_fetching, s_r_idle),
      s_r_fetching -> Mux(rlen === 0.U, s_r_fin, s_r_fetching),
      s_r_fin -> Mux(ypc.io.master.rready, s_r_idle, s_r_fin)
    )
  )
  wstate := MuxLookup(wstate, s_w_idle)(
    Seq(
      s_w_idle -> Mux(ypc.io.master.awvalid, s_w_fin, s_w_idle),
      s_w_fin -> Mux(ypc.io.master.bready, s_w_idle, s_w_fin)
    )
  )

  when(rstate === s_r_idle && ypc.io.master.arvalid) {
    rlen  := ypc.io.master.arlen
    raddr := ypc.io.master.araddr
  }

  when(wstate === s_w_idle && ypc.io.master.awvalid) {
    waddr := ypc.io.master.awaddr
  }

  when(rstate === s_r_fetching && ypc.io.master.rready) {
    rlen  := rlen - 1.U
    raddr := raddr + 4.U
  }

  //axi_signals
  //read
  ypc.io.master.rvalid  := RegNext(rstate === s_r_fetching)
  ypc.io.master.rlast   := RegNext(rlen === 0.U && rstate === s_r_fetching)
  ypc.io.master.arready := rstate === s_w_idle
  ypc.io.master.rresp   := 0.U
  ypc.io.master.rid     := 0.U //TODO!!!
  ypc.io.master.rdata   := memrw.io.data

  //write
  ypc.io.master.awready := wstate === s_r_idle
  ypc.io.master.wready  := 1.U
  ypc.io.master.bvalid  := 1.U
  ypc.io.master.bresp   := 0.U
  ypc.io.master.bid     := 0.U

  ypc.io.interrupt := 0.U
  //应该可以不用管地址通道的valid

  //slave_signals
  ypc.io.slave.awvalid := 0.U
  ypc.io.slave.awaddr  := 0.U
  ypc.io.slave.awid    := 0.U
  ypc.io.slave.awlen   := 0.U
  ypc.io.slave.awsize  := 0.U
  ypc.io.slave.awburst := 0.U
  ypc.io.slave.wvalid  := 0.U
  ypc.io.slave.wdata   := 0.U
  ypc.io.slave.wstrb   := 0.U
  ypc.io.slave.wlast   := 0.U
  ypc.io.slave.bready  := 0.U
  ypc.io.slave.arvalid := 0.U
  ypc.io.slave.araddr  := 0.U
  ypc.io.slave.arid    := 0.U
  ypc.io.slave.arlen   := 0.U
  ypc.io.slave.arsize  := 0.U
  ypc.io.slave.arburst := 0.U
  ypc.io.slave.rready  := 0.U

  memrw.io.raddr := Mux(ypc.io.master.arvalid, ypc.io.master.araddr, raddr)
  memrw.io.waddr := Mux(ypc.io.master.awvalid, ypc.io.master.awaddr, waddr)
  memrw.io.wdata := ypc.io.master.wdata
  memrw.io.wmask := ypc.io.master.wstrb
  memrw.io.read  := rstate === s_r_fetching
  memrw.io.write := ypc.io.master.wvalid
  memrw.io.clock := clock
}
class DPIC_MEMRW extends BlackBox with HasBlackBoxInline {
  val io = IO(new Bundle {
    val waddr = Input(UInt(32.W))
    val raddr = Input(UInt(32.W))
    val wdata = Input(UInt(32.W))
    val wmask = Input(UInt(8.W))
    val write = Input(Bool())
    val read  = Input(Bool())
    val data  = Output(UInt(32.W))
    val clock = Input(Clock())
  })

  setInline(
    "DPIC_MEMRW.v",
    """import "DPI-C" function int pmem_read(int raddr);
      |import "DPI-C" function void pmem_write(int waddr, int wdata, byte wmask);
      |
      |module DPIC_MEMRW(
      |  input [31:0] raddr,
      |  input [31:0] waddr,
      |  input [31:0] wdata,
      |  input [7:0] wmask,
      |  input write,
      |  input read,
      |  output reg [31:0] data,
      |  input clock
      |);
      |always @(posedge clock) begin
      |  if (read) begin
      |      // Read operation
      |      data <= pmem_read(raddr);
      |    end
      |  if (write) begin
      |      // Write operation
      |      pmem_write(waddr, wdata, wmask);
      |  end
      |end
      |endmodule
    """.stripMargin
  )
}
