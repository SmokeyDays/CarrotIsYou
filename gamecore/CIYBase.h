#pragma once
#include "./lib/MiniMalloc.h"

const int WIDTH_MAX = 16;
const int HEIGHT_MAX = 16;

const int NOUN_NUM = 16;
const int VERB_NUM = 8;
const int ADJ_NUM = 16;

const int DIRECTION[4][2] = {
  {-1, 0},
  {0, 1},
  {1, 0},
  {0, -1}
};

// type_noun: 0: Carrot, 1: Flag, 2: Wall, 3: Rock, 4: Water, 5: Lava, 6: Ice, 7: Heart, 8: Witch, 9: Door, 10: Key, 11: Box, 12: Star, 13: Skull, 14: Ghost, 15: Bug
// type_verb: 16: Is, 17: Has, 18: And
// type_adj: 24: You, 25: Win, 26: Push, 27: Stop, 28: Melt, 29: Sink, 30: Hot, 31: Defeat, 32: Open, 33: Shut, 34: Weak, 35: Move, 36: Float, 37: Text, 38: Pull, 39: Tele
// type_noun_text: 40: Carrot, 41: Flag, 42: Wall, 43: Rock, 44: Water, 45: Lava, 46: Ice, 47: Heart, 48: Witch, 49: Door, 50: Key, 51: Box, 52: Star, 53: Skull, 54: Ghost, 55: Bug

// Be Careful:
// Defeat, Hot, Melt, Sink, Open, Shut, Win, Tele only effect objects that are atSameFloat;

enum CIYType {
  CARROT = 0, FLAG, WALL, ROCK, WATER, LAVA, ICE, HEART, WITCH, DOOR, KEY, BOX, STAR, SKULL, GHOST, BUG,
  IS = 16, HAS, AND, EMPTY, ILLEGAL, TO_WIN, GRAY, LEGAL,
  YOU = 24, WIN, PUSH, STOP, MELT, SINK, HOT, DEFEAT, OPEN, SHUT, WEAK, MOVE, FLOAT, TEXT, PULL, TELE,
  CARROT_TEXT = 40, FLAG_TEXT, WALL_TEXT, ROCK_TEXT, WATER_TEXT, LAVA_TEXT, ICE_TEXT, HEART_TEXT, WITCH_TEXT, DOOR_TEXT, KEY_TEXT, BOX_TEXT, STAR_TEXT, SKULL_TEXT, GHOST_TEXT, BUG_TEXT
};

enum CIYTypeGroup {
  NOUN = 0, VERB, ADJ, NOUN_TEXT, DISPLAY_ILLEGAL
};

inline CIYTypeGroup getGroupByType(CIYType type) {
  if (type == EMPTY) {
    return NOUN;
  } else if (type == ILLEGAL) {
    return DISPLAY_ILLEGAL;
  } else if (type < 16) {
    return NOUN;
  } else if (type < 24) {
    return VERB;
  } else if (type < 40) {
    return ADJ;
  } else {
    return NOUN_TEXT;
  }
}

inline bool isText(CIYType type) {
  return type != EMPTY && type >= IS;
}

struct CIYObject {
  unsigned short VALUE;
  CIYObject() {
    VALUE = 0;
  }
  CIYObject(short v) {
    VALUE = v;
  } 
  CIYObject(int x, int y, int direction, int type) {
    VALUE = (x & 0xF) | ((y & 0xF) << 4) | ((direction & 0x3) << 8) | ((type & 0x3F) << 10);
  }
  int x() const {
    return VALUE & 0xF;
  }
  int y() const {
    return (VALUE >> 4) & 0xF;
  }
  int direction() const {
    return (VALUE >> 8) & 0x3;
  }
  CIYType type() const {
    return (CIYType)((VALUE >> 10) & 0x3F);
  }
  void setX(int x) {
    VALUE = (VALUE & 0xFFF0) | (x & 0xF);
  }
  void setY(int y) {
    VALUE = (VALUE & 0xFF0F) | ((y & 0xF) << 4);
  }
  void setDirection(int direction) {
    VALUE = (VALUE & 0xFCFF) | ((direction & 0x3) << 8);
  }
  void setType(CIYType type) {
    VALUE = (VALUE & 0x03FF) | ((type & 0x3F) << 10);
  }
};

struct CIYRule {
  unsigned short VALUE;
  CIYRule() {
    VALUE = 0;
  }
  CIYRule(CIYType subject, CIYType verb, CIYType object) {
    VALUE = (subject & 0x3F) | ((verb & 0x1) << 6) | ((object & 0x3F) << 7);
  }
  CIYType subject() const {
    return (CIYType)(VALUE & 0x3F);
  }
  CIYType verb() const {
    return (CIYType)(16 + ((VALUE >> 6) & 1));
  }
  CIYType object() const {
    return (CIYType)((VALUE >> 7) & 0x3F);
  }
};