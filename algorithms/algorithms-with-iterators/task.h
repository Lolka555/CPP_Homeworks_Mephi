#include <cstdlib>
#include <iterator>
#include <cstdint>


template<class InputIt, class OutputIt, class UnaryOperation>
void Transform(InputIt firstIn, InputIt lastIn, OutputIt firstOut, UnaryOperation op) {
    for(auto iter=firstIn; iter != lastIn; ++iter){
        *firstOut = op(*iter);
        firstOut++; 
    }
}


template<class BidirIt, class UnaryPredicate>
void Partition(BidirIt first, BidirIt last, UnaryPredicate p) {
    auto left = first;
    for(auto iter = first; iter != last; ++iter) {
        if(p(*iter)){
            auto temp = *left;
            *left = *iter;
            *iter = temp;
            ++left;
        }
    }
}

template<class InputIt1, class InputIt2, class OutputIt>
void Merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt firstOut) {
    while (first1 != last1 && first2 != last2) {
        if (*first1 <= *first2) {
            *firstOut = *first1;
            ++first1;
        } else {
            *firstOut = *first2;
            ++first2;
        }
        ++firstOut;
    }
    while (first1 != last1) {
        *firstOut = *first1;
        ++first1;
        ++firstOut;
    }
    while (first2 != last2) {
        *firstOut = *first2;
        ++first2;
        ++firstOut;
    }
}


class FibonacciRange {
private:
    size_t cnt;

public:
    class Iterator {
        friend class FibonacciRange;
    
    private:
        size_t last;
        size_t now_num;
        size_t before_num;

    public:
        using value_type = uint64_t;
        using difference_type = ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category = std::input_iterator_tag;

        Iterator(size_t index): last(index), now_num(1), before_num(1){
            for(size_t i = 0; i < last; i++){
                size_t tmp = now_num;
                now_num += before_num;
                before_num = tmp;
            }
        }

        value_type operator *() const {
            return now_num;
        }

        Iterator& operator ++() {
            ++last;
            size_t tmp = now_num;
            now_num += before_num;
            before_num= tmp;
            return *this;
        }

        Iterator operator ++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator ==(const Iterator& rhs) const {
            return (now_num == rhs.now_num);
        }

        bool operator <(const Iterator& rhs) const {
            return (now_num < rhs.now_num);
        }
    };

    FibonacciRange(size_t amount) {
        cnt = amount;
    }

    Iterator begin() const {
        return Iterator(0);
    }

    Iterator end() const {
        return Iterator(cnt);
    }

    size_t size() const {
        return cnt;
    }
};
