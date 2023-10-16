#include "MiniMalloc.h"

const int MAX_MALLOC_INT = 8192;

int mallocIntArr[MAX_MALLOC_INT];
bool usedIntChunk[MAX_MALLOC_INT / 64];
int allocatedIntSize[MAX_MALLOC_INT / 64];

int *mallocInt(int size) {
  if (size % 64 != 0) {
    size += 64 - size % 64;
  }
  int chunkNum = size / 64;
  int chunkIndex = -1;
  for (int i = 0; i < MAX_MALLOC_INT / 64; i++) {
    for (int j = 0; j < chunkNum; j++) {
      if (usedIntChunk[i + j]) {
        break;
      }
      if (j == chunkNum - 1) {
        chunkIndex = i;
        break;
      }
    }
    if (chunkIndex != -1) {
      break;
    } 
  }
  if (chunkIndex == -1) {
    return nullptr;
  }
  for (int i = 0; i < chunkNum; i++) {
    usedIntChunk[chunkIndex + i] = true;
  }
  allocatedIntSize[chunkIndex] = size;
  int *ret = mallocIntArr + chunkIndex * 64 * sizeof(int);
  return ret;
}

void freeIntPtr(int *ptr) {
  // Assert: (ptr - mallocInt) % 64 == 0
  int chunkIndex = (ptr - mallocIntArr) / (64 * sizeof(int));
  int chunkNum = allocatedIntSize[chunkIndex] / 64;
  for (int i = 0; i < chunkNum; i++) {
    usedIntChunk[chunkIndex + i] = false;
  }
}

int getAllocatedIntSize(int *ptr) {
  // Assert: (ptr - mallocInt) % 64 == 0
  int chunkIndex = (ptr - mallocIntArr) / 64;
  return allocatedIntSize[chunkIndex];
}
