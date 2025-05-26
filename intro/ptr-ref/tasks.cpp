#include "tasks.h"

#include <cmath>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <complex>
#include <limits>

/*
В этом задании необходимо реализовать следующие функции:

Increment - принимает указатель на целое число и увеличивает это число на 1
Multiply - принимает 2 целых числа и указатель на флаг для возвращения ошибки.
В случае переполнения при перемножении должна выставить значение флага в true, иначе - false и вернуть результат умножения

ScalarProduct - принимает на вход 2 массива целых чисел и их размер, возвращает результат скалярного произведения входных массивов
SizeOfMaximumSquareOfCrosses - принимает на вход двумерный массив char и его размерности.
Возвращает размер максимальной квадратной матрицы из символов '+'

MultiplyToLongLong - принимает два целых числа и возвращает указатель на длинное целое число, которое является произведением аргументов
MultiplyInplace - принимает ссылку на целое число и вторым аргументом ещё одно целое число. Возвращает в первом аргументе их произведение
CompareArraysByAverage - принимает на вход массив целых чисел и его размер, а третьим параметром - массив фиксированного размера.
Возвращает -1, если среднее значение в первом массиве меньше, чем во втором; 0 - если равно; 1 - когда среднее значение в первом массиве больше,
чем во втором
*/


void NPointers::Increment(int* n){
     *n = *n + 1;
}

int NPointers::Multiply(int a, int b, bool* overflowFlag) {
  *overflowFlag = false;

  if (a > 0 && b > 0 && a > std::numeric_limits<int>::max() / b) {
    *overflowFlag = true;
    return 0;
  }
  else if (a < 0 && b < 0 && a < std::numeric_limits<int>::max() / b) {
    *overflowFlag = true;
    return 0;
  }
  else if ((a > 0 && b < 0 && b < std::numeric_limits<int>::min() / a) ||
           (a < 0 && b > 0 && a < std::numeric_limits<int>::min() / b)) {
    *overflowFlag = true;
    return 0;
  }
  return a * b;
}

int NPointers::ScalarProduct(const int* a, const int* b, unsigned long long m){
  int otv = 0;
  for(unsigned long long i = 0; i < m; i++){
    otv += a[i] * b[i];
  }
  return otv;
}

int NPointers::SizeOfMaximumSquareOfCrosses(const char* input, int n, int m) {
    std::vector<std::vector<char>> a(n, std::vector<char>(m));

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        a[i][j] = input[i * m + j];
      }
    }

    std::vector<std::vector<int>> dp(n, std::vector<int>(m, 0));
    int maxSize = 0;

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (a[i][j] == '+') {
          if (i == 0 || j == 0) {
            dp[i][j] = 1;
          } else {
            dp[i][j] = std::min(std::min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1]
                                                                        [j - 1])
                       + 1;
          }
          maxSize = std::max(maxSize, dp[i][j]);
        }
      }
    }

    return maxSize;
  }


long long* NPointers::MultiplyToLongLong(int a, int b) {
  long long* result = new long long;
  *result = static_cast<long long>(a) * static_cast<long long>(b);
  return result;
}

void NReferences::MultiplyInplace(int& a, int b) {
  a *= b;
}

/*
CompareArraysByAverage - принимает на вход массив целых чисел и его размер, а третьим параметром - массив фиксированного размера.
Возвращает -1, если среднее значение в первом массиве меньше, чем во втором; 0 - если равно; 1 - когда среднее значение в первом массиве больше,
чем во втором
*/

int NReferences::CompareArraysByAverage(const int* array1, long long unsigned
                                                               size1, const int*
                                            array2) {
  long long sum1 = 0;
  long long sum2 = 0;
  long long unsigned size2 = 5;
  for (long long unsigned i = 0; i < size1; ++i) {
    sum1 += array1[i];
  }
  for (long long unsigned i = 0; i < size2; ++i) {
    sum2 += array2[i];
  }


  if (sum1 * size2 < sum2 * size1) {
    return -1;
  } else if (sum1 * size2 > sum2 * size1) {
    return 1;
  } else {
    return 0;
  }
}




























