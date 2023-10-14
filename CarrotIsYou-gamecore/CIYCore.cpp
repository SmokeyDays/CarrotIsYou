#pragma once
#include "lib/MiniMalloc.cpp"
#include "lib/MiniVector.cpp"

const int MAX_OBJ_NUM = 1024;

struct CIYObject {
  int x, y;
  int type;
  int direction;
};

struct CIYBoard {
  int height, width;
  
  int objectNum;
  CIYObject objects[MAX_OBJ_NUM];
};

class CIYCore {
private:
  CIYBoard board;
public:
  CIYCore() {
    
  }
  ~CIYCore() {
    
  }
  // Up 0, Right 1, Down 2, Left 3
  void move(int direction) {
    
  }
  Vector getObjectsByPosition(int x, int y) {
    Vector ret;
    ret.push(0);
    
  }
  Vector getObjectsByFeature(int feature) {
    Vector ret;
    ret[0] = 0;
    for (int i = 0; i < board.objectNum; i++) {
      if (board.objects[i].type == feature) {
        ret[++ret[0]] = i;
      }
    }
    return ret;
  }
  CIYBoard getBoard() {
    return board;
  }
};