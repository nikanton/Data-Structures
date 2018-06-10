struct Node {
  Node *next, *prev;
  int value;

  Node(int value, Node *prev, Node *next) : value(value), prev(prev), next(next) {}
};

class List {
 private:
  Node *head;
 public:
  List() {
    head = nullptr;
  }
  ~List() {
    while (head != nullptr) del(head);
  }
  bool empty() {
    return (head == nullptr) ? true : false;
  }
  Node *head() {
    return head;
  }
  Node *tail();
  void insert(int value);
  void insert(int value, Node *position);
  void del(Node *element);
  Node *search(int value);

};

Node *List::tail() {
  if (head == nullptr) return nullptr;
  Node *ptr;
  while (ptr->next != nullptr) ptr = ptr->next;
  return ptr;
}
void List::insert(int value) {
  Node *newNode = new Node(value, nullptr, head);
  head->prev = newNode;
  head = newNode;
}
void List::insert(int value, Node *position) {
  if (position->next == nullptr) {
    Node *newNode = new Node(value, position, nullptr);
    position->next = newNode;
  } else {
    Node *newNode = new Node(value, position, position->next);
    position->next->prev = newNode;
    position->next = newNode;
  }
}
void List::del(Node *element) {
  if (element->prev != nullptr) element->prev->next = element->next;
  else head = element->next;
  if (element->next != nullptr) element->next->prev = element->prev;
  delete element;
}
Node *List::search(int value) {
  for (Node *ptr = head; head != nullptr; head = head->next)
    if (ptr->value == value)
      return ptr;
  return nullptr;
}