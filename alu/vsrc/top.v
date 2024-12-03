module top(
    input clk,
    input rst,
    input [3:0] a,
    input [3:0] b,
    input [2:0] ALUctr,
    output [7:0] ledr,
    output [6:0] seg0,seg1 
);
    //reg [2:0] y;
    //reg z;
    //encode83 e83 (x, en, y, z);
    //led l (clk, rst, y, z, ledr);
    //bcd7seg b7s (y, seg0);
    alu a1(ALUctr,a,b,ledr[3:0],ledr[4],ledr[5],ledr[6],ledr[7]);
    bcd7seg b7s (ledr[3:0],seg0,seg1);
endmodule
