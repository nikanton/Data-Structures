#include <vector>

using UI = unsigned long long;
using VectorUI = std::vector<UI>;

const UI numberOfElements = 1 << 24;

inline int log2(int x) {
  int log = -1;
  while (x > 0) {
    x >>= 1;
    ++log;
  }
  return log;
}

inline int pow2(int x) {
  return 1 << x;
}

inline UI upToNearestPowOf2(UI a) {
  UI pow = pow2(log2(a));
  return a > pow ? pow << 1 : pow;
}

class SegmentTree {
 private:
  UI elementsInTree; //we count here onle leafs
  UI lastSegment; //elementsInTree rounded up to nearest pow of 2
  VectorUI sumOnSegments;
  VectorUI addToSegment;
  size_t elementsOfVertex(int vertex) {
    return lastSegment / pow2(log2(vertex + 1));
  }
  inline int leftKid(const int &vertex) {
    return ((vertex + 1) << 1) - 1;
  }
  inline int rightKid(const int &vertex) {
    return (vertex + 1) << 1;
  }
  inline int parent(const int &vertex) {
    return (vertex - 1) >> 1;
  }
  inline bool isLeaf(const int &vertex) {
    return vertex >= lastSegment - 1;
  }
  void push(int vertex) {
    if (vertex >= lastSegment - 1) {
      return void();
    }
    addToSegment[leftKid(vertex)] += addToSegment[vertex];
    addToSegment[rightKid(vertex)] += addToSegment[vertex];
    addToSegment[vertex] = 0;
  }
  void subAdd(UI &from, UI &to, UI &addValue,
              UI processingFrom, UI processingTo, UI elementNumberInVector) {
    if (to < processingFrom || from > processingTo) {
      return void();
    }
    if (from <= processingFrom && to >= processingTo) {
      addToSegment[elementNumberInVector] += addValue;
      return void();
    }
    push(elementNumberInVector);
    subAdd(from, to, addValue, processingFrom,
           (processingFrom + processingTo) >> 1, (elementNumberInVector << 1) + 1);
    subAdd(from, to, addValue, ((processingFrom + processingTo) >> 1) + 1,
           processingTo, (elementNumberInVector << 1) + 2);
    if (!isLeaf(elementNumberInVector)) {
      sumOnSegments[elementNumberInVector] = sumOnSegments[leftKid(elementNumberInVector)] +
          elementsOfVertex(leftKid(elementNumberInVector)) * addToSegment[leftKid(elementNumberInVector)] +
          sumOnSegments[rightKid(elementNumberInVector)] +
          elementsOfVertex(rightKid(elementNumberInVector)) * addToSegment[rightKid(elementNumberInVector)];
    }
  }
  UI subSum(UI &from, UI &to, UI processingFrom, UI processingTo, UI elementNumberInVector) {
    if (to < processingFrom || from > processingTo) {
      return 0;
    }
    if (from <= processingFrom && to >= processingTo) {
      return sumOnSegments[elementNumberInVector] + addToSegment[elementNumberInVector] *
          elementsOfVertex(elementNumberInVector);
    }
    push(elementNumberInVector);
    UI ans = subSum(from, to, processingFrom, (processingFrom + processingTo) >> 1,
                    (elementNumberInVector << 1) + 1) +
        subSum(from, to, ((processingFrom + processingTo) >> 1) + 1, processingTo,
               (elementNumberInVector << 1) + 2);
    /*sumOnSegments[elementNumberInVector] = sumOnSegments[leftKid(elementNumberInVector)] +
        elementsOfVertex(leftKid(elementNumberInVector)) * addToSegment[leftKid(elementNumberInVector)] +
        sumOnSegments[rightKid(elementNumberInVector)] +
        elementsOfVertex(rightKid(elementNumberInVector)) * addToSegment[rightKid(elementNumberInVector)];*/
    return ans;
  }
  UI updateSum(int vertex) {
    if (isLeaf(vertex)) {
      return sumOnSegments[vertex];
    } else {
      sumOnSegments[vertex] = updateSum(leftKid(vertex)) + updateSum(rightKid(vertex));
      return sumOnSegments[vertex];
    }
  }
 public:
  SegmentTree(VectorUI &elements) {
    elementsInTree = elements.size();
    lastSegment = upToNearestPowOf2(elements.size());
    sumOnSegments = VectorUI(lastSegment * 2 - 1);
    addToSegment = VectorUI(lastSegment * 2 - 1);
    for (int i = 0, l = elements.size(); i < l; ++i) {
      sumOnSegments[lastSegment - 1 + i] = elements[i];
    }
    updateSum(0);
  }
  void add(UI &from, UI &to, UI &addValue) {
    subAdd(from, to, addValue, 0, lastSegment - 1, 0);
  }
  UI sum(UI &from, UI &to) {
    return subSum(from, to, 0, lastSegment - 1, 0);
  }
};
