#include "CarrotOS.h"
#include "./lib/MiniMalloc.h"

int main() {
  set_led(0x13579bdf);
  CarrotOS os;
  os.run();
  return 0;
}