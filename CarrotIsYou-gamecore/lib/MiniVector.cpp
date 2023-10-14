#pragma once
#include "MiniMalloc.cpp"

class Vector {
private:
  int length;
  int *data;
  int chunkNum;
public:
  Vector() {
    length = 0;
    data = nullptr;
    chunkNum = 0;
  }
  ~Vector() {
    if (data != nullptr) {
      freeIntPtr(data);
    }
  }
  void push(int value) {
    if (length % 64 == 0) { 
      if (data != nullptr) {
        int *newData = nullptr;
        newData = mallocInt((chunkNum + 1) * 64);
        for (int i = 0; i < chunkNum * 64; i++) {
          newData[i] = data[i];
        }
        chunkNum++;
        freeIntPtr(data);
      } else {
        data = mallocInt(64);
      }
    }
    data[length++] = value;
  }
  int size() {
    return length;
  }
  void clear() {
    if (data != nullptr) {
      freeIntPtr(data);
    }
    length = 0;
    data = nullptr;
    chunkNum = 0;
  }
  int& operator[](int index) {
    return data[index];
  }
};