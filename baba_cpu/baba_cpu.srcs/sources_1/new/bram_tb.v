`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/10/22 14:57:37
// Design Name: 
// Module Name: bram_tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module bram_tb(

    );
    
    reg clk, rst, load, store;
    reg [2:0] acc;
    reg [31:0] addr, din;
    wire [31:0] dout;
    
    ram ramtb(clk, rst, load, store, acc, addr, din, dout);
    
    initial begin
        clk <= 0;
        rst <= 0;
        load <= 0;
        store <= 0;
        acc <= 0;
        addr <= 0;
        din <= 0;
        forever # 3 clk <= ~clk;
    end
    
    initial begin
    
        #10
        store <= 1;
        addr <= 0;
        acc <= 2;
        din <= 32'haabbccdd;
        
        #10
        acc <= 1;
        store <= 0;
        load <= 1;
        
        #10
        addr <= 1;
        
        #10
        addr <= 2;
        
        #10
        addr <= 3;
        
        #10
        store <= 1;
        load <= 0;
        acc <= 1;
        din <= 32'h11223344;
        addr <= 4;
        
        #10
        store <= 0;
        load <= 1;
        acc <= 0;
        
        #10
        acc <= 1;
        
        #10
        acc <= 2;
        
    end
    
    
    
    
    
endmodule
