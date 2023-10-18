#pragma once

#include "CIYBoard.h"
#include "./lib/MiniMalloc.h"

const int HISTORY_SIZE = 256;


class CIYCore {
private:
  int level;
  CIYBoard board;
  BufVector<int, HISTORY_SIZE> history;

  void initBoard();

public:
  CIYCore() = default;

  void init(int level);

  ~CIYCore() = default;

  CIYBoard &getBoard() {
    return board;
  }

  void move(int direction);
  void undo();
  bool isWinning() {
    return board.isWinning();
  }
};
