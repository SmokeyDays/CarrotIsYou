#pragma once

#include "CIYBoard.h"

class CIYCore {
private:
  CIYBoard board;

public:
  CIYCore();

  ~CIYCore();

  CIYBoard &getBoard() {
    return board;
  }
};
