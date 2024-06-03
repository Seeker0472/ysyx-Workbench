module bcd7seg(
  input  [3:0] b,
  output reg [6:0] h
);
// detailed implementation ...
  always @(*) begin
    case(b)
      4'b0000 : h = 7'b0000000;
      4'b0001 : h = 7'b0000010;
      4'b0010 : h = 7'b0001000;
      4'b0011 : h = 7'b0100000;
      4'b0100 : h = 7'b0000000;
      4'b0101 : h = 7'b0000000;
      4'b0110 : h = 7'b0000000;
      4'b0111 : h = 7'b0000000;
      4'b1000 : h = 7'b0000000;
      4'b1001 : h = 7'b0000000;
      default : y= 7'b0000000;
    endcase
  end
endmodule