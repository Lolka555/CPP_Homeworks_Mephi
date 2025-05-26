#pragma once
#include <vector>
#include <string>

namespace NPointers {
    void Increment(int*);
    int Multiply(int, int, bool*);
    int ScalarProduct(const int*, const int*, unsigned long long);
    int SizeOfMaximumSquareOfCrosses(const char*,
                                         int, int);
    long long* MultiplyToLongLong(int, int);
}

namespace NReferences {
    void MultiplyInplace(int&, int);
    int CompareArraysByAverage(const int*, long long unsigned, const
                               int*);
}
