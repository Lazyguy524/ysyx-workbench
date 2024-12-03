module top(
    input clk,
    input rst,
    input ps2_clk,
    input ps2_data,
    input uart_rx,
    output uart_tx,
    //input en,
    output [3:0] ledr,
    output [6:0] seg0,seg1,seg2,seg3,seg4,seg5
);
    // reg [2:0] y;
    // reg z;
    // encode83 e83 (x, en, y, z);
    // led l (clk, rst, y, z, ledr);
    // bcd7seg b7s (y, seg0);
    reg [7:0] k_key;
    reg [7:0] a_key;
    reg [7:0] cnt_key;
    reg en;
    ps2_keyboard my_keyboard(
    .clk(clk),
    .resetn(~rst),
    .ps2_clk(ps2_clk),
    .ps2_data(ps2_data),
    .keyboard_out(k_key),
    .press_cnt(cnt_key),
    .en(en)
);

key2ascii k2a(k_key,a_key);
bcd7seg b7s(k_key,en,seg0,seg1);
bcd7seg b7s2(a_key,en,seg2,seg3);
bcd7seg b7s3(cnt_key,1,seg4,seg5);

uart my_uart(
    .rx(uart_rx),
    .tx(uart_tx)
);

endmodule
