#include "CarrotOS.h"

void CarrotOS::render() {
  for(int i = 0; i < 16; ++i) {
    for(int j = 0; j < 16; ++j) {
      int type = core.display[i][j];
      int mask = core.mask[i][j];
      for(int k = 0; k < 8; ++k) {
        int val = type % 16;
        for(int l = 0; l < 8; ++l) {
          setDisplayMemory(i * 16 + k, j * 16 + l, val);
        }
      }
    }
  }
}

void CarrotOS::run() {
  while(true) {
    switch(state) {
      case OS_INIT:
        
        break;
      case OS_GAME_START:

        break;
      case OS_GAME_RUNNING:
        if (!keyEmpty()) {
          int keyInput = keyPop();
          switch (keyInput) {
            case KEY_UP:
              core.move(0);
              break;
            case KEY_RIGHT:
              core.move(1);
              break;
            case KEY_DOWN:
              core.move(2);
              break;
            case KEY_LEFT:
              core.move(3);
              break;
            case KEY_KEEP:
              core.move(-1);
              break;
            case KEY_UNDO:
              core.undo();
              break;
            case KEY_RESTART:
              core.init(level);
              break;
            case KEY_BACK:
              if (level > 1) {
                level--;
              }
              core.init(level);
              break;
            case KEY_NEXT: 
              if (level < LEVEL_MAX) {
                level++;
              }
              core.init(level);
              break;
          }
          render();
        }
        break;
    }
  }
}