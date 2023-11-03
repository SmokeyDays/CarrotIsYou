#pragma once
#include "Interfaces.h"

const int CHUNK_SIZE = 16;

int *mallocInt(int size);
void freeIntPtr(int *ptr);
int getAllocatedIntSize(int *ptr);
int getEmptyChunkNum();

#ifdef RISCV
extern "C" {
  void *memcpy(void *dest, const void *src, unsigned int n);
  void* memset(void* dest, int c, unsigned long n);
}
#endif
#ifdef CARROT_ON_SDL
void *memcpy(void *dest, const void *src, unsigned int n);
void* memset(void* dest, int c, unsigned long n);
#endif