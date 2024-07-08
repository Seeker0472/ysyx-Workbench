import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec
import core.Decoder

class DecoderTest extends AnyFlatSpec with ChiselScalatestTester {
  "Decoder" should "set ebreak correctly" in {
    test(new Decoder) { dut =>
      // dut.io.instr.poke("b0000000000000000000000001110011".U)
      // dut.io.out.ebreak.expect(true.B)

      // // 测试指令的 [6:0] 位不等于 0x6B 的情况
      // dut.io.instr.poke("b0000000000000000000000000000000".U)
      // dut.io.out.ebreak.expect(false.B)

      // dut.io.instr.poke("b1111111111111111111111111111111".U)
      // dut.io.out.ebreak.expect(false.B)
    }
  }
}
