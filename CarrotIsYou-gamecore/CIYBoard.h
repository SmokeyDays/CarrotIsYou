#pragma once

#include "lib/MiniMalloc.h"
#include "lib/MiniVector.h"
#include "CIYBase.h"

const int MAX_OBJ_NUM = 1024;
const int MAX_RULE_NUM = 64;

struct CIYBoard {
  int height, width;

  int objectNum;
  CIYObject objects[MAX_OBJ_NUM];

  int ruleNum;
  CIYRule rules[MAX_RULE_NUM];

  CIYObject &getObject(int obj) {
    return objects[obj];
  }

  const CIYObject &getObject(int obj) const {
    return objects[obj];
  }

  template<typename Func>
  Vector getObjectsByCondition(Func condition) {
    Vector ret;
    ret.push(0);
    for (int __getObjectsByCondition_i = 0; __getObjectsByCondition_i < objectNum; __getObjectsByCondition_i++) {
      if (condition(objects[__getObjectsByCondition_i])) {
        ret.push(__getObjectsByCondition_i);
      }
    }
    return ret;
  }

  Vector getObjectsByPositionAndAdj(int x, int y, int adj) {
    return getObjectsByCondition([&](CIYObject obj) {
      return obj.x == x && obj.y == y && this->hasAdj(obj.type, adj);
    });
  }

  Vector getObjectsByNoun(int noun) {
    return getObjectsByCondition([&](CIYObject obj) {
      return obj.type == noun;
    });
  }

  Vector getObjectsByPosition(int x, int y) {
    return getObjectsByCondition([&](CIYObject obj) {
      return obj.x == x && obj.y == y;
    });
  }

  Vector getObjectsByAdj(int adj) {
    return getObjectsByCondition([&](CIYObject obj) {
      return hasAdj(obj.type, adj);
    });
  }

  Vector getAdjByNoun(int noun) {
    Vector ret;
    ret.push(0);
    for (int i = 0; i < ruleNum; i++) {
      if (rules[i].noun == noun) {
        ret.push(rules[i].adj);
      }
    }
    return ret;
  }

  bool hasAdj(int noun, int adj) {
    Vector adjs = getAdjByNoun(noun);
    for (int i = 1; i < adjs.size(); i++) {
      if (adjs[i] == adj) {
        return true;
      }
    }
    return false;
  }

  Vector getObjectsByType(int type) {
    Vector ret;
    ret.push(0);
    for (int i = 0; i < objectNum; i++) {
      if (objects[i].type == type) {
        ret.push(i);
      }
    }
    return ret;
  }

  bool isAtEdge(int x, int y) const {
    return x == 0 || x == width - 1 || y == 0 || y == height - 1;
  }

  bool isAtEdge(int obj) const {
    const CIYObject &object = getObject(obj);
    return isAtEdge(object.x, object.y);
  }

  bool applyMove(const Vector &objs, int direction, int x, int y);

public:
  // Up 0, Right 1, Down 2, Left 3
  void move(int direction);
};
