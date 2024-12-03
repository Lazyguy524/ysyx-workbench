module top(
    input clk,
    input rst,
    input [7:0] x,
    input en,
    output [3:0] ledr,
    output [6:0] seg0 
);
    reg [2:0] y;
    reg z;
    encode83 e83 (x, en, y, z);
    led l (clk, rst, y, z, ledr);
    bcd7seg b7s (y, seg0);
endmodule
