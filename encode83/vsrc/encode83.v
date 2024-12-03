module encode83(x,en,y,z);
    input [7:0] x;
    input en;
    output reg [2:0] y;
    output reg z;
    integer i;
    always @(x or en) begin
        y = 3'b000;
        z = 0;
        if (en) begin
            for (i = 0; i <= 7 ; i = i+1) begin
                if(x[i] == 1) begin
                    y = i[2:0];
                    z = 1;
                end                
            end
        end
    end
endmodule
