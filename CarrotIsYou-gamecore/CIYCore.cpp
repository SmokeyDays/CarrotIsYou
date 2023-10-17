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
  render();
}

void CIYCore::render() {
  for(int i = 0; i < WIDTH_MAX; i++) {
    for(int j = 0; j < HEIGHT_MAX; j++) {
      display[i][j] = EMPTY;
      mask[i][j] = 0;
    }
  }
  const BufVector<CIYObject, MAX_OBJ_NUM> objs = board.getObjects();
  for (auto &&obj : objs) {
    display[obj.x()][obj.y()] = obj.type();
  }
  const BufVector<CIYObject, MAX_ILLEGAL_NUM> illegalObjs = board.getIllegalObjects();
  for (auto &&obj : illegalObjs) {
    mask[obj.x()][obj.y()] |= 1 << 0;
  }

  BufVector<CIYObject, MAX_OBJ_NUM> winObjs = board.getWinObjs();
  for (auto &&obj : winObjs) {
    mask[obj.x()][obj.y()] |= 1 << 1;
  }
}