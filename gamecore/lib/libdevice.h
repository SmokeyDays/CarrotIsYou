#pragma once
#define CLOCK_ADDR ((volatile unsigned char*)0xfbadbedf)
#define LED_ADDR ((volatile unsigned int*)0xfbadc0fe)
#define VRAM_ADDR ((volatile unsigned char*)0xfbad0000)
#define VRAM_COMMIT_ADDR ((volatile unsigned char*)0xfbadf000)
#define KBD_READY_ADDR ((volatile unsigned char*)0xfbadbeee)
#define KBD_DATA_ADDR ((volatile unsigned char*)0xfbadbeef)
#define UART_RECV_READY_ADDR ((volatile unsigned char*)0xfbada000)
#define UART_SEND_READY_ADDR ((volatile unsigned char*)0xfbada001)
#define UART_RECV_DATA_ADDR ((volatile unsigned char*)0xfbada002)
#define UART_SEND_DATA_ADDR ((volatile unsigned char*)0xfbada003)
#define VRAM_X 128 // X is vertical
#define VRAM_Y 128 // Y is horizontal
unsigned int time();

void sleep(unsigned int us);

void set_led(unsigned int val);

void set_vram(int x, int y, unsigned int pixel);

void commit_vram();

unsigned char keyboard_ready();

unsigned char keyboard_data();

unsigned char uart_recv_ready();
unsigned char uart_send_ready();
unsigned char uart_recv();
void uart_send(unsigned char data);