#include <iostream>
#include <vector>
#include <cassert>

/*
 * Напишите шаблонный класс Deque, который представляет собой двустороннюю очередь и поддерживает
 * - вставку в начало и в конец в лучшем случае за константное время, а в худшем случае за линейное в зависимости от
 *  текущего количества элементов в деке;
 * - произвольный доступ по порядковому номеру к любым элементам дека за константное время
 * - удаление одного элемента из конца или из начала дека за константное время
 * Более подробно с интерфейсом класса Deque можно ознакомиться в вызывающем коде в функции main
 *
 * С учетом данных ограничений Deque может быть удобно реализовать с помощью Ring Buffer'а
 */


/*
Методы внутри main
Size()
Front() Back()
Clear()
PushBack() + PopBack()
PushFront() + PopFront()
Empty
*/

template<typename T>
class Deque {
private:
    std::vector<T> data;
    size_t frontIndex;
    size_t backIndex;
    size_t realSize;

    void allocate(size_t newCapacity) {
        std::vector<T> newData(newCapacity);
        for (size_t i = 0; i < realSize; ++i) {
            newData[i] = data[(frontIndex + i) % data.size()];
        }
        data.swap(newData);
        frontIndex = 0;
        backIndex = realSize;
    }

public:
    Deque(size_t newCapacity = 4) : data(newCapacity), frontIndex(0), backIndex(0), realSize(0) { }

    size_t Size() const {
        return realSize;
    }

    bool Empty() const {
        return realSize == 0;
    }


    const T& operator [](const size_t i) const {
        assert(i < realSize && "Index overflow");
        return data[(frontIndex + i) % data.size()];
    }

    T& operator [](const size_t i) {
        assert(i < realSize && "Index overflow");
        return data[(frontIndex + i) % data.size()];
    }

    void Clear() {
        frontIndex = 0;
        backIndex = 0;
        realSize = 0;
        data.clear();
        data.resize(4);
    }

    T& Front() {
        assert(!Empty() && "Deque pusto");
        return data[frontIndex];
    }

    T& Back() {
        assert(!Empty() && "Deque pusto");
        return data[(backIndex - 1 + data.size()) % data.size()];
    }

    void PushFront(const T& value) {
        if (realSize == data.size()) {
            allocate(data.size() * 2);
        }
        frontIndex = (frontIndex - 1 + data.size()) % data.size();
        data[frontIndex] = value;
        realSize += 1;
    }

    void PushBack(const T& value) {
        if (realSize == data.size()) {
            allocate(data.size() * 2);
        }
        data[backIndex] = value;
        backIndex = (backIndex + 1) % data.size();
        realSize += 1;
    }

    void PopBack() {
        if (Empty()) {
            return;
        }
        backIndex = (backIndex - 1 + data.size()) % data.size();
        realSize -= 1;
    }

    void PopFront() {
        assert(!Empty() && "Deque pusto");
        frontIndex = (frontIndex + 1) % data.size();
        realSize -= 1;
    }
};


int main() {
    Deque<int> deque;

    assert(deque.Size() == 0);
    assert(deque.Empty());

    deque.PushBack(1);
    // assert(deque[5]);
    assert(deque.Size() == 1);
    assert(!deque.Empty());
    assert(deque[0] == 1);
    assert(deque.Front() == 1);
    assert(deque.Back() == 1);

    deque.PopFront();
    assert(deque.Size() == 0);
    assert(deque.Empty());

    for (int i = 0; i < 20; ++i) {
        if (i % 2) {
            deque.PushBack(i);
        } else {
            deque.PushFront(i);
        }
    }

    for (size_t i = 0; i < deque.Size(); ++i) {
        std::cout << deque[i] << " ";
    }
    std::cout << std::endl;

    assert(deque.Size() == 20);

    const int beforeBack = deque[deque.Size() - 2];
    const int afterFront = deque[1];

    deque.PopBack();
    deque.PopFront();

    assert(deque.Back() == beforeBack);
    assert(deque.Front() == afterFront);

    std::string s;
    for (size_t i = 0; i < deque.Size(); ++i) {
        s += std::to_string(deque[i]) + " ";
    }

    for (size_t i = 0; i < deque.Size(); ++i) {
        deque.PushBack(deque.Front());
        deque.PopFront();
    }

    std::string s2;
    for (size_t i = 0; i < deque.Size(); ++i) {
        s2 += std::to_string(deque[i]) + " ";
    }

    assert(s == s2);

    assert(deque.Size() == 18);
    deque.Clear();
    assert(deque.Size() == 0);
    assert(deque.Empty());

    return 0;
}
