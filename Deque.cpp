template<class T>
struct Node {
  Node *next, *prev;
  T value;
  Node(T value, Node *prev, Node *next) : value(value), prev(prev), next(next) {}
};

template<class T>
class Deque {
 private:
  Node<T> *head, *tail;
  int elements;
 public:
  Deque() {
    head = NULL;
    tail = NULL;
    elements = 0;
  }
  ~Deque() {
    clear();
  }
  inline bool isNotEmpty() {
    return (elements == 0) ? false : true;
  }
  T front() {
    return head->value;
  }
  T back() {
    return tail->value;
  }
  inline int size() {
    return elements;
  }
  void clear();
  void pushFront(T value);
  void pushBack(T value);
  T popFront();
  T popBack();
};

template<class T>
void Deque<T>::clear() {
  Node<T> *oldNode;
  while (isNotEmpty()) {
    oldNode = head;
    head = head->next;
    delete oldNode;
    --elements;
  }
}
template<class T>
void Deque<T>::pushBack(T value) {
  if (isNotEmpty()) {
    Node<T> *newNode = new Node<T>(value, tail, NULL);
    tail->next = newNode;
    tail = newNode;
  } else {
    Node<T> *newNode = new Node<T>(value, NULL, NULL);
    tail = newNode;
    head = newNode;
  }
  ++elements;
}
template<class T>
void Deque<T>::pushFront(T value) {
  if (isNotEmpty()) {
    Node<T> *newNode = new Node<T>(value, NULL, head);
    head->prev = newNode;
    head = newNode;
  } else {
    Node<T> *newNode = new Node<T>(value, NULL, NULL);
    tail = newNode;
    head = newNode;
  }
  ++elements;
}
template<class T>
T Deque<T>::popFront() {
  Node<T> *oldNode = head;
  T value = head->value;
  --elements;
  if (isNotEmpty()) head = head->next;
  delete oldNode;
  return value;
}
template<class T>
T Deque<T>::popBack() {
  Node<T> *oldNode = tail;
  T value = tail->value;
  --elements;
  if (isNotEmpty()) tail = tail->prev;
  delete oldNode;
  return value;
}