object Elaborate extends App {
  val firtoolOptions = Array(
    "--lowering-options=" + List(
      // make yosys happy
      // see https://github.com/llvm/circt/blob/main/docs/VerilogGeneration.md
      "disallowLocalVariables", // If true, do not emit SystemVerilog locally scoped "automatic" or logic declarations - emit top level wire and reg's instead.
      "disallowPackedArrays", //If true, eliminate packed arrays for tools that don't support them (e.g. Yosys).
      "locationInfoStyle=wrapInAtSquareBracket" //wrapInAtSquareBracket: // @[perf/regress/AndNot.fir:3:10, :7:{10,17}]
    ).reduce(_ + "," + _)
  )
  circt.stage.ChiselStage.emitSystemVerilogFile(new core.ypc(), args, firtoolOptions)
}
object ElaborateRaw extends App {
  val firtoolOptions = Array(
    "--lowering-options=" + List(
      // make yosys happy
      // see https://github.com/llvm/circt/blob/main/docs/VerilogGeneration.md
      "disallowLocalVariables", // If true, do not emit SystemVerilog locally scoped "automatic" or logic declarations - emit top level wire and reg's instead.
      "disallowPackedArrays", //If true, eliminate packed arrays for tools that don't support them (e.g. Yosys).
      "locationInfoStyle=wrapInAtSquareBracket" //wrapInAtSquareBracket: // @[perf/regress/AndNot.fir:3:10, :7:{10,17}]
    ).reduce(_ + "," + _)
  )
  circt.stage.ChiselStage.emitSystemVerilogFile(new core.raw_core(), args, firtoolOptions)
}
