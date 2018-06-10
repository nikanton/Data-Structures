template<typename T>
class Vector {
 private:
  T *begin_;
  size_t size_, elements_;
  static const size_t BASE_ = 2;
 public:
  Vector() : size_(1), begin_(new T[1]), elements_(0) {}

  ~Vector() { delete[] begin_; }

  void push_back(T value) {
    if (elements_ < size_)
      begin_[elements_++] = value;
    else {
      T *new_begin = new T[size_ * BASE_];

      for (size_t i = 0; i < elements_; ++i)
        new_begin[i] = begin_[i];

      std::swap(new_begin, begin_);
      delete[] new_begin;
      size_ *= BASE_;

      begin_[elements_++] = value;
    }
  }

  T pop_back() {
    T ret = begin_[--elements_];

    if (elements_ <= size_ / BASE_) {
      T *new_begin = new T[size_ / BASE_];

      for (size_t i = 0; i < elements_; ++i)
        new_begin[i] = begin_[i];

      std::swap(new_begin, begin_);
      delete[] new_begin;
      size_ /= BASE_;
    }

    return ret;
  }

  T &back() { return begin_[elements_ - 1]; }

  const T &back() const { return begin_[elements_ - 1]; }

  size_t size() const { return elements_; }

  T &operator[](int n) { return begin_[n]; }

  const T &operator[](int n) const { return begin_[n]; }

  void clear() {
    size_ = 1;
    delete[] begin_;
    begin_ = new T[1];
    elements_ = 0;
  }
}