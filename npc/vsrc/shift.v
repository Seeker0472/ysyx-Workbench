module shift(clk,h);
input clk;
output reg [6:0] h;
output reg [6:0] k;
reg [7:0] num = 8'b00000001;
bcd7seg seg0(num[3:0], h);
bcd7seg seg1(num[7:4], h);
always @(posedge clk)begin
    num<={num[6:0],num[0]^num[2]^num[3]^num[4]};
end
endmodule