#include <iostream>

using namespace std;

template<typename T>
inline T gcd(T a, T b) {
  return b ? gcd(b, a % b) : a;
}

class RationalDivisionByZero {

};

class Rational {
 private:
  long long p;
  long long q;

  void reduce() {
    int gcdPQ = gcd(p < 0 ? -p : p, q < 0 ? -q : q);
    p /= gcdPQ;
    q /= gcdPQ;
    if (q < 0) {
      q *= -1;
      p *= -1;
    }
  }

 public:
  Rational() : p(), q() {}
  Rational(int p, int q) : p(p), q(q) { reduce(); }
  Rational(int p) : p(p), q(1) {}
  bool operator==(const Rational &number) const {
    return p == number.p && q == number.q;
  }
  bool operator!=(const Rational &number) const {
    return !(p == number.p && q == number.q);
  }
  bool operator<(const Rational &number) const {
    return p * number.q < q * number.p;
  }
  bool operator>(const Rational &number) const {
    return p * number.q > q * number.p;
  }
  bool operator<=(const Rational &number) const {
    return p * number.q <= q * number.p;
  }
  bool operator>=(const Rational &number) const {
    return p * number.q >= q * number.p;
  }
  const Rational operator-() const {
    Rational res = *this;
    res.p *= -1;
    return res;
  }
  const Rational operator+() const {
    return *this;
  }
  Rational &operator+=(const Rational &number) {
    int lcm = q * number.q / gcd(q, number.q);
    p = p * (lcm / q) + number.p * (lcm / number.q);
    q = lcm;
    reduce();
    return *this;
  }
  Rational &operator-=(const Rational &number) {
    int lcm = q * number.q / gcd(q, number.q);
    p = p * (lcm / q) - number.p * (lcm / number.q);
    q = lcm;
    reduce();
    return *this;
  }
  Rational &operator*=(const Rational &number) {
    p = p * number.p;
    q = q * number.q;
    reduce();
    return *this;
  }
  Rational &operator/=(const Rational &number) {
    if (number.p == 0) throw RationalDivisionByZero();
    p = p * number.q;
    q = q * number.p;
    reduce();
    return *this;
  }
  const Rational operator++(int) {
    const Rational res = *this;
    p += q;
    return res;
  }
  Rational &operator++() {
    p += q;
    return *this;
  }
  const Rational operator--(int) {
    const Rational res = *this;
    p -= q;
    return res;
  }
  Rational &operator--() {
    p -= q;
    return *this;
  }
  const long long getNumerator() const {
    return p;
  }
  const long long getDenominator() const {
    return q;
  }
  friend std::istream &operator>>(std::istream &, Rational &);
  friend std::ostream &operator<<(std::ostream &, const Rational &);
};

std::istream &operator>>(std::istream &is, Rational &number) {
  char input[256];
  is >> input;
  int i = 0;
  number.p = 0;
  bool minus = false;
  if (input[i] == '-') {
    minus = true;
    ++i;
  }
  while ('0' <= input[i] && input[i] <= '9') {
    number.p *= 10;
    number.p += input[i] - '0';
    ++i;
  }
  if (minus) number.p *= -1;
  if (input[i] == '/') {
    number.q = 0;
    ++i;
    while ('0' <= input[i] && input[i] <= '9') {
      number.q *= 10;
      number.q += input[i] - '0';
      ++i;
    }
  } else number.q = 1;
  number.reduce();
  return is;
}

std::ostream &operator<<(std::ostream &os, const Rational &number) {
  os << number.p;
  if (number.q != 1) os << '/' << number.q;
  return os;
}

const Rational operator+(const Rational &firstNumber, const Rational &secondNumber) {
  Rational res = firstNumber;
  return res += secondNumber;
}

const Rational operator-(const Rational &firstNumber, const Rational &secondNumber) {
  Rational res = firstNumber;
  return res -= secondNumber;
}

const Rational operator*(const Rational &firstNumber, const Rational &secondNumber) {
  Rational res = firstNumber;
  return res *= secondNumber;
}

const Rational operator/(const Rational &firstNumber, const Rational &secondNumber) {
  Rational res = firstNumber;
  return res /= secondNumber;
}

inline const bool operator<(const long long &firstNumber, const Rational &secondNumber) {
  return secondNumber > firstNumber;
}

inline const bool operator>(const long long &firstNumber, const Rational &secondNumber) {
  return secondNumber < firstNumber;
}

inline const bool operator<=(const long long &firstNumber, const Rational &secondNumber) {
  return secondNumber >= firstNumber;
}

inline const bool operator>=(const long long &firstNumber, const Rational &secondNumber) {
  return secondNumber <= firstNumber;
}

inline const bool operator==(const long long &firstNumber, const Rational &secondNumber) {
  return secondNumber == firstNumber;
}

inline const bool operator!=(const long long &firstNumber, const Rational &secondNumber) {
  return secondNumber != firstNumber;
}

class MatrixWrongSizeError {
};

class MatrixIndexError {
};

class MatrixIsDegenerateError {
};
// non-specified functions to get "zero" and "one" of type T

template<typename T>
T getZero() {
  return T(0);
}

template<typename T>
T getOne() {
  return T(1);
}

template<typename T>
class Matrix {
 protected:
  int rowsCnt;
  int colsCnt;
  T **array;
 public:
  Matrix(int n, int m) : rowsCnt(n), colsCnt(m), array() {
    //if (typeid(*this) == typeid(SquareMatrix<T>)) throw MatrixWrongSizeError();
    array = new T *[rowsCnt];
    for (int i = 0; i < rowsCnt; ++i)
      array[i] = new T[colsCnt];
  }
  Matrix(const Matrix &m) : rowsCnt(m.rowsCnt), colsCnt(m.colsCnt) {
    array = new T *[m.rowsCnt];
    for (int i = 0; i < rowsCnt; ++i)
      array[i] = new T[colsCnt];
    for (int i = 0; i < rowsCnt; ++i)
      for (int j = 0; j < colsCnt; ++j)
        array[i][j] = m.array[i][j];
  }
  ~Matrix() {
    for (int i = 0; i < rowsCnt; ++i)
      delete[] array[i];
    delete[] array;
  }
  Matrix &operator=(const Matrix &m) {
    if (this == &m) return *this;
    for (int i = 0; i < rowsCnt; ++i)
      delete[] array[i];
    delete[] array;
    rowsCnt = m.rowsCnt;
    colsCnt = m.colsCnt;
    array = new T *[rowsCnt];
    for (int i = 0; i < rowsCnt; ++i)
      array[i] = new T[colsCnt];
    for (int i = 0; i < rowsCnt; ++i)
      for (int j = 0; j < colsCnt; ++j)
        array[i][j] = m.array[i][j];
    return *this;
  }
  Matrix &operator+=(const Matrix &m) {
    if (rowsCnt != m.rowsCnt || colsCnt != m.colsCnt) throw MatrixWrongSizeError();
    for (int i = 0; i < rowsCnt; ++i)
      for (int j = 0; j < colsCnt; ++j)
        array[i][j] += m.array[i][j];
    return *this;
  }
  Matrix &operator-=(const Matrix &m) {
    if (rowsCnt != m.rowsCnt || colsCnt != m.colsCnt) throw MatrixWrongSizeError();
    for (int i = 0; i < rowsCnt; ++i)
      for (int j = 0; j < colsCnt; ++j)
        array[i][j] -= m.array[i][j];
    return *this;
  }
  Matrix &operator*=(const Matrix &m) {
    if (colsCnt != m.rowsCnt) throw MatrixWrongSizeError();
    Matrix res(rowsCnt, m.colsCnt);
    for (int i = 0; i < res.rowsCnt; ++i)
      for (int j = 0; j < res.colsCnt; ++j) {
        res.array[i][j] = 0;
        for (int k = 0; k < colsCnt; ++k)
          res.array[i][j] += array[i][k] * m.array[k][j];
      }
    std::swap(*this, res);
    return *this;
  }
  Matrix &operator*=(const T &number) {
    for (int i = 0; i < rowsCnt; ++i)
      for (int j = 0; j < colsCnt; ++j)
        array[i][j] *= number;
    return *this;
  }
  T &operator()(int i, int j) { //const??
    if (i >= rowsCnt || j >= colsCnt) throw MatrixIndexError();
    return array[i][j];
  }
  T *&operator()(int i) { //const??
    if (i >= rowsCnt) throw MatrixIndexError();
    return array[i];
  }
  const T &operator()(int i, int j) const { //const??
    if (i >= rowsCnt || j >= colsCnt) throw MatrixIndexError();
    return array[i][j];
  }
  const T *&operator()(int i) const { //const??
    if (i >= rowsCnt) throw MatrixIndexError();
    return array[i];
  }
  Matrix &transpose() {
    Matrix res(colsCnt, rowsCnt);
    for (int i = 0; i < res.rowsCnt; ++i)
      for (int j = 0; j < res.colsCnt; ++j)
        res.array[i][j] = array[j][i];
    std::swap(*this, res);
    return *this;
  }
  Matrix getTransposed() const {
    Matrix res(colsCnt, rowsCnt);
    for (int i = 0; i < res.rowsCnt; ++i)
      for (int j = 0; j < res.colsCnt; ++j)
        res.array[i][j] = array[j][i];
    return res;
  }
  int getRowsNumber() const {
    return rowsCnt;
  }
  int getColumnsNumber() const {
    return colsCnt;
  }
  template<typename Te>
  friend std::istream &operator>>(std::istream &, Matrix<Te> &);
  template<typename Te>
  friend std::ostream &operator<<(std::ostream &, const Matrix<Te> &);
};

template<typename T>
std::istream &operator>>(std::istream &is, Matrix<T> &matrix) {
  for (int i = 0; i < matrix.rowsCnt; ++i)
    for (int j = 0; j < matrix.colsCnt; ++j)
      is >> matrix.array[i][j];
  return is;
}
template<typename T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix) {
  for (int i = 0; i < matrix.rowsCnt; ++i) {
    for (int j = 0; j < matrix.colsCnt; ++j)
      os << matrix.array[i][j] << '\t';
    os << '\n';
  }
  return os;
}
template<typename T>
const Matrix<T> operator+(const Matrix<T> &firstMatrix, const Matrix<T> &secondMatrix) {
  Matrix<T> res = firstMatrix;
  return res += secondMatrix;
}
template<typename T>
const Matrix<T> operator-(const Matrix<T> &firstMatrix, const Matrix<T> &secondMatrix) {
  Matrix<T> res = firstMatrix;
  return res -= secondMatrix;
}
template<typename T>
const Matrix<T> operator*(const Matrix<T> &firstMatrix, const Matrix<T> &secondMatrix) {
  Matrix<T> res = firstMatrix;
  return res *= secondMatrix;
}
template<typename T>
const Matrix<T> operator*(const T &number, const Matrix<T> &matrix) {
  Matrix<T> res = matrix;
  return res *= number;
}
template<typename T>
const Matrix<T> operator*(const Matrix<T> &matrix, const T &number) {
  Matrix<T> res = matrix;
  return res *= number;
}

template<typename T>
class SquareMatrix : public Matrix<T> {
 private:
  void rowMinusRow(T *first, T *second, T f, T s) {
    for (int i = 0; i < Matrix<T>::getRowsNumber(); ++i) {
      first[i] = first[i] - second[i] * s / f;
    }
  }
  void rowDev(T *m, T c) {
    for (int i = 0; i < Matrix<T>::getRowsNumber(); ++i) {
      m[i] /= c;
    }
  }
 public:
  SquareMatrix &transpose() {
    Matrix<T>::transpose();
    return *this;
  }
  SquareMatrix getTransposed() const {
    SquareMatrix s = Matrix<T>::getTransposed();
    return s;
  }
  SquareMatrix(int n) : Matrix<T>(n, n) {}
  SquareMatrix(Matrix<T> a) : Matrix<T>(a) {}
  SquareMatrix minorY(int row, int col) const {
    SquareMatrix<T> s(this->getSize() - 1);
    int size = this->getSize();
    for (int i = 0; i < size; ++i)
      for (int j = 0; j < size; ++j) {
        if (i == row || j == col) continue;
        s(i > row ? i - 1 : i, j > col ? j - 1 : j) = (*this)(i, j);
      }
    return s;
  }
  int getSize() const {
    return Matrix<T>::getRowsNumber();
  }
  T getDeterminant() const {
    SquareMatrix<T> cpy(*this);
    bool swapped = false;
    for (int i = 0; i < Matrix<T>::getRowsNumber(); ++i) {
      if (cpy.array[i][i] == 0) {
        for (int j = i + 1; j < Matrix<T>::getRowsNumber(); ++j)
          if (cpy.array[j][i] != 0) {
            std::swap(cpy.array[i], cpy.array[j]);
            swapped = !swapped;
            goto metka;
          }
        return 0;
      }
      metka:
      for (int j = i + 1; j <= Matrix<T>::getRowsNumber() - 1; ++j) {
        if (cpy.array[j][i] == 0) continue;
        T f = cpy.array[i][i];
        T s = cpy.array[j][i];
        cpy.rowMinusRow(cpy.array[j], cpy.array[i], f, s);
      }
    }
    T ans = 1;
    for (int i = 0, n = Matrix<T>::getRowsNumber(); i < n; ++i)
      ans *= cpy(i, i);
    ans *= (swapped ? -1 : 1);
    return ans;
  }
  SquareMatrix &invert() {
    T det = this->getDeterminant();
    if (det == T(0)) throw MatrixIsDegenerateError();

    SquareMatrix res(this->getSize());
    int size = this->getSize();

    for (int i = 0; i < size; ++i)
      for (int j = 0; j < size; ++j) {
        res(i, j) = (this->minorY(i, j)).getDeterminant() / det;
        if ((i + j) % 2 == 1) {
          res(i, j) *= -1;
        }
      }

    res.transpose();
    std::swap(res, *this);
    return *this;

    //  OLD
    //if (getDeterminant() == T(0)) throw MatrixIsDegenerateError();
    //SquareMatrix<T> eye(Matrix<T>::getRowsNumber());
    //for (int i = 0; i < Matrix<T>::getRowsNumber(); ++i)
    //	for (int j = 0; j < Matrix<T>::getRowsNumber(); ++j)
    //		eye.array[i][j] = (i == j ? 1 : 0);
    //for (int i = 0; i < Matrix<T>::getRowsNumber(); ++i) {
    //	if ((*this)(i, i) == 0)
    //		for (int j = i + 1; j < Matrix<T>::getRowsNumber() - 1; ++j)
    //			if ((*this)(j, i) != 0) {
    //				std::swap(eye.array[i], eye.array[j]);
    //				std::swap((*this)(i), (*this)(j));
    //				break;
    //			}
    //	for (int j = i + 1; j <= Matrix<T>::getRowsNumber() - 1; ++j) {
    //		if ((*this)(j, i) == 0) continue;
    //		T f = (*this)(i, i);
    //		T s = (*this)(j, i);
    //		rowMinusRow((*this)(j), (*this)(i), f, s);
    //		rowMinusRow(eye.array[j], eye.array[i], f, s);
    //	}
    //}
    //for (int i = Matrix<T>::getRowsNumber() - 1; i > 0; --i) {
    //	for (int j = i - 1; j >= 0; --j) {
    //		if ((*this)(j, i) == 0) continue;
    //		T f = (*this)(i, i);
    //		T s = (*this)(j, i);
    //		rowMinusRow((*this)(j), (*this)(i), f, s);
    //		rowMinusRow(eye.array[j], eye.array[i], f, s);
    //	}
    //}
    //for (int i = 0; i < Matrix<T>::getRowsNumber(); ++i) {
    //	rowDev(eye.array[i], (*this)(i, i));
    //}
    //std::swap(*this, eye);
    //return *this;
  }
  SquareMatrix getInverse() const {
    SquareMatrix cpy = *this;
    cpy.invert();
    return cpy;
  }
  T getTrace() const {
    T res = 0;
    for (int i = 0; i < this->Matrix<T>::getRowsNumber(); ++i)
      res += (*this)(i, i);
    return res;
  }
  SquareMatrix &operator=(const SquareMatrix &m) {
    Matrix<T>::operator=(m);
    return *this;
  }
  SquareMatrix &operator+=(const SquareMatrix &m) {
    Matrix<T>::operator+=(m);
    return *this;
  }
  SquareMatrix &operator-=(const SquareMatrix &m) {
    Matrix<T>::operator-=(m);
    return *this;
  }
  SquareMatrix &operator*=(const SquareMatrix &m) {
    Matrix<T>::operator*=(m);
    return *this;
  }
  SquareMatrix &operator*=(const T &number) {
    Matrix<T>::operator*=(number);
    return *this;
  }
};

template<typename T>
const SquareMatrix<T> operator+(const SquareMatrix<T> &firstMatrix, const SquareMatrix<T> &secondMatrix) {
  SquareMatrix<T> res = firstMatrix;
  return res += secondMatrix;
}
template<typename T>
const SquareMatrix<T> operator-(const SquareMatrix<T> &firstMatrix, const SquareMatrix<T> &secondMatrix) {
  SquareMatrix<T> res = firstMatrix;
  return res -= secondMatrix;
}
template<typename T>
const SquareMatrix<T> operator*(const SquareMatrix<T> &firstMatrix, const SquareMatrix<T> &secondMatrix) {
  SquareMatrix<T> res = firstMatrix;
  return res *= secondMatrix;
}
template<typename T>
const SquareMatrix<T> operator*(const T &number, const SquareMatrix<T> &matrix) {
  Matrix<T> res = matrix;
  return res *= number;
}
template<typename T>
const SquareMatrix<T> operator*(const SquareMatrix<T> &matrix, const T &number) {
  SquareMatrix<T> res = matrix;
  return res *= number;
}