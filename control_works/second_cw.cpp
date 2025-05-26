#include <iostream>
#include <vector>
#include <optional>
#include <numeric>
#include <cassert>

/*
 * Нужно реализовать шаблонный класс WindowAverageIterator, который позволяет пробегать по диапазону значений
 * и вычислять среднее значение в окне заданного размера.
 * - В конструктор WindowAverageIterator передается итератор, с которого нужно начинать бежать и вычислять среднее,
 *  а также размер окна для вычисления среднего значения;
 * - Объекты WindowAverageIterator можно сравнивать с помощью оператора != с другими WindowAverageIterator'ами, а также с
 *  итераторами такого типа, который был передан в WindowAverageIterator при создании. Сравнение производится по позиции
 *  конца окна. Смысл такого сравнения в том, чтобы при сравнении с итераторами какого-то диапазона, по которому мы бежим
 *  и вычисляем среднее значение в окне, мы могли остановить итерации в тот момент, когда окно уперлось в end. Более понятно
 *  эта логика видна в функции main
 */

template <typename IterType>
class WindowAverageIterator {
    using ValueType = typename std::iterator_traits<IterType>::value_type;

private:
    IterType current_; 
    IterType first_;
    size_t windowSize_;
    ValueType windowSum_;

public:
    WindowAverageIterator(IterType current, size_t windowSize)
        : current_(current), first_(current), windowSize_(windowSize), windowSum_(0) {
        assert(windowSize_ > 0);

        windowSum_ += *current_;
        for (size_t i = 1; i < windowSize_; ++i) {
            ++current_;
            windowSum_ += *current_;
        }
    }

    WindowAverageIterator& operator++() {
        windowSum_ -= *first_;      
        ++first_;                  
        ++current_;                 
        windowSum_ += *current_;    
        return *this;
    }

    ValueType* operator->() {
        return &windowSum_;
    }

    bool operator!=(const WindowAverageIterator& other) const {
        return current_ != other.current_;
    }

    bool operator!=(const IterType& other) const {
        return current_ != other;
    }

    ValueType operator*() const {
        return windowSum_ / static_cast<float>(windowSize_);
    }

    ValueType Sum() const {
        return windowSum_;
    }
};

template <typename IterType>
WindowAverageIterator<IterType> MakeWindowAverageIterator(IterType iter, size_t windowSize) {
    return WindowAverageIterator<IterType>(iter, windowSize);
}

// Код, помогающий в отладке

class Foo {
public:
    Foo() = default;
    Foo(const float& number) : number_(number) {}

    void bar() const {
        std::cout << number_ << " from Foo. ";
    }

    Foo& operator += (const Foo& foo) {
        number_ += foo.number_;
        return *this;
    }

    Foo& operator -= (const Foo& foo) {
        number_ -= foo.number_;
        return *this;
    }

    Foo operator / (float value) const {
        return Foo(number_ / value);
    }
private:
    float number_;
};

int main() {
    const std::vector<const int> numbers = {1, 2, 3, 4, 5, 6, 7, 8};

    std::cout << "Numbers:\n";
    for (const int& number : numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;

    std::cout << "Window 1:\n";
    // Итерации должны остановиться, когда правый край окна дойдет до позиции numbers.end()
    std::string concatenatedWindow1;
    for (auto it = MakeWindowAverageIterator(numbers.begin(), 1); it != numbers.end(); ++it) {
        std::cout << *it << " ";
        concatenatedWindow1 += std::to_string(*it);
    }
    std::cout << std::endl;
    assert(concatenatedWindow1 == "12345678");

    std::cout << "Integer window 2:\n";
    std::string concatenatedWindow2;
    for (auto it = MakeWindowAverageIterator(numbers.begin(), 2); it != numbers.end(); ++it) {
        std::cout << *it << " ";
        concatenatedWindow2 += std::to_string(*it);
    }
    std::cout << std::endl;
    assert(concatenatedWindow2 == "1234567");

    {
        std::cout << "Float window 2:\n";
        std::vector<float> floats(numbers.begin(), numbers.end());
        std::string concatenatedWindow2Float;
        for (auto it = MakeWindowAverageIterator(floats.begin(), 2); it != floats.end(); ++it) {
            std::cout << *it << " ";
            concatenatedWindow2Float += std::to_string(*it);
        }
        std::cout << std::endl;
        assert(concatenatedWindow2Float == "1.5000002.5000003.5000004.5000005.5000006.5000007.500000");
    }

    std::cout << "Window 3:\n";
    for (auto it = MakeWindowAverageIterator(numbers.begin(), 3); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    {
        std::cout << "Foo window 4:\n";
        std::vector<Foo> foos = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        for (auto it = MakeWindowAverageIterator(foos.begin(), 4); it != foos.end(); ++it) {
            it->bar();
        }
        std::cout << std::endl;
    }

    {
        std::cout << "Sum of windows:\n";
        // Нужно обернуть end в тип WindowAverageIterator, чтобы шаблон std::accumulate мог вывести единый тип для итератора
        const int sum = std::accumulate(MakeWindowAverageIterator(numbers.begin(), 3), MakeWindowAverageIterator(numbers.end(), 1), 0);
        std::cout << sum << std::endl;
        assert(sum == 27);
    }
}
