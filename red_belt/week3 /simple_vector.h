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
    data_(nullptr),
    capacity_(0),
    size_(0) {}

  explicit SimpleVector(size_t size) :
    data_(new T[size]),
    capacity_(size),
    size_(size) {}

  ~SimpleVector() {
    delete[] data_;
  }

  T& operator[](size_t index) {
    return data_[index];
  }

  const T& operator[](size_t index) const {
    return data_[index];
  }

  T* begin() { return data_; }
  T* end() { return data_ + size_; }

  const T* begin() const { return data_; }
  const T* end() const { return data_ + size_; }

  size_t Size() const { 
    return size_;
  }
  size_t Capacity() const {
    return capacity_;
  }

  void PushBack(const T& value) {
    Resize();
    data_[size_++] = value; 
  }

private:
  T* data_;
  size_t capacity_;
  size_t size_;

  void Resize() {
    if (capacity_ == size_) {
      capacity_ = capacity_ == 0 ? 1 : capacity_ * 2;
      T* new_data_ = new T[capacity_];
      copy(begin(), end(), new_data_);
      delete[] data_;
      data_ = new_data_;
    }
  }
};
