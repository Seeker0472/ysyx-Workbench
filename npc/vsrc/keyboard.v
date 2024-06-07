module keyboard(clk,rest,ps2clk,ps2dat,keycode0,keycode1,ascii0,ascii1,cnt0,cnt1);
input reg ps2clk,ps2dat;
input reg clk,rest;
output reg [6:0] keycode0;
output reg [6:0] keycode1;
output reg [6:0] ascii0;
output reg [6:0] ascii1;
output reg [6:0] cnt0;
output reg [6:0] cnt1;

reg key_up=1'b0;
reg display_enable=1'b0;
reg [7:0] data;
reg [7:0] data_current;
reg [7:0] cnt=8'b00000000;
reg ready,nextdata_n,overflow;
ps2_keyboard keyb(
    .clk(clk),
    .clrn(rest),
    .ps2_clk(ps2clk),
    .ps2_data(ps2dat),
    .data(data),
    .ready(ready),
    .nextdata_n(nextdata_n),
    .overflow(overflow)
);
always @(negedge clk)begin
    if(nextdata_n==1'b1)begin//nextdata_n保持一个周期
        nextdata_n=1'b0;
    end else if(ready==1'b1)begin//准备接收数据
        if(key_up==1'b1)begin//如果上一个数据是按键抬起
            key_up=1'b0;
            cnt+=8'b00000001;
            display_enable=1'b0;
        end else if(data==8'b11110000)begin//如果是按键抬起
            key_up=1'b1;
            data_current=8'b00000000;
        end else begin//正常数据
            display_enable=1'b1;
            data_current=data;
        end
        nextdata_n=1'b1;
    end
end
display dis(data_current,display_enable,keycode0,keycode1,ascii0,ascii1);
bcd7seg bc5(cnt[3:0],1'b1,cnt0);
bcd7seg bc6(cnt[7:4],1'b1,cnt1);
endmodule

module display(data,enable,keycode0,keycode1,ascii0,ascii1);
input reg [7:0] data;
input enable;
output reg [6:0] keycode0;
output reg [6:0] keycode1;
output reg [6:0] ascii0;
output reg [6:0] ascii1;
reg [7:0] val;
always @(*) begin
        case (data)
            8'h1C	: val=	8'h41	;
            8'h32	: val=	8'h42	;
            8'h21	: val=	8'h43	;
            8'h23	: val=	8'h44	;
            8'h24	: val=	8'h45	;
            8'h2B	: val=	8'h46	;
            8'h34	: val=	8'h47	;
            8'h33	: val=	8'h48	;
            8'h43	: val=	8'h49	;
            8'h3B	: val=	8'h4A	;
            8'h42	: val=	8'h4B	;
            8'h4B	: val=	8'h4C	;
            8'h3A	: val=	8'h4D	;
            8'h31	: val=	8'h4E	;
            8'h44	: val=	8'h4F	;
            8'h4D	: val=	8'h50	;
            8'h15	: val=	8'h51	;
            8'h2D	: val=	8'h52	;
            8'h1B	: val=	8'h53	;
            8'h2C	: val=	8'h54	;
            8'h3C	: val=	8'h55	;
            8'h2A	: val=	8'h56	;
            8'h1D	: val=	8'h57	;
            8'h22	: val=	8'h58	;
            8'h35	: val=	8'h59	;
            8'h1A	: val=	8'h5A	;
            default : val=  8'hFF   ;
        endcase
    end
bcd7seg bc1(data[3:0],enable,keycode0);
bcd7seg bc2(data[7:4],enable,keycode1);
bcd7seg bc3(val[3:0],enable,ascii0);
bcd7seg bc4(val[7:4],enable,ascii1);
endmodule