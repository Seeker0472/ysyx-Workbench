package core

import chisel3._
import chisel3.util._

class raw_core extends Module {
  val io = IO(new Bundle {
    // val inin = Input(Bool())
    // val outout = Output(Bool())
  })
    val ypc = Module(new ypc())
    ypc.io.slave.awvalid:=0.U
    ypc.io.slave.awaddr:=0.U
    ypc.io.slave.awid:=0.U
    ypc.io.slave.awlen:=0.U
    ypc.io.slave.awsize:=0.U
    ypc.io.slave.awburst:=0.U
    ypc.io.slave.wvalid:=0.U
    ypc.io.slave.wdata:=0.U
    ypc.io.slave.wstrb:=0.U
    ypc.io.slave.wlast:=0.U
    ypc.io.slave.bready:=0.U
    ypc.io.slave.arvalid:=0.U
    ypc.io.slave.araddr:=0.U
    ypc.io.slave.arid:=0.U
    ypc.io.slave.arlen:=0.U
    ypc.io.slave.arsize:=0.U
    ypc.io.slave.arburst:=0.U
    ypc.io.slave.rready:=0.U

    ypc.io.master.awready := 1.U
    ypc.io.master.wready  := 1.U
    ypc.io.master.bvalid  := 1.U
    ypc.io.master.bresp   := 0.U
    ypc.io.master.bid     := 0.U
    ypc.io.master.arready := 1.U
    // ypc.io.master.rvalid  := 0.U
    ypc.io.master.rresp   := 0.U
    // ypc.io.master.rdata   := 0.U
    ypc.io.master.rlast   := 0.U //Ignore
    ypc.io.master.rid     := 0.U //Ignore

    ypc.io.interrupt:=0.U
    //应该可以不用管地址通道的valid
    val rvalid = RegInit(false.B)
    val rdata = RegInit(0.U(32.W))
    rvalid := ypc.io.master.arvalid && ~rvalid
    ypc.io.master.rdata   := rdata
    ypc.io.master.rvalid   := rvalid

    val memrw = Module(new DPIC_MEMRW)
    memrw.io.raddr:=ypc.io.master.araddr
    memrw.io.waddr:=ypc.io.master.awaddr
    memrw.io.wdata:=ypc.io.master.wdata
    memrw.io.wmask:=ypc.io.master.wstrb
    memrw.io.read:=ypc.io.master.arvalid
    memrw.io.write:=ypc.io.master.wvalid
    memrw.io.clock:=clock
    rdata:=memrw.io.data
}
class DPIC_MEMRW extends BlackBox with HasBlackBoxInline {
  val io = IO(new Bundle {
    val waddr = Input(UInt(32.W))
    val raddr = Input(UInt(32.W))
    val wdata = Input(UInt(32.W))
    val wmask = Input(UInt(8.W))
    val write = Input(Bool())
    val read = Input(Bool())
    val data = Output(UInt(32.W))
    val clock = Input(Clock())
  })

  setInline(
    "DPIC_MEMRW.v",
    """import "DPI-C" function int pmem_read(int raddr);
      |import "DPI-C" function void pmem_write(int waddr, int wdata, char wmask);
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
      |always @(negedge clock) begin
      |  if (read) begin
      |      // Read operation
      |      data <= pmem_read(raddr);
      |    end
      |  if (write) begin
      |      // Write operation
      |      pmem_write(waddr, wdata, wmask);
      |      data <=32'h0;
      |  end
      |end
      |endmodule
    """.stripMargin
  )
}

