#pragma once

#include <stdexcept>
#include <array>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
  explicit StackVector(size_t a_size = 0) : size(a_size) {
    if (size > data.size())
      throw invalid_argument("");
  }

  T& operator[](size_t index) {
    if (index >= data.size())
      throw overflow_error("");
    return data[index];
  }
  const T& operator[](size_t index) const {
    if (index >= data.size())
      throw overflow_error("");
    return data[index];
  }

  typename array<T, N>::iterator begin() {
    return data.begin();
  }

  typename array<T, N>::iterator end() { 
    return data.begin() + size;
  }

  typename array<T, N>::const_iterator begin() const {
    return data.begin();
  }
  const typename array<T, N>::const_iterator end() const {
    return data.begin() + size;
  }

  size_t Size() const {
    return size;
  }

  size_t Capacity() const {
    return data.size();
  }

  void PushBack(const T& value) {
    if (size == data.size())
      throw overflow_error("");
    data[size++] = value;
  }

  T PopBack() {
    if (size == 0)
      throw underflow_error("");
    return data[--size];
  }

private:
  array<T, N> data;
  size_t size = 0;
};

