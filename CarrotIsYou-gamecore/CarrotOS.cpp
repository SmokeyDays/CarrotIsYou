#include "CarrotOS.h"

void CarrotOS::render() {
  for(int i = 0; i < 16; ++i) {
    for(int j = 0; j < 16; ++j) {
      int type = core.display[i][j];
      int mask = core.mask[i][j];
      if(type != EMPTY) {
        for(int k = 0; k < 8; ++k) {
          unsigned int val = 0xEEEEEEEE;
          // if(type == CARROT) {
          //   val = 0xEEEEEEE0 + k;
          // } else if (type == IS) {
          //   val = 0xE0E0E0E0 + k;
          // } else {
          //   val = type % 16;
          //   val = val << 4 | val;
          //   val = val << 8 | val;
          //   val = val << 16 | val;
          // }
          #ifdef CARROT_ON_SDL
            setDisplayMemory(i * 8 + k, j, val);
          #endif
        }
      } else {
        #ifdef CARROT_ON_SDL
        for(int k = 0; k < 8; ++k) {
          setDisplayMemory(i * 8 + k, j, 0);
        }
        #endif
      }
    }
  }
#ifdef CARROT_ON_SDL
  sdlUpdate();
#endif
}

void CarrotOS::run() {
  core.init(level);
  render();
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