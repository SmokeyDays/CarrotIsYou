#include "libdevice.h"
#ifdef RISCV

bool keyEmpty() {
  return keyboard_ready();
}

uint8_t getKey() {
  return keyboard_data();
}

#endif