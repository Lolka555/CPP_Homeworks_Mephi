#include "task.h"

using namespace std;

vector<int> HeapSort(const vector<int>& v) {
  priority_queue<int> bufferPq;
  for (int i: v){
    bufferPq.push(i);
  }
  vector<int> sortedVector(v.size());
  for (int i = (int)v.size() - 1; i >= 0; i--) {
    sortedVector[i] = bufferPq.top();
    bufferPq.pop();
  }
  return sortedVector;
}
