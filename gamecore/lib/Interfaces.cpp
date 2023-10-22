#include "libdevice.h"
#include "Interfaces.h"
#ifdef RISCV

bool keyEmpty() {
  return keyboard_ready();
}

unsigned char keyPop() {
  unsigned key = keyboard_data();
  set_led(key);
  return key;
}

#endif