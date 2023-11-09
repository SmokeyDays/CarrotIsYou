module vram_decode (input [3:0] num,
                    output reg [11:0] data);
// y is vertical, x is horizonal
always @(*) begin
  data              = 12'h000;
  case (num)
    4'b0000: begin
      data = 12'h000; // I, cyan
    end
    4'b0001: begin
      data = 12'hfff; // T, purple
    end
    4'b0010: begin
      data = 12'h333; // O, yellow
    end
    4'b0011: begin
      data = 12'h999; // J, blue
    end
    4'b0100: begin
      data = 12'hf11; // L, orange
    end
    4'b0101: begin
      data = 12'hfd2; // S, green
    end
    4'b0110: begin
      data = 12'h7cd; // Z, red
    end
    4'b0111: begin
      data = 12'h17b; // shadow, grey
    end
    4'b1000: begin
      data = 12'h5c8; // garbage
    end
    4'b1001: begin
      data = 12'hf39; // background
    end
    4'b1010: begin
      data = 12'hf86; // dark background
    end
    4'b1011: begin
      data = 12'h321; // I, light cyan
    end
    4'b1100: begin
      data = 12'h654; // T, light purple
    end
    4'b1101: begin
      data = 12'ha83; // O, light yellow
    end
    4'b1110: begin
      data = 12'hf86; // J, light blue
    end
    4'b1111: begin
      data = 12'hfdb; // L, light orange
    end
  endcase
end
endmodule

//module draw_bottom_half (
//  input [2:0] addr_x,
//  input [2:0] addr_y,
//  input [11:0] bg,
//  input [11:0] fg,
//  output [11:0] res
//  );
//  assign res = addr_y > 4 ? fg : bg;
//endmodule
//module draw_border (
//  input [2:0] addr_x,
//  input [2:0] addr_y,
//  input [11:0] bg,
//  input [11:0] fg,
//  output reg [11:0] res
//  );
//  always @(*) begin
//    res = bg;
//    if (addr_x == 0 || addr_y == 0 || addr_x == 7 || addr_y == 7) begin
//      res = fg;
//    end
//    if (addr_x == 1 || addr_y == 1 || addr_x == 6 || addr_y == 6) begin
//      res = fg;
//    end
//  end
//endmodule
