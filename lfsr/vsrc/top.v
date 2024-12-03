module top(
    input button,
    output [6:0] seg0,seg1 
);
    reg clk;
    reg [7:0] lfsr_out;
    initial begin
        clk = 1'b0;
    end
    always @(posedge button) begin
            clk <= ~clk;
        end
    lfsr lfsr0(clk,lfsr_out);
    bcd7seg b7s (lfsr_out,seg0,seg1);
endmodule


