#include "libdevice.h"
#ifdef RISCV
// top of stack
extern unsigned __stacktop;
// initial stack pointer is first address of program
__attribute__((section(".stack"), used)) unsigned* __stack_init = &__stacktop;

extern int main();

__attribute__((section(".text.start"))) __attribute__((naked)) void _start() {
  asm("mv sp, %0\n\t" ::"r"(&__stacktop));
  asm("j %0\n\t" ::"i"(&main));
}
#endif

unsigned int time() { return *CLOCK_ADDR; }

void sleep(unsigned int us) {
  unsigned int start = *CLOCK_ADDR;
  while (1) {
    if (*CLOCK_ADDR >= start + us) {
      break;
    }
  }
}

void set_led(unsigned int val) { *LED_ADDR = val; }

void set_vram(int x, int y, unsigned int pixel) {
  VRAM_ADDR[x * VRAM_Y + y] = pixel;
}
void commit_vram() { *VRAM_COMMIT_ADDR = 1; }
unsigned char keyboard_ready() { return *KBD_READY_ADDR; }

unsigned char keyboard_data() { return *KBD_DATA_ADDR; }

unsigned char uart_recv_ready() { return *UART_RECV_READY_ADDR; }
unsigned char uart_send_ready() { return *UART_SEND_READY_ADDR; }
unsigned char uart_recv() { return *UART_RECV_DATA_ADDR; }
void uart_send(unsigned char data) { *UART_SEND_DATA_ADDR = data; }
