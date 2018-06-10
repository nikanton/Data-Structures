inline long long gcd(long long a, long long b) {
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