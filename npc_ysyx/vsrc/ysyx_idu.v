module ysyx_idu(
    input  wire [31:0]  inst,         // 从IFU接收的指令
    
    output wire [31:0]  imm,          // 改为wire类型
    output wire [4:0]   rs1_addr,     // 改为wire类型
    output wire [4:0]   rd_addr,      // 改为wire类型
    output wire [2:0]   alu_op,       // 改为wire类型
    output wire         reg_write_en, // 添加寄存器写使能
    output wire [6:0]   opcode        // 改为wire类型
);
    import "DPI-C" function void npc_trap();
    wire [6:0] op = inst[6:0];
    wire [2:0] func3 = inst[14:12];
    wire is_ebreak = (func3 == 3'b000 && op == 7'b1110011);
    reg trap_triggered;

    initial trap_triggered = 1'b0;

    // I-type立即数生成
    assign imm = {{20{inst[31]}}, inst[31:20]};
    assign rs1_addr = inst[19:15];
    assign alu_op = func3;
    assign rd_addr = inst[11:7];
    assign opcode = op;
    
    always @(*) begin
        if (is_ebreak) begin
            npc_trap();
        end
    end

    // 仅对0010011 opcode(I-type指令)生成写使能
    assign reg_write_en = (op == 7'b0010011);
endmodule

