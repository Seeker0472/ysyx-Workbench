package core

import chisel3._
import chisel3.util._

class ebreak_handler extends BlackBox with HasBlackBoxInline {
  val io = IO(new Bundle {
    val halt = Input(Bool())
  })
  setInline(
    "ebreak_handler.v",
    """import "DPI-C" function void call_ebreak();
      |module ebreak_handler(
      |  input halt
      |);
      |always @(*) begin
      |   if (halt) begin
      |      call_ebreak();
      |  end
      | end
      |endmodule
    """.stripMargin
  )
}

// class ebreak_handler extends Module {
//   val io = IO(new Bundle {
//     val halt = Input(Bool())
//   })
// }
