#pragma once

#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
  SimpleVector() : 
    data(nullptr),
    capacity(0),
    size(0) {}

  //SimpleVector(const SimpleVector& other) = delete;

  //void operator=(const SimpleVector& other) = delete;

  explicit SimpleVector(size_t size) :
    data(new T[size]),
    capacity(size),
    size(size) {}

  ~SimpleVector() {
    delete[] data;
  }

  T& operator[](size_t index) {
    return data[index];
  }

  const T& operator[](size_t index) const {
    return data[index];
  }

  T* begin() { return data; }
  T* end() { return data + size; }

  const T* begin() const { return data; }
  const T* end() const { return data + size; }

  size_t Size() const { 
    return size;
  }
  size_t Capacity() const {
    return capacity;
  }

  void PushBack(T value) {
    Resize();
    data[size++] = move(value); 
  }
  
private:
  T* data;
  size_t capacity;
  size_t size;

  void Resize() {
    if (capacity == size) {
      capacity = capacity == 0 ? 1 : capacity * 2;
      T* new_data = new T[capacity];
      move(begin(), end(), new_data);
      delete[] data;
      data = new_data;
    }
  }
};
