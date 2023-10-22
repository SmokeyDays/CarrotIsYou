// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2022.2 (win64) Build 3671981 Fri Oct 14 05:00:03 MDT 2022
// Date        : Mon Oct 23 06:11:28 2023
// Host        : DESKTOP-CJ62T2D running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               f:/lsy_code/CarrotIsYou/baba_cpu/baba_cpu.gen/sources_1/ip/bram_3/bram_3_stub.v
// Design      : bram_3
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "blk_mem_gen_v8_4_5,Vivado 2022.2" *)
module bram_3(clka, wea, addra, dina, clkb, addrb, doutb)
/* synthesis syn_black_box black_box_pad_pin="clka,wea[0:0],addra[13:0],dina[7:0],clkb,addrb[13:0],doutb[7:0]" */;
  input clka;
  input [0:0]wea;
  input [13:0]addra;
  input [7:0]dina;
  input clkb;
  input [13:0]addrb;
  output [7:0]doutb;
endmodule
