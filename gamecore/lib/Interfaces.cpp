#include "libdevice.h"
#include "Interfaces.h"
#ifdef RISCV

bool keyEmpty() {
  return keyboard_ready();
}

unsigned char keyPop() {
  return keyboard_data();
}

#endif