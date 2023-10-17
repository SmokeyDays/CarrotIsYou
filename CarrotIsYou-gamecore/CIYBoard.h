#pragma once

#include "lib/MiniMalloc.h"
#include "lib/MiniVector.h"
#include "lib/BufVector.h"
#include "CIYBase.h"

const int MAX_OBJ_NUM = 128;
const int MAX_RULE_NUM = 64;
const int MAX_ILLEGAL_NUM = 16;

struct CIYBoard {
  int height, width;

  BufVector<CIYObject, MAX_OBJ_NUM> objects;
  BufVector<CIYRule, MAX_RULE_NUM> rules;
  BufVector<CIYObject, MAX_ILLEGAL_NUM> illegalObjects;

  bool isWin;

  CIYObject &getObject(int obj) {
    return objects[obj];
  }

  void removeObject(int obj) {
    objects[obj].setType(EMPTY);
  }

  const CIYObject &getObject(int obj) const {
    return objects[obj];
  }

  template<typename Func>
  Vector getObjectsByCondition(Func condition) const {
    Vector ret;
    for (int i = 0; i < objects.size(); i++) {
      if (condition(objects[i]) && objects[i].type() != EMPTY) {
        ret.push(i);
      }
    }
    return ret;
  }

  template<typename Func>
  Vector getRulesByCondition(Func condition) const {
    Vector ret;
    for (int i = 0; i < rules.size(); i++) {
      if (condition(rules[i])) {
        ret.push(i);
      }
    }
    return ret;
  }

  bool atSameFloat(int A, int B) const {
    return !(objHasAdj(A, FLOAT) ^ objHasAdj(B, FLOAT));
  }

  Vector getObjectsByPositionAndAdj(int x, int y, int adj) const {
    return getObjectsByCondition([&](const CIYObject &obj) {
      return obj.x() == x && obj.y() == y && nounHasAdj(obj.type(), adj);
    });
  }

  Vector getObjectsByNoun(int noun) const {
    return getObjectsByCondition([&](const CIYObject &obj) {
      return obj.type() == noun;
    });
  }

  Vector getObjectsByPosition(int x, int y) const {
    return getObjectsByCondition([&](const CIYObject &obj) {
      return obj.x() == x && obj.y() == y;
    });
  }

  Vector getObjectsByAdj(int adj) const {
    return getObjectsByCondition([&](const CIYObject &obj) {
      return nounHasAdj(obj.type(), adj);
    });
  }

  Vector getAdjByNoun(int noun) const {
    Vector ret;
    ret.push(0);
    for (auto &rule : rules) {
      if (rule.subject() == noun && rule.verb() == IS && getGroupByType(rule.object()) == ADJ) {
        ret.push(rule.object());
      }
    }
    return ret;
  }

  bool nounHasAdj(int noun, int adj) const {
    Vector adjs = getAdjByNoun(noun);
    for (int i = 0; i < adjs.size(); i++) {
      if (adjs[i] == adj) {
        return true;
      }
    }
    return false;
  }

  bool objHasAdj(int obj, int adj) const {
    return nounHasAdj(getObject(obj).type(), adj);
  }

  Vector getObjectsByType(int type) const {
    Vector ret;
    ret.push(0);
    for (int i = 0; i < objects.size(); i++) {
      if (objects[i].type() == type) {
        ret.push(i);
      }
    }
    return ret;
  }

  bool isAtEdge(int x, int y) const {
    return x == 0 || x == height - 1 || y == 0 || y == width - 1;
  }

  bool isAtEdge(int objId) const {
    const CIYObject &object = getObject(objId);
    return isAtEdge(object.x(), object.y());
  }

  bool applyPush(const Vector &objs, int direction, int x, int y, Vector &pushList);

  bool applyPull(const Vector &objs, int direction, int x, int y, Vector &pullList);
  
  void insertRules(const Vector &subjects, const Vector &verb, const Vector &objects);

  void checkRemove();

  void checkRules();

public:

  CIYBoard() {
    height = 0;
    width = 0;
    isWin = false;
  };

  ~CIYBoard() {
    objects.clear();
    rules.clear();
    illegalObjects.clear();
  }

  void init(int h, int w, const BufVector<CIYObject, MAX_OBJ_NUM> &objs) {
    height = h;
    width = w;
    objects.clear();
    for(auto obj : objs) {
      objects.push(obj);
    }
    checkRules();
  }

  // Up 0, Right 1, Down 2, Left 3
  void move(int direction);

  bool isWinning() const {
    return isWin;
  }

  const BufVector<CIYObject, MAX_OBJ_NUM> &getObjects() const {
    return objects;
  }

  const BufVector<CIYObject, MAX_ILLEGAL_NUM> &getIllegalObjects() const {
    return illegalObjects;
  }
  
  const BufVector<CIYRule, MAX_RULE_NUM> &getRules() const {
    return rules;
  }

  BufVector<CIYObject, MAX_OBJ_NUM> getWinObjs() {
    Vector winObjs = getObjectsByAdj(WIN);
    BufVector<CIYObject, MAX_OBJ_NUM> ret;
    for (int i = 0; i < winObjs.size(); i++) {
      ret.push(getObject(winObjs[i]));
    }
    return ret;
  }

};
