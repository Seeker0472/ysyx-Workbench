package core.IO

import chisel3.util._
import chisel3._

object StageConnect {
  def apply[T <: Data](left: DecoupledIO[T], right: DecoupledIO[T],flush: Bool, arch: String = "single"): Unit = {
    arch match {
      case "single" =>
        right.bits  := left.bits
        right.valid := left.valid
        left.ready  := right.ready

      case "multi" =>
        right <> left
        right.valid := left.valid
        left.ready  := right.ready

      case "pipeline" =>
        right.bits <> RegEnable(left.bits, left.valid && right.ready)
        left.ready := right.ready
        right.valid := RegEnable(left.valid , right.ready||flush)//Problem?
        // right.valid := RegNext(left.valid && right.ready)//Problem?

      case "pipeline_state" =>
        right.bits <> RegEnable(left.bits, left.valid && right.ready)
        left.ready := right.ready
        right.valid := left.valid && ~flush
        // right.valid := RegNext(left.valid && right.ready)//Problem?

      // case "ooo" =>
      //   right <> Queue(left, 16)

      case _ =>
        throw new IllegalArgumentException(s"Unknown architecture type: $arch")
    }
  }
}
