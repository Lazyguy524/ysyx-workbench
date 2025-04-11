module ysyx_exu(
    input wire [31:0]  imm,
    input wire [2:0]   alu_op,
    input wire [31:0]  rs1_data,
    output wire [31:0] rd_data  // 改为wire类型
);
    reg [31:0] result;
    
    always @(*) begin
        case (alu_op)
            3'b000: begin // ADD
                result = rs1_data + imm;
            end
            3'b111: begin // AND
                result = rs1_data & imm;
            end
            3'b110: begin // OR
                result = rs1_data | imm;
            end
            3'b100: begin // XOR
                result = rs1_data ^ imm;
            end
            default: begin
                result = 32'b0;
            end
        endcase
    end
    
    assign rd_data = result;
endmodule

