module bcd7seg(
  input  [3:0] b,
  output reg [6:0] h
);
// detailed implementation ...
  always @(*) begin
    case(b)
      4'b000 : h = 7'b0000000;
      4'b001 : h = 7'b0000010;
      4'b010 : h = 7'b0001000;
      4'b011 : h = 7'b0100000;
      4'b100 : h = 7'b0000000;
      4'b101 : h = 7'b0000000;
      4'b110 : h = 7'b0000000;
      4'b111 : h = 7'b0000000;
    endcase
  end
endmodule