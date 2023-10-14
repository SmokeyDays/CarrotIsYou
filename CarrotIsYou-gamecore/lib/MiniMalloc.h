#pragma once
#include "MiniMalloc.cpp"

int *mallocInt(int size);
void freeIntPtr(int *ptr);
int getAllocatedIntSize(int *ptr);
