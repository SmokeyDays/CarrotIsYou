#pragma once

constexpr int NOUN_NUM = 16;
constexpr int VERB_NUM = 8;
constexpr int ADJ_NUM = 16;

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

inline CIYTypeGroup getGroupByType(CIYType type) {
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

struct CIYRule {
  CIYType noun, verb, adj;
};
