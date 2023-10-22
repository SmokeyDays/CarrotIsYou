`timescale 1ns/10ps
module single_cycle_cpu_board_tb();
  reg clk, rst, halt, ps2_clk;
  wire [7:0] AN, SEG;
  always #2 clk     = ~clk;
  localparam period = 5;
  initial begin
    clk            <= 0;
    forever #1 clk = ~clk;
  end
  initial begin
    
    //ps2_clk <=0;
    //forever #100 ps2_clk<=~ps2_clk;
    
  end
  /*iverilog */
  initial begin
    $dumpfile("single_cycle_cpu_board_wave_vga.vcd");        //生成的vcd文件名称
    $dumpvars(0, 
    cpu.VGA_R,
    cpu.VGA_G,
    cpu.VGA_B,
    cpu.VGA_HS,
    cpu.VGA_VS
    );    //tb模块名称
  end
  wire [3:0] VGA_R, VGA_G, VGA_B;
  wire VGA_HS, VGA_VS;
  wire [5:0]LED;
  single_cycle_cpu_board cpu(.clk(clk),
  .rst(rst),
  .halt(halt),
  .AN(AN),
  .SEG(SEG),
  .VGA_R(VGA_R),
  .VGA_G(VGA_G),
  .VGA_B(VGA_B),
  .VGA_HS(VGA_HS),
  .VGA_VS(VGA_VS),
  .LED(LED)
  //, .PS2_CLK(ps2_clk)
  );
  initial begin
    clk  = 0;
    rst  = 1;
    halt = 0;
    #100;
    rst = 0;
    #34000000;
    $stop;
  end
endmodule
