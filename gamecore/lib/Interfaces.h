#pragma once
#define RISCV
#ifdef CARROT_ON_SDL
  #include<cstdio>
  #define KEY_UP    0x40000052
  #define KEY_DOWN  0x40000051
  #define KEY_LEFT  0x40000050
  #define KEY_RIGHT 0x4000004F
  #define KEY_W     0x77
  #define KEY_S     0x73
  #define KEY_A     0x61
  #define KEY_D     0x64
  #define KEY_SPACE 0x20
  #define KEY_Z 0x7A
  #define KEY_R 0x72
  #define KEY_ENTER 0xD
  #define KEY_Q 0x71
  #define KEY_P 0x70
#endif
#ifdef RISCV

  #define KEY_UP    0x40000052
  #define KEY_DOWN  0x40000051
  #define KEY_LEFT  0x40000050
  #define KEY_RIGHT 0x4000004F
  #define KEY_W     0x77
  #define KEY_S     0x73
  #define KEY_A     0x61
  #define KEY_D     0x64
  #define KEY_SPACE 0x29
  #define KEY_Z 0x7A
  #define KEY_R 0x72
  #define KEY_ENTER 0xD
  #define KEY_Q 0x71
  #define KEY_P 0x70
#endif

extern void sdlSetDisplayMemory(int x, int y, unsigned int value);

extern bool keyEmpty();

extern int keyPop();

extern void sdlUpdate();

extern void clearDisplayMemory();
