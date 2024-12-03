module ps2_keyboard(clk,resetn,ps2_clk,ps2_data,keyboard_out,press_cnt,en);
    input clk,resetn,ps2_clk,ps2_data;
    output reg [7:0] keyboard_out,press_cnt;
    output reg en;
    reg [9:0] buffer;        // ps2_data bits
    reg [3:0] count;  // count ps2_data bits
    reg [2:0] ps2_clk_sync;

    always @(posedge clk) begin
        ps2_clk_sync <=  {ps2_clk_sync[1:0],ps2_clk};
    end

    wire sampling = ps2_clk_sync[2] & ~ps2_clk_sync[1];

    always @(posedge clk) begin
        if (resetn == 0) begin // reset
            count <= 0;
            press_cnt <= 0;
        end
        else begin
            if (sampling) begin
              if (count == 4'd10) begin
                if ((buffer[0] == 0) &&  // start bit
                    (ps2_data)       &&  // stop bit
                    (^buffer[9:1])) begin      // odd  parity
                    $display("receive %x", buffer[8:1]);
                    keyboard_out <= buffer[8:1];
                    if (keyboard_out != 8'hF0) begin
                      press_cnt <= press_cnt;
                      en <= 1;
                    end else begin
                      press_cnt <= press_cnt + 1;
                      en <= 0;
                    end
                    $display("kbo : %x", keyboard_out);
                end
                count <= 0;     // for next
              end else begin
                buffer[count] <= ps2_data;  // store ps2_data
                count <= count + 3'b1;
              end
            end
        end
    end

endmodule
//目前只实现了基础的单个按键的ASCII码显示，且只有字符和数字键的输入，对于组合键的功能还没有实现，
//不过应该也不难，添加一个fifo缓冲一下，记录一下当前按键的状态，再补充一下对这些状态的处理就可以了。