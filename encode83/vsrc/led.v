module led(
    input clk,
    input rst,
    input [2:0] x,
    input z,
    output reg [3:0] ledr
);
    assign ledr = {z,x};
endmodule

