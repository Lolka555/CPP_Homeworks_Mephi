#include "tasks.h"

#include <cmath>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <complex>


int NOuter::NInner::DoSomething(int lhs, int rhs) {
    return lhs + rhs;
}

int NOuter::DoSomething(int lhs, int rhs) {
    return lhs - rhs;
}

int NOverload::ProcessTwoArgs(int lhs, int rhs) {
    return lhs + rhs;
}

char NOverload::ProcessTwoArgs(char lhs, char rhs) {
    return std::max(lhs, rhs);
}

int NOverload::ProcessTwoArgs(int lhs, char rhs) {
    return lhs - (int) rhs;
}

unsigned int NOverflow::WithOverflow(int lhs, int rhs) {
    return lhs + rhs;
}

uint64_t NOverflow::WithOverflow(int64_t lhs, int64_t rhs) {
    return lhs - rhs;
}

int NLoop::SumInRange(const int lhs, const int rhs) {
    int otv = 0;
    for(int i = lhs; i < rhs; i++) {
        otv += i;
    }
    return otv;
}

int NLoop::CountFixedBitsInRange(const int from, const int to, const int bitsCnt) {
    int otv = 0;
    for(int i = from; i < to; i++) {
        int bs = __builtin_popcount(i);
        if(bs == bitsCnt) {
            otv++;
        }
    }
    return otv;
}

double NMath::ComputeMathFormula(const double arg) {
    return std::abs((std::sin(arg) / 2 + std::cos(arg)) * (std::sin(arg) / 2 + std::cos(arg)) + std::tan(arg) * std::atan(arg));
}

bool NMath::IsPositive(int arg) {
    if(arg > 0) {
        return true;
    } else {
        return false;
    }
}

int NRecursion::CalculateFibonacci(const int arg) {
    if (arg <= 2)
        return 1;

    int prev = 1, curr = 1;

    for (int i = 3; i <= arg; ++i) {
        int next = prev + curr;
        prev = curr;
        curr = next;
    }

    return curr;
}
