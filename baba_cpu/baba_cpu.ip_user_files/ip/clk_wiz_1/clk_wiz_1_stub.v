// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2022.2 (win64) Build 3671981 Fri Oct 14 05:00:03 MDT 2022
// Date        : Fri Nov  3 12:14:22 2023
// Host        : DESKTOP-CJ62T2D running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               F:/lsy_code/CarrotIsYou/baba_cpu/baba_cpu.runs/clk_wiz_1_synth_1/clk_wiz_1_stub.v
// Design      : clk_wiz_1
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
module clk_wiz_1(vga_clk, reset, locked, clk_in1)
/* synthesis syn_black_box black_box_pad_pin="vga_clk,reset,locked,clk_in1" */;
  output vga_clk;
  input reset;
  output locked;
  input clk_in1;
endmodule
