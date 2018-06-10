#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include <queue>

int MIN_KEY = -1;

class Treap {
 private:
  int key, priority, treapSize;
  Treap *left, *right;
  static int prioritySelection() {
    return std::rand();
  };
  static int size(const Treap *treap) {
    return (treap == nullptr) ? 0 : treap->treapSize;
  }
  static void updateSize(Treap *treap) {
    if (treap != nullptr) {
      treap->treapSize = size(treap->left) + size(treap->right) + 1;
    }
  }
 public:
  Treap(int key) : key(key), priority(prioritySelection()), left(nullptr), right(nullptr), treapSize(1) {}
  Treap(int key, int priority) : key(key), priority(priority), left(nullptr), right(nullptr), treapSize(1) {}
  const Treap *kthStatistics(int k) const {
    if (this == nullptr || k > treapSize) return nullptr;
    else if (size(left) == k) {
      return this;
    } else if (size(left) > k) {
      return left->kthStatistics(k);
    } else {
      return right->kthStatistics(k - size(left) - 1);
    }
  }
  int getKey() const {
    return key;
  }
  friend void split(Treap *root, int x, Treap *&left, Treap *&right);
  friend Treap *merge(Treap *left, Treap *right);
  friend Treap *insert(Treap *to, Treap *what);
  bool exists(int lookedForKey) const {
    if (this == nullptr) return false;
    else if (key == lookedForKey) {
      return true;
    } else if (key > lookedForKey) {
      return left->exists(lookedForKey);
    } else if (key < lookedForKey) {
      return right->exists(lookedForKey);
    }
  }
  int upperBounce(int lookedForKey) const {
    const Treap *currentVertex = this;
    int lastSuitableKey = MIN_KEY;
    while (currentVertex != nullptr) {
      if (lookedForKey < currentVertex->key) {
        lastSuitableKey = currentVertex->key;
        currentVertex = currentVertex->left;
      } else {
        currentVertex = currentVertex->right;
      }
    }
    return lastSuitableKey;
  }

  int lowerBounce(int lookedForKey) const {
    const Treap *currentVertex = this;
    int lastSuitableKey = MIN_KEY;
    while (currentVertex != nullptr) {
      if (lookedForKey > currentVertex->key) {
        lastSuitableKey = currentVertex->key;
        currentVertex = currentVertex->right;
      } else {
        currentVertex = currentVertex->left;
      }
    }
    return lastSuitableKey;
  }
};

void split(Treap *treap, int splitKey, Treap *&left, Treap *&right) {
  if (treap == nullptr) {
    left = nullptr;
    right = nullptr;
    return void();
  }
  if (treap->key < splitKey) {
    left = treap;
    split(treap->right, splitKey, left->right, right);
  } else {
    right = treap;
    split(treap->left, splitKey, left, right->left);
  }
  Treap::updateSize(left);
  Treap::updateSize(right);
}

Treap *merge(Treap *left, Treap *right) {
  if (left == nullptr || right == nullptr) {
    return left == nullptr ? right : left;
  }
  if (left->priority > right->priority) {
    left->right = merge(left->right, right);
    Treap::updateSize(left);
    return left;
  } else {
    right->left = merge(left, right->left);
    Treap::updateSize(right);
    return right;
  }
}

Treap *insert(Treap *to, Treap *what) {
  Treap *left, *right;
  split(to, what->key, left, right);
  return merge(merge(left, what), right);
}

Treap *deleteVertex(Treap *from, int key) {
  Treap *left, *right, *middle;
  split(from, key, left, right);
  split(right, key + 1, middle, right);
  return merge(left, right);
}

int main() {
  std::srand(std::time(0));
  std::string inputType;
  int inputValue;
  Treap *root = nullptr;
  std::queue < Treap * > verticesToDelete;
  while (std::cin >> inputType) {
    std::cin >> inputValue;
    if (inputType == "insert") {
      Treap *insertTreap = new Treap(inputValue);
      root = insert(root, insertTreap);
      verticesToDelete.push(insertTreap);
    } else if (inputType == "kth") {
      const Treap *kth = root->kthStatistics(inputValue - 1);
      std::cout << (kth != nullptr ? std::to_string(kth->getKey()) : "none") << '\n';
    } else if (inputType == "next") {
      int upperBounceVal = root->upperBounce(inputValue);
      std::cout << (upperBounceVal == -1 ? "none" : std::to_string(upperBounceVal)) << '\n';
    } else if (inputType == "prev") {
      int lowerBounceVal = root->lowerBounce(inputValue);
      std::cout << (lowerBounceVal == -1 ? "none" : std::to_string(lowerBounceVal)) << '\n';
    } else if (inputType == "delete") {
      root = deleteVertex(root, inputValue);
    } else if (inputType == "exists") {
      std::cout << (root->exists(inputValue) ? "true" : "false") << '\n';
    }
  }
  while (!verticesToDelete.empty()) {
    delete verticesToDelete.front();
    verticesToDelete.pop();
  }

}