#pragma once

#include "CIYBoard.h"
#include "./lib/MiniMalloc.h"

const int HISTORY_SIZE = 16;


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
