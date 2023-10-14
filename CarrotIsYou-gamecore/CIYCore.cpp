#pragma once
#include "lib/MiniMalloc.cpp"
#include "lib/MiniVector.cpp"

const int MAX_OBJ_NUM = 1024;
const int MAX_RULE_NUM = 64;

const int NOUN_NUM = 16;
const int VERB_NUM = 8;
const int ADJ_NUM = 16;

// type_noun: 0: Carrot, 1: Flag, 2: Wall, 3: Rock, 4: Water, 5: Lava, 6: Ice, 7: Heart, 8: Witchess, 9: Door, 10: Key, 11: Box, 12: Star, 13: Skull, 14: Ghost, 15: Bug
// type_verb: 16: Is, 17: Has, 18: And
// type_adj: 24: You, 25: Win, 26: Push, 27: Stop, 28: Melt, 29: Sink, 30: Hot, 31: Defeat, 32: Open, 33: Shut, 34: Weak, 35: Move, 36: Float
// type_noun_text: 40: Carrot, 41: Flag, 42: Wall, 43: Rock, 44: Water, 45: Lava, 46: Ice, 47: Heart, 48: Witchess, 49: Door, 50: Key, 51: Box, 52: Star, 53: Skull, 54: Ghost, 55: Bug

enum CIYType {
  CARROT = 0, FLAG, WALL, ROCK, WATER, LAVA, ICE, HEART, WITCHESS, DOOR, KEY, BOX, STAR, SKULL, GHOST, BUG,
  IS = 16, HAS, AND,
  YOU = 24, WIN, PUSH, STOP, MELT, SINK, HOT, DEFEAT, OPEN, SHUT, WEAK, MOVE, FLOAT,
  CARROT_TEXT = 40, FLAG_TEXT, WALL_TEXT, ROCK_TEXT, WATER_TEXT, LAVA_TEXT, ICE_TEXT, HEART_TEXT, WITCHESS_TEXT, DOOR_TEXT, KEY_TEXT, BOX_TEXT, STAR_TEXT, SKULL_TEXT, GHOST_TEXT, BUG_TEXT
};

struct CIYObject {
  int x, y;
  CIYType type;
  int direction;
};

struct CIYBoard {
  int height, width;
  
  int objectNum;
  CIYObject objects[MAX_OBJ_NUM];
  
  int ruleNum;
  CIYRule rules[MAX_RULE_NUM];


  CIYObject &getObject(int obj) {
    return objects[obj];
  }
  Vector getObjectsByPositionAndAdj(int x, int y, int adj) {
    Vector ret;
    ret.push(0);
    for (int i = 0; i < objectNum; i++) {
      if (objects[i].x == x && objects[i].y == y && hasAdj(i, adj)) {
        ret.push(i);
      }
    }
    return ret;
  }
  Vector getObjectsByNoun(int noun) {
    Vector ret;
    ret.push(0);
    for (int i = 0; i < objectNum; i++) {
      if (objects[i].type == noun) {
        ret.push(i);
      }
    }
    return ret;
  }
  Vector getObjectsByPosition(int x, int y) {
    Vector ret;
    ret.push(0);
    for (int i = 0; i < objectNum; i++) {
      if (objects[i].x == x && objects[i].y == y) {
        ret.push(i);
      }
    }
    return ret;
  }
  Vector getObjectsByAdj(int adj) {
    Vector ret;
    ret.push(0);
    for(int i = 0; i < ruleNum; i++) {
      if (rules[i].adj == adj && rules[i].verb == IS) {
        ret.push(rules[i].noun);
      }
    }
    return ret;
  }
  Vector getAdjByNoun(int noun) {
    Vector ret;
    ret.push(0);
    for(int i = 0; i < ruleNum; i++) {
      if (rules[i].noun == noun && rules[i].verb == IS) {
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
  bool isAtEdge(int obj) {
    if (getObject(obj).x == 0 || getObject(obj).x == width - 1 || getObject(obj).y == 0 || getObject(obj).y == height - 1) {
      return true;
    }
    return false;
  }
  bool isAtEdge(int x, int y) {
    if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
      return true;
    }
    return false;
  }
  bool applyMove(Vector objs, int direction, int x, int y) {
    bool posStop = false;
    for (int i = 1; i < objs.size(); i++) {
      posStop |= hasAdj(objs[i], STOP);
    }

    if (posStop || isAtEdge(x, y)) {
      return false;
    }
    if (direction == 0) {
      Vector nextObjs = getObjectsByPositionAndAdj(x, y - 1, PUSH);
      if (nextObjs.size() > 0 && !applyMove(nextObjs, direction, x, y - 1)) {
        return false;
      }
      for (int i = 0; i < objs.size(); i++) {
        getObject(objs[i]).y--;
      }
    } else if (direction == 1) {
      Vector nextObjs = getObjectsByPositionAndAdj(x + 1, y, PUSH);
      if (nextObjs.size() > 0 && !applyMove(nextObjs, direction, x + 1, y)) {
        return false;
      }
      for (int i = 0; i < objs.size(); i++) {
        getObject(objs[i]).x++;
      }
    } else if (direction == 2) {
      Vector nextObjs = getObjectsByPositionAndAdj(x, y + 1, PUSH);
      if (nextObjs.size() > 0 && !applyMove(nextObjs, direction, x, y + 1)) {
        return false;
      }
      for (int i = 0; i < objs.size(); i++) {
        getObject(objs[i]).y++;
      }
    } else if (direction == 3) {
      Vector nextObjs = getObjectsByPositionAndAdj(x - 1, y, PUSH);
      if (nextObjs.size() > 0 && !applyMove(nextObjs, direction, x - 1, y)) {
        return false;
      }
      for (int i = 0; i < objs.size(); i++) {
        getObject(objs[i]).x--;
      }
    }
    return true;
  }

public:  
  // Up 0, Right 1, Down 2, Left 3
  void move(int direction) {
    // move stage
    Vector objAutoMove = getObjectsByAdj(MOVE);
    Vector objMove[4];
    for(int i = 0; i < objAutoMove.size(); i++) {
      objMove[getObject(objAutoMove[i]).direction].push(objAutoMove[i]);
    }
    Vector objYouMove = getObjectsByAdj(YOU);
    objMove[direction].push(objYouMove);
    for(int i = 0; i < 4; i++) {
      if(objMove[i].size() > 0) {
        applyMove(objMove[i], i, getObject(objMove[i][0]).x, getObject(objMove[i][0]).y);
      }
    }
    // check rules
  }
};

struct CIYRule {
  CIYType noun, verb, adj;
};

class CIYCore {
private:
  CIYBoard board;

public:
  CIYCore() {
    
  }
  ~CIYCore() {
    
  }
  CIYBoard getBoard() {
    return board;
  }
};