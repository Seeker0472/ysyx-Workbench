module bcd7seg(
  input  [3:0] b,
  output reg [6:0] h
);
// detailed implementation ...
  always @(*) begin
    case(b)
      4'b0000 : h = 7'b0000001;
      4'b0001 : h = 7'b1001111;
      4'b0010 : h = 7'b0010010;
      4'b0011 : h = 7'b0000110;
      4'b0100 : h = 7'b1001100;
      4'b0101 : h = 7'b0100100;
      4'b0110 : h = 7'b0100000;
      4'b0111 : h = 7'b0001111;
      4'b1000 : h = 7'b0000000;
      4'b1001 : h = 7'b0000100;
      default : h = 7'b1111111;
    endcase
  end
endmodule

module encoder(enco,h);
input [7:0] enco;
output reg [6:0] h;
integer i;
reg [3:0] bcd_input;
bcd7seg seg0(bcd_input, h);
always @(enco) begin
    // bcd_input = 4'b1111;
    h=7'b1111111;
    for(i = 0; i < 8; i = i + 1) begin
        if(enco[i] == 1) begin
            bcd_input=i[3:0];
        end
    end
end
endmodule