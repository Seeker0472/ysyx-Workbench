import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec
import core.Decoder
import core.IO._

class DecoderTest extends AnyFlatSpec with ChiselScalatestTester {
  "Decoder" should "set ebreak correctly" in {
    test(new Decoder) { dut =>
      // dut.io.instr.poke("b0000000000000001001000100010111".U)
      // dut.io.out.alu_use_pc.expect(true.B)

      // // 测试指令的 [6:0] 位不等于 0x6B 的情况
      // dut.io.instr.poke("b0000000000000000000000000000000".U)
      // 0000000000000001001000100010111
      // dut.io.out.ebreak.expect(false.B)

      // dut.io.instr.poke("b1111111111111111111111111111111".U)
      // dut.io.out.ebreak.expect(false.B)
    }
  }
}
