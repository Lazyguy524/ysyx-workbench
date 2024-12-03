module bcd7seg(
    input [3:0] b,
    output reg [6:0] h,
    output reg [6:0] h1
);
    always @(*) begin
        h1 = 7'b0000000;
        h = 7'b0000000;
        if (b[3]==1) begin
            h1 = 7'b1111110;
            case(b[2:0])
            3'b000: h = 7'b1111111;
            3'b001: h = 7'b0001111;
            3'b010: h = 7'b0100000;
            3'b011: h = 7'b0100100;
            3'b100: h = 7'b1001100;
            3'b101: h = 7'b0000110;
            3'b110: h = 7'b0010010;
            3'b111: h = 7'b1001111;
        endcase
        end
        else begin
            h1 = 7'b0000001;
            case(b[2:0])
                3'b000: h = 7'b0000001;
                3'b001: h = 7'b1001111;
                3'b010: h = 7'b0010010;
                3'b011: h = 7'b0000110;
                3'b100: h = 7'b1001100;
                3'b101: h = 7'b0100100;
                3'b110: h = 7'b0100000;
                3'b111: h = 7'b0001111;
            endcase
        end
    end
endmodule

