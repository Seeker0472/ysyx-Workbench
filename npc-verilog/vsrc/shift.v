module shift(clk,h,k);
input clk;
output reg [6:0] h;
output reg [6:0] k;
reg [7:0] num = 8'b00000001;
bcd7seg seg0(num[3:0],1'b1, h);
bcd7seg seg1(num[7:4],1'b1, k);
always @(posedge clk)begin
    num<={num[0]^num[2]^num[3]^num[4],num[7:1]};
end
endmodule