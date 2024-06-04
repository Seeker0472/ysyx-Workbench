module shift(clk,h);
input clk;
output reg [6:0] h;
reg [7:0] num = 8'b00000001;
bcd7seg seg0(num, h);
always @(posedge clk)begin
    num<={num[6:0],num[0]^num[2]^num[3]^num[4]};
end
endmodule