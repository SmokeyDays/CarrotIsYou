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
  #define KEY_ENTER 0xD
  #define KEY_BACK 0x71
  #define KEY_NEXT 0x70
#endif

extern void setDisplayMemory(int x, int y, unsigned int value);

extern bool keyEmpty();

extern int keyPop();

extern void sdlUpdate();

extern void clearDisplayMemory();