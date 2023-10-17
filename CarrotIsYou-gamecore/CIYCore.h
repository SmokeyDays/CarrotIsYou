#pragma once

#include "CIYBoard.h"

constexpr int HISTORY_SIZE = 16;
const unsigned short LEVEL1[] = {
     54,    16,     8, 40960, 16385, 24578, 41988,
  16389, 25606, 43016, 16393, 27658, 44044, 16397,
  26638,    83,  1118,  2064,  2160,  2065,  2161,
   2066,  2162,  2067,  2163,  2068,  2164,  2069,
   2165,  2070,  2166,  2071,  2167,  2072,  2168,
   2073,  2169,  2074,  2170,  2075,  2171,  2076,
   2172,  2077,  2173,  2078,  2174,  2079,  2175,
   3112,  3128,  3144,  3160,  3176
};

int *getLevel(int level) {
  switch (level) {
    case 1:
      return (int *)LEVEL1;
    default:
      return nullptr;
  }
}

class CIYCore {
private:
  CIYBoard board;
  BufVector<CIYBoard, HISTORY_SIZE> history;

  void render();

public:
  unsigned short display[WIDTH_MAX][HEIGHT_MAX];
  unsigned short mask[WIDTH_MAX][HEIGHT_MAX];
  CIYCore() = default;

  void init(int level);

  ~CIYCore() = default;

  CIYBoard &getBoard() {
    return board;
  }

  void move(int direction);
  void undo() {
    if (history.size() > 0) {
      board = history.pop();
      render();
    }
  }
};
