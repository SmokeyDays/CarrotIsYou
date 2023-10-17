#include "MiniMalloc.h"
#include<cstdio>
const int MAX_MALLOC_INT = 8192;

int mallocIntArr[MAX_MALLOC_INT];
bool usedIntChunk[MAX_MALLOC_INT / CHUNK_SIZE];
int allocatedIntSize[MAX_MALLOC_INT / CHUNK_SIZE];

int *mallocInt(int size) {
  if (size % CHUNK_SIZE != 0) {
    size += CHUNK_SIZE - size % CHUNK_SIZE;
  }
  int chunkNum = size / CHUNK_SIZE;
  int chunkIndex = -1;
  for (int i = 0; i < MAX_MALLOC_INT / CHUNK_SIZE; i++) {
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
  int cnt = 0;
  for (int i = 0; i < MAX_MALLOC_INT / CHUNK_SIZE; ++i) {
    cnt += usedIntChunk[chunkIndex + i];
  }
  allocatedIntSize[chunkIndex] = size;
  int *ret = mallocIntArr + chunkIndex * CHUNK_SIZE * sizeof(int);
  return ret;
}

void freeIntPtr(int *ptr) {
  // Assert: (ptr - mallocInt) % 64 == 0
  int chunkIndex = (ptr - mallocIntArr) / (CHUNK_SIZE * sizeof(int));
  int chunkNum = allocatedIntSize[chunkIndex] / CHUNK_SIZE;
  for (int i = 0; i < chunkNum; i++) {
    usedIntChunk[chunkIndex + i] = false;
  }
}

int getAllocatedIntSize(int *ptr) {
  // Assert: (ptr - mallocInt) % 64 == 0
  int chunkIndex = (ptr - mallocIntArr) / CHUNK_SIZE;
  return allocatedIntSize[chunkIndex];
}

void *memcpy(void *dest, const void *src, unsigned int n) {
    for (unsigned int i = 0; i < n; i++)
    {
        ((char*)dest)[i] = ((char*)src)[i];
    }
}