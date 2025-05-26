#include "task.h"

char* concat(const char* lhs, const char* rhs) {
  int lhsLength = 0, rhsLength = 0;
  while (lhs[lhsLength] != '\0') {
    lhsLength++;
  }
  while (rhs[rhsLength] != '\0') {
    rhsLength++;
  }
  char* newString = new char[lhsLength + rhsLength + 1];
  for (int i = 0; i < lhsLength; i++) {
    newString[i] = lhs[i];
  }
  for (int i = 0; i < rhsLength; i++) {
    newString[lhsLength + i] = rhs[i];
  }
  newString[lhsLength + rhsLength] = '\0';

  return newString;
}
