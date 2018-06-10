template<class T>
struct Node {
  T value;
  Node<T> *next;
  T min;
  Node<T>(T value, Node<T> *next) : value(value), next(next) {
    if (next == NULL) min = value;
    else min = (next->min < value) ? next->min : value;
  }
};
template<class T>
class Stack {
 private:
  Node<T> *head;
  int elements;
 public:
  Stack<T>() {
    head = NULL;
    elements = 0;
  }
  ~Stack<T>() {
    clear();
  }
  bool isNotEmpty() {
    return (elements) ? true : false;
  }
  void push(T value);
  T pop();
  T back() {
    return head->value;
  }
  T min() {
    return head->min;
  }
  T size() {
    return elements;
  }
  void clear();
};
template<class T>
void Stack<T>::push(T value) {
  Node<T> *newNode = new Node<T>(value, head);
  head = newNode;
  ++elements;
}
template<class T>
T Stack<T>::pop() {
  Node<T> *oldNode = head;
  T value = head->value;
  head = head->next;
  delete oldNode;
  --elements;
  return value;
}
template<class T>
void Stack<T>::clear() {
  while (elements > 0) {
    Node<T> *oldNode = head;
    head = head->next;
    delete oldNode;
    --elements;
  }
}

template<class T>
class Queue {
 private:
  Stack<T> left, right;
  void balance();
 public:
  inline void enqueue(T value) {
    left.push(value);
  }
  T dequeue();
  T front();
  T min();
  int size() {
    return left.size() + right.size();
  }
  void clear() {
    left.clear();
    right.clear();
  }
  bool isNotEmpty() {
    return (size() == 0) ? false : true;
  }
};
template<class T>
T Queue<T>::front() {
  if (right.isNotEmpty()) return right.back();
  else {
    balance();
    return right.back();
  }
}
template<class T>
T Queue<T>::dequeue() {
  if (right.isNotEmpty()) return right.pop();
  else {
    balance();
    return right.pop();
  }
}
template<class T>
void Queue<T>::balance() {
  if (!right.isNotEmpty())
    while (left.isNotEmpty())
      right.push(left.pop());
}
template<class T>
T Queue<T>::min() {
  T min;
  if (left.isNotEmpty())
    if (right.isNotEmpty()) min = (left.min() < right.min()) ? left.min() : right.min();
    else min = left.min();
  else
    min = right.min();
  return min;
}