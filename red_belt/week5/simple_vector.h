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

  explicit SimpleVector(size_t size) :
    data(new T[size]),
    capacity(size),
    size(size) {}

  SimpleVector(const SimpleVector& other) :
    data(new T[other.capacity]),
    capacity(other.capacity),
    size(other.size) {
    copy(other.begin(), other.end(), begin());
  }

  ~SimpleVector() {
    delete[] data;
  }

  T& operator[](size_t index) {
    return data[index];
  }



  void operator=(const SimpleVector& other) {
    if (other.size <= capacity) {
      copy(other.begin(), other.end(), begin());
    } else {
      SimpleVector<T> tmp(other);
      swap(tmp.data, data);
      swap(tmp.size, size);
      swap(tmp.capacity, capacity);
    }
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

  void PushBack(const T& value) {
    Resize();
    data[size++] = value; 
  }

private:
  T* data;
  size_t capacity;
  size_t size;

  void Resize() {
    if (capacity == size) {
      capacity = capacity == 0 ? 1 : capacity * 2;
      T* new_data = new T[capacity];
      copy(begin(), end(), new_data);
      delete[] data;
      data = new_data;
    }
  }
};
