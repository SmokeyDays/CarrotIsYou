#include "keyInput.h"
#ifndef RISCV
#include "sdl_interface.h"
#endif
#define K_ARROW_PREFIX 0xe0
#define K_RELEASE_PREFIX 0xf0


#define K_W     0x1D   // release: F01D
#define K_S     0x1B   // release: F01B
#define K_A     0x1C   // release: F01C
#define K_D     0x23   // release: F023
#define K_SPACE 0x29   // release: F029
#define K_Z     0x1A   // release: F01A
#define K_R     0x2D   // release: F02D
#define K_Q     0x15   // release: F015
#define K_P     0x4D   // release: F04D

#define K_LEFT 0x6b
#define K_RIGHT 0x74
#define K_UP 0x75
#define K_DOWN 0x72
#define K_ENTER 0x5A // release: E0F05A

#ifndef RISCV
#define BUF_SIZE 32
#define BUF_MASK (BUF_SIZE - 1)
unsigned char key_buffer[32];
unsigned char head = 0;
unsigned char tail = 0;
#endif

#ifndef RISCV
#endif

unsigned char kbd_ready() {
#ifdef RISCV
  return keyboard_ready();
#else
  return head != tail;
#endif
}

unsigned char kbd_data() {
#ifdef RISCV
  return keyboard_data();
#else
  unsigned char ret = key_buffer[head];

  head = (head + 1) & BUF_MASK;
  return ret;
#endif
}

int getKey() {
#ifndef RISCV
  sdl_wait_key(&key_buffer, &head, &tail);
#endif
  int ret = 0;
  while (kbd_ready()) {
    unsigned char cur = kbd_data();
    switch (cur) {
      case K_W:
      case K_S:
      case K_A:
      case K_D:
      case K_SPACE:
      case K_Z:
      case K_R:
      case K_Q:
      case K_P:
      case K_ENTER:
        ret = cur;
        break;
      default:
        break;
    }
  }
  return ret;
  // uint8_t key_bin = key->down | (key->right << 1) | (key->left << 2) |
  //                   (key->space << 3) | (key->c << 4) | (key->x << 5) |
  //                   (key->z << 6);
  // //  0b10000000
  // //     zxcSlrd
  // send_data(0xff);
  // send_data(key_bin);
  return ret;
}

// void wait_any_key_down(struct KeyMap* key) {
//   while (1) {
//     int res = input_update(key);
//     memset(key, 0, sizeof(struct KeyMap));
//     if ((res & 1) == 1) {
//       return;
//     }
//   }
// }

