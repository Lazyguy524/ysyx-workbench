module alu(
    input [2:0] ALUctr,
    input [3:0] a,
    input [3:0] b,
    output reg [3:0] ALUout,
    output reg less,
    output reg of,zf,cf
);
    reg [3:0] temp;
    reg [3:0] t_no_Cin;
    always @(*) begin
        ALUout = 4'b0000;temp = 4'b0000;less = 1'b0;of = 1'b0;zf = 1'b0;cf = 1'b0;t_no_Cin = 4'b0000;
        casez(ALUctr)
            3'b00z: begin
                t_no_Cin = {4{ALUctr[0]}} ^ b;
                {cf,ALUout} = a + t_no_Cin + {3'b0,ALUctr[0]};
                of = (a[3] == t_no_Cin[3]) && (ALUout[3] != a[3]);
                zf = ~(|ALUout);
            end
            3'b010: begin
                ALUout = ~a;
            end
            3'b011: begin
                ALUout = a & b;
            end
            3'b100: begin
                ALUout = a | b;
            end
            3'b101: begin
                ALUout = a ^ b;
            end
            3'b11z: begin
                t_no_Cin = {4'b1111} ^ b;
                {cf,temp} = a + t_no_Cin + {4'b0001};
                of = (a[3] == t_no_Cin[3]) && (temp[3] != a[3]);
                zf = ~(|temp);
                less = temp[3] ^ of;
                //没有实现到真正的判断功能，后续再改改代码逻辑看看，再判断加减法
                if (zf) begin
                    ALUout = 4'b1111;
                end
                else begin
                    if (less) begin
                        ALUout = 4'b1111;
                    end
                    else begin
                    ALUout = 4'b0000;
                    end
                end
            end
            default: begin
                ALUout = 4'b0000;
            end
        endcase
    end
endmodule


        
