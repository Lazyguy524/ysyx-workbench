// module top(
//   input clk,
//   input rst,
//   input [1:0]sw,
//   output led
// );

// led my_led(
//   .clk(clk),
//   .rst(rst),
//   .sw(sw),
//   .led(led)
// );
// endmodule

// module led(
//   input clk,
//   input rst,
//   input [1:0]sw,
//   output led
// );
//   always @(posedge clk) begin
//     if (rst) begin led<=1; end
//     else begin
//       assign led = sw[0] ^ sw[1];
//     end
//   end
// endmodule
module top(
  input a,
  input b,
  output f
);

  assign f = a ^ b;

endmodule