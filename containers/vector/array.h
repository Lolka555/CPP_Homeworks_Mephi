#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <stdexcept>
#include <algorithm>

class Array {
private:
  std::ostream& Ostream_;
  int* data;
  size_t realSize;
  size_t capacity;

  void allocate(size_t newCapacity) {
    if (newCapacity > capacity) {
      int* newData = new int[newCapacity];
      for (size_t i = 0; i < realSize; ++i) {
        newData[i] = data[i];
      }
      delete[] data;
      data = newData;
      capacity = newCapacity;
    }
  }

public:
  Array(std::ostream& Ostream_): Ostream_(Ostream_), data(new int[2]),
                                 realSize(0), capacity(2) {
    Ostream_ << "Constructed. " << *this << std::endl;
  }

  friend std::ostream& operator<<(std::ostream& Ostream_, const Array& array) {
    Ostream_ << "Result Array's capacity is " << array.capacity << " and size is " << array.realSize;
    if (array.realSize > 0){
      Ostream_ << ", elements are: ";
    }
    for (size_t i = 0; i < array.realSize; ++i) {
      Ostream_ << array.data[i];
      if (i < array.realSize - 1) {
        Ostream_ << ", ";
      }
    }
    return Ostream_;
  }


  Array(size_t size, std::ostream& Ostream_, int defaultValue = 0)
      : Ostream_(Ostream_), realSize(size), capacity(size > 0 ? 2 * size :
                                                     2) {
    data = new int[capacity];
    for (size_t i = 0; i < realSize; ++i) {
      data[i] = defaultValue;
    }
    Ostream_ << "Constructed with default. " << *this << std::endl;
  }

    Array(const Array& other)
        : Ostream_(other.Ostream_)
        , data(new int[other.capacity])
        , realSize(other.realSize)
        , capacity(other.capacity) {
      std::copy(other.data, other.data + realSize, data);
      Ostream_ << "Constructed from another Array. " << *this << std::endl;
    }

  ~Array() {
    Ostream_ << "Destructed " << realSize << std::endl;
    delete[] data;
  }

  size_t Capacity() const {
    return capacity;
  }

  void PushBack(int value) {
    if (realSize == capacity) {
      allocate(capacity * 2);
    }
    data[realSize++] = value;
  }

  size_t Size() const {
    return realSize;
  }

  /*
  void Resize(size_t newSize) {
    if (newSize > 0) {
      if (newSize > capacity) {
        allocate(newSize);
      }
      realSize = newSize;
    }
  }
   */
    void Resize(size_t newSize) {
        allocate(newSize);
        realSize = newSize;
      }


  void Reserve(size_t newCapacity) {
      allocate(newCapacity);

  }

  void PopBack() {
    if (realSize > 0) {
      --realSize;
    }
  }

  int& operator[](const size_t& index) {
    return data[index];
  }

  const int& operator[](const size_t i) const {
    return data[i];
  }

  explicit operator bool() const {
    return realSize > 0;
  }

  Array& operator<<(const int& value) {
    PushBack(value);
    return *this;
  }

  Array& operator<<(const Array& other) {
    for (size_t i = 0; i < other.realSize; ++i) {
      PushBack(other.data[i]);
    }
    return *this;
  }

  bool operator<(const Array& it) const {
    for (size_t i = 0; i < std::min(realSize, it.realSize); ++i) {
      if (data[i] != it.data[i]) {
        return data[i] < it.data[i];
      }
    }
    return realSize < it.realSize;
  }

  bool operator>(const Array& it) const { return it < *this; }
  bool operator!=(const Array& it) const { return *this < it || it < *this; }
  bool operator==(const Array& it) const { return !(*this != it); }
  bool operator<=(const Array& it) const { return !(*this > it); }
  bool operator>=(const Array& it) const { return !(*this < it); }

};

#endif
