-makelib xcelium_lib/xpm -sv \
  "F:/Xilinx/Vivado/2022.2/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \
-endlib
-makelib xcelium_lib/xpm \
  "F:/Xilinx/Vivado/2022.2/data/ip/xpm/xpm_VCOMP.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../../baba_cpu.gen/sources_1/ip/clk_wiz/clk_wiz_clk_wiz.v" \
  "../../../../baba_cpu.gen/sources_1/ip/clk_wiz/clk_wiz.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  glbl.v
-endlib

