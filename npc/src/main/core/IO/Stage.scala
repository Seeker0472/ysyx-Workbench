package core.IO

import chisel3.util._
import chisel3._

object StageConnect {
  def apply[T <: Data](left: DecoupledIO[T], right: DecoupledIO[T], arch: String = "single"): Unit = {
    arch match {
      case "single" =>
        right.bits := left.bits
        right.valid := left.valid
        left.ready := right.ready

      case "multi" =>
        right <> left
        right.valid := left.valid
        left.ready := right.ready

      // case "pipeline" =>
      //   right <> RegEnable(left, left.fire)

      // case "ooo" =>
      //   right <> Queue(left, 16)

      case _ =>
        throw new IllegalArgumentException(s"Unknown architecture type: $arch")
    }
  }
}
