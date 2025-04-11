module ysyx_ifu (
    input  wire         clk,
    input  wire         rst,
    output reg  [31:0]  pc
);
    always @(posedge clk or posedge rst) begin  // 高电平复位
        if (rst)
            pc <= 32'h80000000;
        else
            pc <= pc + 4;
    end
endmodule

