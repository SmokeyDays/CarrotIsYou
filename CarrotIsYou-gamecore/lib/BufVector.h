#pragma once

template <typename T, int N>
class BufVector {
private:
  T data[N];
  int length;

public:
  BufVector() : length(0) {}

  bool empty() const { return length == 0; }
  int size() const { return length; }

  T &operator[](int index) { return data[index]; }
  const T &operator[](int index) const { return data[index]; }

  T *begin() { return data; }
  T* end() { return data + length; }

  const T *begin() const { return data; }
  const T* end() const { return data + length; }

  void push(const T &value) {
    if(length >= N) {
      return;
    }
    data[length++] = value;
  }

  T pop() {
    if(length == 0) {
      return T();
    }
    return data[--length];
  }

  void clear() {
    length = 0;
  }
};
