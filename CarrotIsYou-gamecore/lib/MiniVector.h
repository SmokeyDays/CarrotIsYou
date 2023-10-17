#pragma once

#include "MiniMalloc.h"

class Vector {
private:

public:
  int length;
  int *data;
  int chunkNum;
  Vector()
    : length(0), data(nullptr), chunkNum(0) {}

  ~Vector() {
    if (data != nullptr) {
      freeIntPtr(data);
    }
  }

  void push(int value) {
    if (length % CHUNK_SIZE == 0) {
      if (data != nullptr) {
        int *newData = nullptr;
        newData = mallocInt((chunkNum + 1) * CHUNK_SIZE);
        for (int i = 0; i < chunkNum * CHUNK_SIZE; i++) {
          newData[i] = data[i];
        }
        chunkNum++;
        freeIntPtr(data);
      } else {
        data = mallocInt(CHUNK_SIZE);
      }
    }
    data[length++] = value;
  }

  void push(const Vector &vec) {
    for (auto &&value : vec) {
      push(value);
    }
  }

  int size() const {
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
  int operator[](int index) const {
    return data[index];
  }

  Vector operator+(const Vector &B) const {
    Vector ret;
    ret.push(*this);
    ret.push(B);
    return ret;
  }

  Vector getIntersection(const Vector &B) const {
    Vector ret;
    for (auto &&value : *this) {
      for (auto &&value2 : B) {
        if (value == value2) {
          ret.push(value);
          break;
        }
      }
    }
    return ret;
  }

  bool has(int value) const {
    for (int i = 0; i < length; i++) {
      if (data[i] == value) {
        return true;
      }
    }
    return false;
  }

  // for range-based for loop
  int *begin() { return data; }
  int *end() { return data + length; }

  const int *begin() const { return data; }
  const int *end() const { return data + length; }
};
