#pragma once

#include "MiniMalloc.h"
#include "Interfaces.h"

// class Vector {
// private:

// public:
//   int length;
//   int *data;
//   int chunkNum;
//   Vector()
//     : length(0), data(nullptr), chunkNum(0) {}
//   Vector(const Vector &B)
//     : length(B.length), chunkNum(B.chunkNum) {
//     if(&B == this || !length) {
//       return;
//     }
//     data = mallocInt(length);
//     for (int i = 0; i < length; i++) {
//       data[i] = B.data[i];
//     }
//   }
//   Vector(Vector &&B)
//     : length(B.length), chunkNum(B.chunkNum), data(B.data) {
      
//     if(&B == this) {
//       return;
//     }
//     B.data = nullptr;
//   }

//   ~Vector() {
//     if (data != nullptr) {
//       freeIntPtr(data);
//       data = nullptr;
//     }
//   }
//   Vector &operator=(const Vector &B) {
//     if(&B == this) {
//       return *this;
//     }
//     if (data != nullptr) {
//       freeIntPtr(data);
//       data = nullptr;
//     }
//     length = B.length;
//     chunkNum = B.chunkNum;
//     if (B.data == nullptr) {
//       return *this;
//     }
//     data = mallocInt(length);
//     for (int i = 0; i < length; i++) {
//       data[i] = B.data[i];
//     }
//     return *this;
//   }

//   Vector &operator=(Vector &&B) {
//     if(&B == this) {
//       return *this;
//     }
//     if (data != nullptr) {
//       freeIntPtr(data);
//       data = nullptr;
//     }
//     length = B.length;
//     chunkNum = B.chunkNum;
//     data = B.data;
//     B.data = nullptr;
//     return *this;
//   }

//   void push(int value) {
//     if (length % CHUNK_SIZE == 0) {
//       if (data != nullptr) {
//         // printf("pre len: %d\n", length);
//         int *newData = mallocInt((chunkNum + 1) * CHUNK_SIZE);
//         for (int i = 0; i < chunkNum * CHUNK_SIZE; i++) {
//           newData[i] = data[i];
//         }
//         chunkNum++;
//         freeIntPtr(data);
//         data = newData;
//         // printf("now len: %d\n", length);
//       } else {
//         data = mallocInt(CHUNK_SIZE);
//         chunkNum = 1;
//       }
//     }
//     data[length++] = value;
//   }

//   void push(const Vector &vec) {
//     if(&vec == this) {
//       return;
//     }
//     for (auto &&value : vec) {
//       push(value);
//     }
//   }

//   int size() const {
//     return length;
//   }

//   void clear() {
//     if (data != nullptr) {
//       freeIntPtr(data);
//       data = nullptr;
//     }
//     length = 0;
//     chunkNum = 0;
//   }

//   int& operator[](int index) {
//     return data[index];
//   }
//   int operator[](int index) const {
//     return data[index];
//   }

//   Vector operator+(const Vector &B) const {
//     if(&B == this) {
//       return *this;
//     }
//     Vector ret;
//     ret.push(*this);
//     ret.push(B);
//     return ret;
//   }

//   Vector getIntersection(const Vector &B) const {
//     Vector ret;
//     for (auto &&value : *this) {
//       for (auto &&value2 : B) {
//         if (value == value2) {
//           ret.push(value);
//           break;
//         }
//       }
//     }
//     return ret;
//   }

//   int has(int value) const {
//     for (int i = 0; i < length; i++) {
//       if (data[i] == value) {
//         return true;
//       }
//     }
//     return false;
//   }

//   // for range-based for loop
//   int *begin() { return data; }
//   int *end() { return data + length; }

//   const int *begin() const { return data; }
//   const int *end() const { return data + length; }
// };
