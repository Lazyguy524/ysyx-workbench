module top(
  input  wire  clk,
  input  wire  rst,
  input  wire  [31:0]  inst,
  output wire  [31:0]  pc
);
  wire [4:0]   rs1_addr, rd_addr;
  wire [31:0]  imm;
  wire [2:0]   alu_op;
  wire [31:0]  rs1_data, rd_data;
  wire         reg_write_en;  // 添加寄存器写使能信号
  
  ysyx_ifu u_ifu(.clk(clk), .rst(rst), .pc(pc));
  
  ysyx_idu u_idu(
    .inst(inst), 
    .imm(imm), 
    .rs1_addr(rs1_addr), 
    .rd_addr(rd_addr), 
    .alu_op(alu_op),
    .reg_write_en(reg_write_en),  // 连接写使能信号
    .opcode()
  );
  
  ysyx_reg u_reg(
    .clk(clk), 
    .rst(rst), 
    .rs1(rs1_addr), 
    .rd(rd_addr), 
    .rd_data(rd_data), 
    .rs1_data(rs1_data),
    .write_en(reg_write_en)  // 连接写使能信号
  );
  
  ysyx_exu u_exu(
    .imm(imm), 
    .alu_op(alu_op), 
    .rs1_data(rs1_data), 
    .rd_data(rd_data)
  );
  
endmodule
