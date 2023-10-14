#pragma once
#include "lib/MiniMalloc.cpp"
#include "lib/MiniVector.cpp"

const int MAX_OBJ_NUM = 1024;
const int MAX_RULE_NUM = 64;

const int NOUN_NUM = 16;
const int VERB_NUM = 8;
const int ADJ_NUM = 16;

constexpr int DIRECTION[4][2] = {
  {0, -1},
  {1, 0},
  {0, 1},
  {-1, 0}
};

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

enum CIYTypeGroup {
  NOUN = 0, VERB, ADJ, NOUN_TEXT
};

CIYTypeGroup getGroupByType(CIYType type) {
  if (type < 16) {
    return NOUN;
  } else if (type < 24) {
    return VERB;
  } else if (type < 40) {
    return ADJ;
  } else {
    return NOUN_TEXT;
  }
}

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

    auto [dx, dy] = DIRECTION[direction];
    
    Vector nextObjs = getObjectsByPositionAndAdj(x + dx, y + dy, PUSH);
    if (nextObjs.size() > 0 && !applyMove(nextObjs, direction, x + dx, y + dy)) {
      return false;
    }
    for (int i = 0; i < objs.size(); i++) {
      getObject(objs[i]).x += dx;
      getObject(objs[i]).y += dy;
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
    Vector objYou = getObjectsByAdj(YOU);
    objMove[direction].push(objYou);
    for(int i = 0; i < 4; i++) {
      if(objMove[i].size() > 0) {
        applyMove(objMove[i], i, getObject(objMove[i][0]).x, getObject(objMove[i][0]).y);
      }
    }
    // check rules
    ruleNum = 0;
    // check by row
    for(int i = 0; i < height; i++) {
      Vector objs = getObjectsByPosition(0, i);
      for(int j = 1; j < width - 1; j++) {
        // Filter Verbs That is "IS" or "HAS"
        Vector verbObjs = getObjectsByPositionAndAdj(j, i, IS);
        verbObjs.push(getObjectsByPositionAndAdj(j, i, HAS));
        if(verbObjs.size() == 0) {
          continue;
        }

        // Filter Subjects; Subjects are Nouns
        int last_subject = j - 1;
        Vector subjects = getObjectsByCondition([&](CIYObject obj) {
          return obj.x == j - 1 && obj.y == i && getGroupByType(obj.type) == NOUN_TEXT;
        });
        if(subjects.size() == 0) {
          continue;
        }
        while(last_subject > 1) {
          Vector newSubjects = getObjectsByCondition([&](CIYObject obj) {
            return obj.x == last_subject - 2 && obj.y == i && getGroupByType(obj.type) == NOUN_TEXT;
          });
          Vector andObjs = getObjectsByPositionAndAdj(last_subject - 1, i, AND);
          if (newSubjects.size() == 0 || andObjs.size() == 0) {
            break;
          }
          last_subject -= 2;
          subjects.push(newSubjects);
        }

        // Filter Objects; Objects are Nouns or Adjectives
        int last_object = j + 1;
        Vector objects = getObjectsByCondition([&](CIYObject obj) {
          return obj.x == j + 1 && obj.y == i && (getGroupByType(obj.type) == NOUN_TEXT || getGroupByType(obj.type) == ADJ);
        });
        if(objects.size() == 0) {
          continue;
        }
        while(last_object < width - 2) {
          Vector newObjects = getObjectsByCondition([&](CIYObject obj) {
            return obj.x == last_object + 2 && obj.y == i && (getGroupByType(obj.type) == NOUN_TEXT || getGroupByType(obj.type) == ADJ);
          });
          Vector andObjs = getObjectsByPositionAndAdj(last_object + 1, i, AND);
          if (newObjects.size() == 0 || andObjs.size() == 0) {
            break;
          }
          last_object += 2;
          objects.push(newObjects);
        }
        for(int k = 0; k < subjects.size(); k++) {
          for(int l = 0; l < objects.size(); l++) {
            for(int m = 0; m < verbObjs.size(); m++) {
              CIYRule rule = {getObject(subjects[k]).type, getObject(verbObjs[m]).type, getObject(objects[l]).type};
              if(ruleNum == 0) {
                rules[ruleNum++] = rule;
              } else {
                bool isSame = false;
                for(int n = 0; n < ruleNum; n++) {
                  if(rules[n].noun == rule.noun && rules[n].verb == rule.verb && rules[n].adj == rule.adj) {
                    isSame = true;
                    break;
                  }
                }
                if(!isSame) {
                  bool isConflict = false;
                  for(int n = 0; n < ruleNum; n++) {
                    if(rules[n].noun == rule.noun && rules[n].verb == rule.verb && rules[n].adj != rule.adj && rule.verb == IS) {
                      isConflict = true;
                      break;
                    }
                  }
                  if(!isConflict) {
                    rules[ruleNum++] = rule;
                  }
                }
              }
              ruleNum++;
            }
          }
        }
      }
    }
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