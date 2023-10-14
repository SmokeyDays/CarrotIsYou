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
  void push(Vector &vec) {
    for (int i = 0; i < vec.size(); i++) {
      push(vec[i]);
    }
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
  Vector operator+(Vector &B) {
    Vector ret;
    ret.push(*this);
    ret.push(B);
    return ret;
  }
  Vector getIntersection(Vector &B) {
    Vector ret;
    for (int i = 0; i < size(); i++) {
      for (int j = 0; j < B.size(); j++) {
        if (data[i] == B[j]) {
          ret.push(data[i]);
        }
      }
    }
    return ret;
  }
};