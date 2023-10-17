#include "CIYCore.h"
#include "./lib/LevelManager.h"
#include "./lib/MiniMalloc.h"

void CIYCore::init(int level) {
  history.clear();
  const unsigned short *levelData = getLevel(level);
  if (levelData == nullptr) {
    return;
  }
  int dataLen = levelData[0];
  int height = levelData[1];
  int width = levelData[2];
  BufVector<CIYObject, MAX_OBJ_NUM> objs;
  for (int i = 3; i < dataLen; i++) {
    objs.push(CIYObject(levelData[i]));
  }
  board.init(height, width, objs);
}


void CIYCore::move(int direction) {
  history.push(board);
  board.move(direction);
}