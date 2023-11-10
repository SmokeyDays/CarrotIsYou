#include "Interfaces.h"
#ifdef RISCV

bool keyEmpty() {
  return !keyboard_ready();
}

unsigned char keyPop() {
  unsigned int key = keyboard_data();
  return key;
}

#endif