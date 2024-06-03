// module example(
//   input clk,
//   input rst,
//   output reg [15:0] led
// );
//   reg [31:0] count;
//   always @(posedge clk) begin
//     if (rst) begin led <= 1; count <= 0; end
//     else begin
//       if (count == 0) led <= {led[14:0], led[15]};
//       count <= (count >= 5 ? 32'b0 : count + 1);
//     end
//   end
// endmodule

module MuxKeyInternal #(NR_KEY = 2, KEY_LEN = 1, DATA_LEN = 1, HAS_DEFAULT = 0) (
  output reg [DATA_LEN-1:0] out,
  input [KEY_LEN-1:0] key,
  input [DATA_LEN-1:0] default_out,
  input [NR_KEY*(KEY_LEN + DATA_LEN)-1:0] lut
);

  localparam PAIR_LEN = KEY_LEN + DATA_LEN;
  wire [PAIR_LEN-1:0] pair_list [NR_KEY-1:0];
  wire [KEY_LEN-1:0] key_list [NR_KEY-1:0];
  wire [DATA_LEN-1:0] data_list [NR_KEY-1:0];

  generate
    for (genvar n = 0; n < NR_KEY; n = n + 1) begin
      assign pair_list[n] = lut[PAIR_LEN*(n+1)-1 : PAIR_LEN*n];
      assign data_list[n] = pair_list[n][DATA_LEN-1:0];
      assign key_list[n]  = pair_list[n][PAIR_LEN-1:DATA_LEN];
    end
  endgenerate

  reg [DATA_LEN-1 : 0] lut_out;
  reg hit;
  integer i;
  always @(*) begin
    lut_out = 0;
    hit = 0;
    for (i = 0; i < NR_KEY; i = i + 1) begin
      lut_out = lut_out | ({DATA_LEN{key == key_list[i]}} & data_list[i]);
      hit = hit | (key == key_list[i]);
    end
    if (!HAS_DEFAULT) out = lut_out;
    else out = (hit ? lut_out : default_out);
  end

endmodule
// 键值选择
module MuxKey #(NR_KEY = 2, KEY_LEN = 1, DATA_LEN = 1) (
  output [DATA_LEN-1:0] out,
  input [KEY_LEN-1:0] key,
  input [NR_KEY*(KEY_LEN + DATA_LEN)-1:0] lut
);
  MuxKeyInternal #(NR_KEY, KEY_LEN, DATA_LEN, 0) i0 (out, key, {DATA_LEN{1'b0}}, lut);
endmodule
//提供一个默认的键值
module MuxKeyWithDefault #(NR_KEY = 2, KEY_LEN = 1, DATA_LEN = 1) (
  output [DATA_LEN-1:0] out,
  input [KEY_LEN-1:0] key,
  input [DATA_LEN-1:0] default_out,
  input [NR_KEY*(KEY_LEN + DATA_LEN)-1:0] lut
);
  MuxKeyInternal #(NR_KEY, KEY_LEN, DATA_LEN, 1) i0 (out, key, default_out, lut);
endmodule
//值对的数量 NR_KEY，键值的位宽 KEY_LEN 以及数据的位宽 DATA_LEN
// start

module mux21e(a,b,s,y);
  input   a,b,s;
  output  y;
  MuxKey #(2, 1, 1) i0 (y, s, {
    1'b0, a,
    1'b1, b
  });
endmodule

module mux41b(a,s,y);
  input  [3:0] a;
  input  [1:0] s;
  output y;
  MuxKeyWithDefault #(4, 2, 1) i0 (y, s, 1'b0, {
    2'b00, a[0],
    2'b01, a[1],
    2'b10, a[2],
    2'b11, a[3]
  });
endmodule


module example(x0,x1,x2,x3)
  input [1:0] y;
  input [1:0] x0;
  input [1:0] x1;
  input [1:0] x2;
  input [1:0] x3;
  output [1:0] f;
  MuxKeyWithDefault #(4,2,2) i0 (f,y,{
    2'b00, x0,
    2'b01, x1,
    2'b10, x2,
    2'b11, x3,
  })

endmodule