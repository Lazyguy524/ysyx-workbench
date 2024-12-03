module bcd7seg(
    input [2:0] b,
    output reg [6:0] h
);
    always @(b) begin
        case(b)
            3'b000: h = 7'b1111110;
            3'b001: h = 7'b1001111;
            3'b010: h = 7'b0010011;
            3'b011: h = 7'b0000110;
            3'b100: h = 7'b1001100;
            3'b101: h = 7'b0100100;
            3'b110: h = 7'b0100000;
            3'b111: h = 7'b0001111;
        endcase
    end
endmodule