

#include <vector>
#include <iterator>
#include <algorithm>


template <typename T>
class FlattenedVector {

private:

  std::vector<size_t> prefixSums;
  std::vector<std::vector<T>>* data = nullptr;

  size_t findSubvectorIndex(size_t index) const {
    auto upperIt = std::upper_bound(prefixSums.begin(), prefixSums.end(), index);
    return static_cast<size_t>(std::distance(prefixSums.begin(), upperIt)) - 1;
  }

  size_t findInSubvectorIndex(size_t index, size_t outerIndex) const {
    return index - prefixSums[outerIndex];
  }

public:

  FlattenedVector(std::vector<std::vector<T>>& input) : data(&input) {
    prefixSums.reserve(input.size() + 1);
    prefixSums.push_back(0);
    for (const auto& vec : input) {
      prefixSums.push_back(prefixSums.back() + vec.size());
    }
  }

  class Iterator {

  private:
    const FlattenedVector* parent;
    size_t index;

  public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    Iterator(const FlattenedVector* parent_, size_t index_)
        : parent(parent_), index(index_) {}

    reference operator*() const {
      auto first = parent->findSubvectorIndex(index);
      auto second = parent->findInSubvectorIndex(index, first);
      return (*parent->data)[first][second];
    }

    reference operator[](difference_type offset) const{
      return *(*this + offset);
    }
    Iterator& operator++() {
      ++index;
      return *this;
    }
    Iterator operator++(int) {
      Iterator tmp = *this;
      ++index;
      return tmp;
    }

    Iterator& operator--() {
      --index;
      return *this;
    }

    Iterator operator--(int) {
      Iterator tmp = *this;
      --index;
      return tmp;
    }

    Iterator operator+(difference_type offset) const {
      return Iterator(parent, index + offset);
    }

    friend Iterator operator+(difference_type offset, const Iterator& it) {
      return Iterator(it.parent, it.index + offset);
    }

    Iterator operator-(difference_type offset) const {
      return Iterator(parent, index - offset);
    }

    friend Iterator operator-(difference_type offset, const Iterator& it) {
      return Iterator(it.parent, offset - it.index);
    }

    Iterator& operator+=(difference_type offset) {
      index += offset;
      return *this;
    }

    Iterator& operator-=(difference_type offset) {
      index -= offset;
      return *this;
    }

    difference_type operator-(const Iterator& other) const {
      return index - other.index;
    }

    bool operator<(const Iterator& other) const {
      return index < other.index;
    }

    bool operator>(const Iterator& other) const {
      return other < *this;
    }

    bool operator<=(const Iterator& other) const {
      return !(other < *this);
    }

    bool operator>=(const Iterator& other) const {
      return !(*this < other);
    }

    bool operator==(const Iterator& other) const {
      return (index == other.index);
    }
    bool operator!=(const Iterator& other) const {
      return (index != other.index);
    }

  };

  Iterator begin() {
    return Iterator(this, 0);
  }

  Iterator end() {
    return Iterator(this, prefixSums.back());
  }

};

