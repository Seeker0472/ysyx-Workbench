import chisel3._
import chisel3.util._


class ebreak_handler extends BlackBox with HasBlackBoxResource {
  val io = IO(new Bundle {
    val halt = Input(Bool())
  })
  addResource("/ebreak.v")
}
