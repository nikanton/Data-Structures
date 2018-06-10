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
  inline bool isNotEmpty() { //�� ������, ��� ����� ���� ������� inline. ��������, ��� �������� ��������� �� ���������.
    return (elements) ? true : false;
  }
  void push(T value);
  T pop();
  inline T back() {
    return head->value;
  }
  inline T min() {
    return head->min;
  }
  inline int size() {
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