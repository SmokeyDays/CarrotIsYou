#include "libdevice.h"
#include "Interfaces.h"
#ifdef RISCV

bool keyEmpty() {
  return keyboard_ready();
}

unsigned char getKey() {
  return keyboard_data();
}

#endif