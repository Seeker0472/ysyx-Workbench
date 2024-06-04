module mux43b(add,sub,rev,land,lor,eo,daxiao,eq,op,out);
input [3:0] add;
input [3:0] sub;
input [3:0] rev;
input [3:0] land;
input [3:0] lor;
input [3:0] eo;
input [3:0] qudaxiao;
input [3:0] eq;
input [2:0] op;
output [3:0] out;
MuxKeyWithDefault #(8,3,4) i0(out,op,4'b0000,{
    3'b000,add,
    3'b001,sub,
    3'b010,rev,
    3'b011,land,
    3'b100,lor,
    3'b101,eo,
    3'b110,qudaxiao,
    3'b111,eq
});
endmodule

module add(A,B,OUT);
input [3:0] A;
input [3:0] B;
output [3:0] OUT;
assign OUT=A+B;
endmodule

module alu(A,B,op,OUT);
input [3:0] A;
input [3:0] B;
input [2:0] op;
output [6:0] OUT;

reg [3:0] add_out;
reg [3:0] bcd_input;

add add0(A,B,bcd_input);

bcd7seg seg0(bcd_input, OUT);

// always@(*) begin

// end
endmodule