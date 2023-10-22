#pragma once

const int CHUNK_SIZE = 16;

int *mallocInt(int size);
void freeIntPtr(int *ptr);
int getAllocatedIntSize(int *ptr);
int getEmptyChunkNum();

void *memcpy(void *dest, const void *src, unsigned int n);
void* memset(void* dest, int c, unsigned long n);