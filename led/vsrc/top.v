`timescale 1ns/1ps
module top(
  input clk,
  input rst,
  input uart_rx,
  output uart_tx,
  output [15:0] led
);

led led_inst(
    .clk(clk),
    .rst(rst),
    .led(led)
);

uart my_uart(
  .tx(uart_tx),
  .rx(uart_rx)
);

endmodule


module led (
  input clk,
  input rst,
  output reg [15:0] led
);
  reg [31:0] counter;
  always @(posedge clk) begin
    if (rst) begin
      led <= 1; counter <= 0;
    end
    else begin
      if (counter == 0) led <= {led[14:0], led[15]};
      counter <= (counter >= 5000000 ? 32'b0 : counter + 1);
    end
  end
endmodule