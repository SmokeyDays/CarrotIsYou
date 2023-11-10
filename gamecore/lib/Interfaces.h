#pragma once
#include "libdevice.h"
#define RISCV
// #define CARROT_ON_SDL
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
  #define KEY_ESC   0x1B   // release: 
#endif
#ifdef RISCV
  #define KEY_UP    0x75 // release: E0F075
  #define KEY_DOWN  0x72 // release: E0F072
  #define KEY_LEFT  0x6B // release: E0F06B
  #define KEY_RIGHT 0x74 // release: E0F074
  #define KEY_W     0x1D   // release: F01D
  #define KEY_S     0x1B   // release: F01B
  #define KEY_A     0x1C   // release: F01C
  #define KEY_D     0x23   // release: F023
  #define KEY_SPACE 0x29   // release: F029
  #define KEY_Z     0x1A   // release: F01A
  #define KEY_R     0x2D   // release: F02D
  #define KEY_ENTER 0x5A // release: E0F05A
  #define KEY_Q     0x15   // release: F015
  #define KEY_P     0x4D   // release: F04D
  #define KEY_ESC   0x76   // release: 
#endif

extern void sdlSetDisplayMemory(int x, int y, unsigned int value);

extern bool keyEmpty();
#ifdef CARROT_ON_SDL
extern int keyPop();
#endif
#ifdef RISCV
extern unsigned char keyPop();
#endif

extern void sdlUpdate();

extern void clearDisplayMemory();
