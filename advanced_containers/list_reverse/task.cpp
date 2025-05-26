#include "task.h"

void ReverseList(std::list<int>& l) {
  std::list<int> reversedList;
  for (auto it = l.rbegin(); it != l.rend(); ++it) {
    reversedList.push_back(*it);
  }
  l = reversedList;
}

