#pragma once

#include <iostream>
#include <stdexcept>
#include <algorithm>

template<typename T>
class Array {
private:
  std::ostream& ostream;
  T* data;
  size_t realSize;
  size_t capacity;

  void allocate(size_t newCapacity) {
    if (newCapacity > capacity) {
      T* newData = new T[newCapacity];
      for (size_t i = 0; i < realSize; ++i) {
        newData[i] = data[i];
      }
      delete[] data;
      data = newData;
      capacity = newCapacity;
    }
  }

public:

    T* begin() {
      return data;
    }

    T* end() {
      return data + realSize;
    }

    const T* begin() const {
      return data;
    }

    const T* end() const {
      return data + realSize;
    }


  Array(std::ostream& ostream): ostream(ostream), data(new T[2]),
  realSize(0), capacity(2) {
    ostream << "Constructed. " << *this << std::endl;
  }

  Array(const Array<T>& array): ostream(array.ostream),
                                data(new T[array.capacity]),
                                realSize(array.realSize),
                                capacity(array.capacity) {
    std::copy(array.data, array.data + realSize, data);
    ostream << "Constructed from another Array. " << *this << std::endl;
  }


  Array(size_t size, std::ostream& ostream = std::cout, T defaultValue = T())
      : ostream(ostream), data(new T[size]), realSize(size), capacity(size) {
    std::fill(data, data + size, defaultValue);
  }

  ~Array() {
    ostream << "Destructed " << realSize << std::endl;
    delete[] data;
  }

  size_t Size() const {
    return realSize;
  }

  size_t Capacity() const {
    return capacity;
  }

  void Reserve(size_t newCapacity) {
    allocate(newCapacity);
  }

  void Resize(size_t newSize) {
    allocate(newSize);
    realSize = newSize;
  }

  void PushBack(T value = 0) {
    if (realSize == capacity) {
      allocate(capacity * 2);
    }
    data[realSize++] = value;
  }

  void PopBack() {
    if (realSize > 0) {
      --realSize;
    }
  }

  const T& operator [](const size_t i) const {
    return data[i];
  }

  T& operator [](const size_t i) {
    return data[i];
  }

  explicit operator bool() const {
    return realSize > 0;
  }

  bool operator <(const Array<T>& it) const {
    size_t minSize = std::min(realSize, it.realSize);
    for (size_t i = 0; i < minSize; ++i) {
      if (data[i] < it.data[i]) {
        return true;
      } else if (data[i] > it.data[i]) {
        return false;
      }
    }
    return realSize < it.realSize;
  }

  bool operator >(const Array<T>& it) const {
    return it < *this;
  }

  bool operator !=(const Array<T>& it) const {
    return *this < it || it < *this;
  }

  bool operator ==(const Array<T>& it) const {
    return !(*this != it);
  }

  bool operator <=(const Array<T>& it) const {
    return !(*this > it);
  }

  bool operator >=(const Array<T>& it) const {
    return !(*this < it);
  }

  Array<T>& operator <<(const T& value) {
    PushBack(value);
    return *this;
  }

  Array<T>& operator <<(const Array<T>& it) {
    for (size_t i = 0; i < it.realSize; ++i) {
      PushBack(it.data[i]);
    }
    return *this;
  }

  bool Insert(size_t pos, const T& value) {
    if (pos > realSize) {
      return false;
    }
    if (realSize == capacity) {
      allocate(capacity * 2);
    }
    for (size_t i = realSize; i > pos; --i) {
      data[i] = data[i - 1];
    }
    data[pos] = value;
    ++realSize;
    return true;
  }

  bool Erase(size_t pos) {
    if (pos >= realSize){
      return false;
    }
    for (size_t i = pos; i < realSize - 1; ++i) {
      data[i] = data[i + 1];
    }
    --realSize;
    return true;
  }

};

template<typename T>
std::ostream& operator <<(std::ostream& ostream, const Array<T>& array) {
  ostream << "Result Array's capacity is " << array.Capacity()
          << " and size is " << array.Size();
  if (array.Size() > 0){
    ostream << ", elements are: ";
  }
  for (size_t i = 0; i < array.Size(); ++i) {
    ostream << array[i];
    if (i < array.Size() - 1) {
      ostream << ", ";
    }
  }
  return ostream;


}
