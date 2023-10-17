#pragma once
#define CARROT_ON_SDL
#ifdef CARROT_ON_SDL
  #define KEY_UP 0x40000052
  #define KEY_DOWN 0x40000051
  #define KEY_LEFT 0x40000050
  #define KEY_RIGHT 0x4000004F
  #define KEY_KEEP 9
  #define KEY_UNDO 4
  #define KEY_RESTART 5
  #define KEY_ENTER 6
  #define KEY_BACK 7
  #define KEY_NEXT 8
#endif

extern int setDisplayMemory(int x, int y, char value);

extern int keyEmpty();

extern int keyPop();