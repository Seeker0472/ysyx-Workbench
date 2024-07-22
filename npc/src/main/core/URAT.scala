package core

import chisel3._
import chisel3.util._
import Constants_Val._

class URAT extends Module{
    val io = IO(Decoupled(new Bundle {
        val data=(UInt(CVAL.DLEN.W))
    }))
    //TODO:DPI_C
}