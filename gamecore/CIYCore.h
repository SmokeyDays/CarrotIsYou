#pragma once

#include "CIYBoard.h"
#include "./lib/MiniMalloc.h"

const int HISTORY_SIZE = 512;
const int ALL_HISTORY_SIZE = 32;


class CIYCore {
private:
  int level;
  CIYBoard board;
  BufVector<int, HISTORY_SIZE> history;
  int backPoint;
  BufVector<CIYBoard, ALL_HISTORY_SIZE> allHistory;

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
  bool isDefeat() {
    return board.isDefeat;
  }
};
