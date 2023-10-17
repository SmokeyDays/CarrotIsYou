#pragma once

#include "CIYCore.h"
#include "./lib/Interfaces.h"
#include "./lib/MiniMalloc.h"

enum OSState {
  OS_INIT,
  OS_GAME_START,
  OS_GAME_RUNNING,

};

const int LEVEL_MAX = 16;

class CarrotOS {
private:
  CIYCore core;
  OSState state = OS_INIT;
  int level = 1;
  void renderIcon(int x, int y, int type, int times);
  void renderTest();
  void renderGameRunning();
  void renderGameStart();
  void renderInit();
public:
  void run();
};