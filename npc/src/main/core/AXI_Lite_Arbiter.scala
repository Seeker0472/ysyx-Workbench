// package core

// import chisel3._
// import chisel3.util._
// import Constants_Val._
// import core.IO._

// class AXI_Lite_Arbiter extends Module{
//     val io = IO(new Bundle{
//         val c1=(new AXIIO)
//         val c2=(new AXIIO)
//     })
//     val s_idle ::s_c1_busy::s_c2_busy::s_c1_valid::s_c2_valid ::Nil = Enum(5)
//     val state = RegInit(s_idle)
//     val axi = Module(new AXI)

//     state:=MuxLookup(state,s_idle)(
//         List(
//             s_idle -> Mux(io.c2.RA.valid,s_c2_busy,Mux(io.c1.RA.valid,s_c1_busy,s_idle)),
//             s_c1_busy->Mux(io.c1.RD.valid,s_c1_valid),
//             s_c
//         )
//     )
    
// }
