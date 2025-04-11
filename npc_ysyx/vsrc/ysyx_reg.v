module ysyx_reg (
    input wire clk,
    input wire rst,          // 复位信号
    input wire [4:0] rs1,
    input wire [4:0] rd,
    input wire [31:0] rd_data,
    input wire write_en,     // 添加写使能信号
    output wire [31:0] rs1_data
);
    reg [31:0] reg_file [0:31];
    integer i;
    
    // 读取rs1数据，确保x0始终为0
    assign rs1_data = (rs1 == 5'b0) ? 32'b0 : reg_file[rs1];
    
    // 写回逻辑 + 复位初始化
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            for (i = 0; i < 32; i = i + 1)
                reg_file[i] <= 32'b0;
        end else if (write_en && rd != 0) begin  // 只有当写使能有效且目标不是x0时才写
            reg_file[rd] <= rd_data;
        end
    end
endmodule
