#include "LevelManager.h"

const unsigned short LEVEL1[] = {
     54,    16,     8, 40960, 16400, 24608, 42048,
  16464, 25696, 43120, 16512, 27792, 44192, 16560,
  26816,    53,  1237,  2049,  2055,  2065,  2071,
   2081,  2087,  2097,  2103,  2113,  2119,  2129,
   2135,  2145,  2151,  2161,  2167,  2177,  2183,
   2193,  2199,  2209,  2215,  2225,  2231,  2241,
   2247,  2257,  2263,  2273,  2279,  2289,  2295,
   3202,  3203,  3204,  3205,  3206
};

const unsigned short *getLevel(int level) {
  switch (level) {
    case 1:
      return (const unsigned short *)LEVEL1;
    default:
      return nullptr;
  }
}