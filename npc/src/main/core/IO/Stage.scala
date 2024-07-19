package core.IO

import chisel3.util._
import chisel3._

object StageConnect {
  def apply[T <: Data](left: DecoupledIO[T], right: DecoupledIO[T],arch: String = "single") = {
    // val arch = "single"
    // 为展示抽象的思想, 此处代码省略了若干细节
    if      (arch == "single")   { right.bits := left.bits }
    else if (arch == "multi")    { right <> left }
    else if (arch == "pipeline") { right <> RegEnable(left, left.fire) }
    else if (arch == "ooo")      { right <> Queue(left, 16) }
  }
}