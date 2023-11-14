#include "MiniMalloc.h"

const int MAX_MALLOC_INT = 8192;

int mallocIntArr[MAX_MALLOC_INT];
int usedIntChunk[MAX_MALLOC_INT / CHUNK_SIZE];
int allocatedIntSize[MAX_MALLOC_INT / CHUNK_SIZE];

int *mallocInt(int size) {
  // assert(size != 0);
  if (size % CHUNK_SIZE != 0) {
    size += CHUNK_SIZE - size % CHUNK_SIZE;
  }
  int chunkNum = size / CHUNK_SIZE;
  int chunkIndex = -1;
  for (int i = 0; i < MAX_MALLOC_INT / CHUNK_SIZE; i++) {
    for (int j = 0; j < chunkNum; j++) {
      if (usedIntChunk[i + j] || i + j >= MAX_MALLOC_INT / CHUNK_SIZE) {
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
  int *ret = mallocIntArr + chunkIndex * CHUNK_SIZE * sizeof(int);
  return ret;
}

void freeIntPtr(int *ptr) {
  // assert((ptr - mallocIntArr) % 64 == 0);
  int chunkIndex = (ptr - mallocIntArr) / (CHUNK_SIZE * sizeof(int));
  int chunkNum = allocatedIntSize[chunkIndex] / CHUNK_SIZE;
  for (int i = 0; i < chunkNum; i++) {
    if(!usedIntChunk[chunkIndex + i]) {
      // printf("%d\n", chunkIndex + i);
      // __debugbreak();
      // assert(usedIntChunk[chunkIndex + i]);
    }
    usedIntChunk[chunkIndex + i] = false;
  }
}

int getAllocatedIntSize(int *ptr) {
  // assert((ptr - mallocIntArr) % 64 == 0);
  int chunkIndex = (ptr - mallocIntArr) / CHUNK_SIZE;
  return allocatedIntSize[chunkIndex];
}

int getEmptyChunkNum() {
  int cnt = 0;
  for (int i = 0; i < MAX_MALLOC_INT / CHUNK_SIZE; ++i) {
    cnt += !usedIntChunk[i];
  }
  return cnt;
}


void *memcpy(void *dest, const void *src, unsigned int n) {
  for (unsigned int i = 0; i < n; i++)
  {
      ((char*)dest)[i] = ((char*)src)[i];
  }
  return dest;
}

void* memset(void* dest, int c, unsigned long n) {
  char* s = (char*)dest;
  for (unsigned int i = 0; i < n; ++i) {
    s[i] = c;
  }
  return dest;
}