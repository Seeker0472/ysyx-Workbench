package core
import chisel3._
import chisel3.util._


class ebreak_handler extends BlackBox with HasBlackBoxInline {
  val io = IO(new Bundle {
    val halt = Input(Bool())
  })
    setInline("ebreak_handler.v",
    """module ebreak_handler(
      |);
      |always @(*) begin
      |   if (halt) begin
      |      call_ebreak();
      |  end
      | end
      |endmodule
    """.stripMargin)

}
