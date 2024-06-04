module mux43b(add,sub,rev,land,lor,eo,qudaxiao,eq,op,out);
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

module add(A,B,OP,OUT);
input [3:0] A;
input [3:0] B;
input OP;
output reg [3:0] OUT;
reg [3:0] temp;
always @(*)begin
    temp={4{OP}}^B+{3'b000,OP};
end
assign OUT=A+temp;
endmodule
// module sub(A,B,OUT);
// input [3:0] A;
// input [3:0] B;
// output [3:0] OUT;
// assign OUT=A-B;
// endmodule

module comp_display(val,outnum,outsin);
input [3:0] val;
output reg [6:0] outnum;
output reg [6:0] outsin;
reg [3:0] num;
bcd7seg seg(num, outnum);
    always @(*) begin
        if (val[3] == 1'b1) begin
            outsin = 7'b1111110;
            num= ~val+4'b001;
        end else begin
            outsin = 7'b1111111;
            num=val;
        end
    end
endmodule
        
module alu(A,B,op,OUT,OUT1);
input [3:0] A;
input [3:0] B;
input [2:0] op;
output [6:0] OUT;
output [6:0] OUT1;

reg [3:0] add_out;
reg [3:0] sub_out;
reg [3:0] bcd_input;

add add0(A,B,0,add_out);
add sub0(A,B,1,sub_out);
mux43b mux(
    .add(add_out),
    .sub(sub_out),
    .rev(~A),
    .land(A&B),
    .lor(A|B),
    .eo(A^B),
    .qudaxiao({3'b000,|sub_out}),
    .eq({3'b000,A==B}),
    .op(op),
    .out(bcd_input)
);
comp_display cmp(bcd_input,OUT,OUT1);

// end
endmodule
