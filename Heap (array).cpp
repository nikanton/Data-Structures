template<class T>
class Heap {
 private:
  T *elements;
  int sizeOfElementsArray;
  int numberOfElements;
  void increaseSize() {
    T *newArray = new T[sizeOfElementsArray * 2];
    for (int i = 0; i < numberOfElements; ++i) newArray[i] = elements[i];
    delete[] elements;
    elements = newArray;
    sizeOfElementsArray *= 2;
  }
  void decreaseSize() {
    T *newArray = new T[sizeOfElementsArray / 2];
    for (int i = 0; i < numberOfElements; ++i) newArray[i] = elements[i];
    delete[] elements;
    elements = newArray;
    sizeOfElementsArray /= 2;
  }
  void siftUp() {
    int position = numberOfElements - 1;
    while ((position + 1) / 2 - 1 >= 0)
      if (elements[(position + 1) / 2 - 1] > elements[position]) {
        std::swap(elements[(position + 1) / 2 - 1], elements[position]);
        position = (position + 1) / 2 - 1;
      } else break;
  }
  void siftDown() {
    int position = 0;
    int min;
    while ((position + 1) * 2 - 1 < numberOfElements) {
      if ((position + 1) * 2 < numberOfElements)
        min =
            (elements[(position + 1) * 2] < elements[(position + 1) * 2 - 1]) ? (position + 1) * 2 : (position + 1) * 2
                - 1;
      else min = (position + 1) * 2 - 1;
      if (elements[position] > elements[min]) {
        std::swap(elements[position], elements[min]);
        position = min;
      } else break;
    }
  }
 public:
  Heap() {
    sizeOfElementsArray = 1;
    elements = new T[sizeOfElementsArray];
    numberOfElements = 0;
  }
  ~Heap() {
    delete[] elements;
  }
  T extractMin();
  void insert(T value);
  void clear();
  inline T getMin() {
    return elements[0];
  }
  inline int size() {
    return numberOfElements;
  }
  inline bool isNotEmpty() {
    return (numberOfElements == 0) ? false : true;
  }
};
template<class T>
void Heap<T>::insert(T value) {
  if (numberOfElements == sizeOfElementsArray) increaseSize();
  elements[numberOfElements] = value;
  ++numberOfElements;
  siftUp();
}
template<class T>
T Heap<T>::extractMin() {
  T value = elements[0];
  --numberOfElements;
  elements[0] = elements[numberOfElements];
  if (numberOfElements <= sizeOfElementsArray / 2 && numberOfElements > 0) decreaseSize();
  siftDown();
  return value;
}

template<class T>
void Heap<T>::clear() {
  delete[] elements;
  elements = new T[1];
  sizeOfElementsArray = 1;
  numberOfElements = 0;
}