module lfsr(
    input clk,
    //input rst_n,
    output reg [7:0] lfsr_out 
);
    // reg [7:0] lfsr_reg;
    // reg x8;
    // initial begin
    //     lfsr_reg = 8'b00000001;
    // end
    // always @(posedge clk) begin
    //     x8 <= lfsr_reg[0] ^ lfsr_reg[2] ^ lfsr_reg[3] ^ lfsr_reg[4];
    //     lfsr_reg <= {x8,lfsr_reg[7:1]};
    //     lfsr_out <= lfsr_reg;
    // end
    
    initial begin
        lfsr_out = 8'b00000001;
    end
    always @(posedge clk) begin
        lfsr_out <= {lfsr_out[0] ^ lfsr_out[2] ^ lfsr_out[3] ^ lfsr_out[4],lfsr_out[7:1]};
    end
endmodule


        
