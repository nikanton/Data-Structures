template <class T> struct Node {
	T value;
	Node<T> *next;
	Node(T value, Node<T> *next) : value(value), next(next) {}
};

template <class T> class Queue {
private:
	Node<T> *head, *tail;
	int elements;
public:
	Queue() {
		head = NULL;
		tail = NULL;
		elements = 0;
	}
	~Queue() {
		clear();
	}
	inline bool isNotEmpty() {
		return (elements == 0) ? false : true;
	}
	void enqueue(T value);
	T dequeue();
	inline T front() {
		return head->value;
	}
	inline int size() {
		return elements;
	}
	void clear();
};
template <class T>
void Queue<T>::enqueue(T value) {
	Node<T> *newNode = new Node<T>(value, NULL);
	if (head == NULL) head = newNode;
	else tail->next = newNode;
	tail = newNode;
	++elements;
}
template <class T>
T Queue<T>::dequeue() {
	Node<T> *oldNode = head;
	head = head->next;
	T value = oldNode->value;
	delete oldNode;
	--elements;
	return value;
}
template <class T>
void Queue<T>::clear() {
	while (elements > 0) {
		Node<T> *oldNode = head;
		head = head->next;
		delete oldNode;
		--elements;
	}
}