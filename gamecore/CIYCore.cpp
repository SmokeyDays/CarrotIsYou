#include "CIYCore.h"
#include "./lib/LevelManager.h"
#include "./lib/MiniMalloc.h"

void CIYCore::initBoard() {
  const unsigned short *levelData = getLevel(level);
  if (levelData == nullptr) {
    return;
  }
  int dataLen = levelData[0];
  int width = levelData[1];
  int height = levelData[2];
  BufVector<CIYObject, MAX_OBJ_NUM> objs;
  for (int i = 3; i < dataLen; i++) {
    objs.push(CIYObject(levelData[i]));
  }
  board.init(height, width, objs);
}

void CIYCore::init(int level) {
  this->level = level;
  history.clear();
  initBoard();
}


void CIYCore::move(int direction) {
  history.push(direction);
  backPoint = history.size();
  allHistory[backPoint % ALL_HISTORY_SIZE] = board;
  board.move(direction);
}

void CIYCore::undo() {
  if(!history.size()) {
    return;
  }
  history.pop();
  if(backPoint - history.size() < ALL_HISTORY_SIZE) {
    board = allHistory[history.size() % ALL_HISTORY_SIZE];
    return;
  }
  initBoard();
  for(int i = 0; i < history.size(); ++i) {
    board.move(history[i]);
  }
}