#pragma once
#define CARROT_ON_SDL
#ifdef CARROT_ON_SDL
  #define KEY_UP    0x40000052
  #define KEY_DOWN  0x40000051
  #define KEY_LEFT  0x40000050
  #define KEY_RIGHT 0x4000004F
  #define KEY_KEEP 0x20
  #define KEY_UNDO 0x7A
  #define KEY_RESTART 0x72
  #define KEY_ENTER 6
  #define KEY_BACK 7
  #define KEY_NEXT 8
#endif

extern void setDisplayMemory(int x, int y, unsigned int value);

extern bool keyEmpty();

extern int keyPop();

extern void sdlUpdate();