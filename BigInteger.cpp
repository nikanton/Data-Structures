class BigIntegerDivisionByZero {
};

class BigIntegerOverflow {
};

class BigInteger {
  Vector<int> digits;
  bool sign;
  static const int BASE = 1e4; //BASE must be power of 10

 public:
  BigInteger() : digits(), sign(true) {}

  BigInteger(int number) {
    int copyOfNumber = number;

    if (number < 0) {
      sign = false;
      copyOfNumber *= -1;
    }

    if (!number) {
      sign = true;
      digits.push_back(0);
    }

    if (number > 0)
      sign = true;

    while (copyOfNumber) {
      digits.push_back(copyOfNumber % BASE);
      copyOfNumber /= BASE;
    }
  }

  BigInteger(const BigInteger &number) {
    sign = number.sign;

    for (size_t i = 0; i < number.digits.size(); ++i)
      digits.push_back(number.digits[i]);
  }

  BigInteger &operator=(const BigInteger &number) {
    if (this != &number) {
      digits.clear();

      sign = number.sign;

      for (size_t i = 0; i < number.digits.size(); ++i)
        digits.push_back(number.digits[i]);
    }

    return *this;
  }

  bool operator==(const BigInteger &number) const {
    if (digits.size() != number.digits.size() || sign != number.sign)
      return false;

    for (size_t i = 0; i < digits.size(); ++i)
      if (digits[i] != number.digits[i])
        return false;

    return true;
  }

  bool operator!=(const BigInteger &number) const {
    return !(*this == number);
  }

  bool operator<(const BigInteger &number) const {
    if (sign < number.sign)
      return true;

    if (sign > number.sign)
      return false;

    if (digits.size() < number.digits.size())
      return sign;

    if (digits.size() > number.digits.size())
      return !sign;

    for (size_t i = digits.size() - 1; i != 0; --i) {
      if (digits[i] < number.digits[i])
        return sign;

      if (digits[i] > number.digits[i])
        return !sign;
    }

    if (digits[0] < number.digits[0])
      return sign;

    return !sign;
  }

  bool operator<=(const BigInteger &number) const {
    return !(number < *this);
  }

  bool operator>(const BigInteger &number) const {
    return number < *this;
  }

  bool operator>=(const BigInteger &number) const {
    return !(*this < number);
  }

  const BigInteger operator-() const {
    BigInteger result = *this;

    if (!result.sign)
      result.sign = true;
    else if (result)
      result.sign = false;

    return result;
  }

  BigInteger &operator+=(const BigInteger &number) {
    if (sign == number.sign) {
      int overflow = 0;
      int newOverflow;

      for (size_t i = 0; i < std::min(digits.size(), number.digits.size()); ++i) {
        newOverflow = (number.digits[i] + digits[i] + overflow) / BASE;
        digits[i] = (number.digits[i] + digits[i] + overflow) % BASE;
        overflow = newOverflow;
      }

      for (size_t i = std::min(digits.size(), number.digits.size()); i < digits.size(); ++i) {
        newOverflow = (digits[i] + overflow) / BASE;
        digits[i] = (digits[i] + overflow) % BASE;
        overflow = newOverflow;
      }

      for (size_t i = std::min(digits.size(), number.digits.size()); i < number.digits.size(); ++i) {
        digits.push_back((number.digits[i] + overflow) % BASE);
        overflow = (number.digits[i] + overflow) / BASE;
      }

      if (overflow)
        digits.push_back(overflow);
    } else {
      BigInteger result;

      if ((sign && *this < -number) || (!sign && *this > -number)) {
        sign = !sign;

        result = number;

        for (size_t i = 0; i < digits.size(); ++i)
          if (digits[i] > result.digits[i]) {
            size_t j;
            for (j = i + 1; j < result.digits.size() && result.digits[j] == 0; ++j);
            --result.digits[j];
            for (size_t t = j - 1; t > i; --t)
              result.digits[t] = BASE - 1;
            result.digits[i] += BASE - digits[i];
          } else
            result.digits[i] -= digits[i];
      } else {

        result = *this;

        for (size_t i = 0; i < number.digits.size(); ++i) {
          if (result.digits[i] < number.digits[i]) {
            size_t j;
            for (j = i + 1; j < result.digits.size() && result.digits[j] == 0; ++j);
            --result.digits[j];
            for (size_t t = j - 1; t > i; --t)
              result.digits[t] = BASE - 1;
            result.digits[i] = BASE - number.digits[i] + result.digits[i];
          } else
            result.digits[i] -= number.digits[i];
        }
      }

      digits.clear();
      size_t i;
      for (i = result.digits.size() - 1; i != 0 && !result.digits[i]; --i);
      for (size_t j = 0; j <= i; ++j)
        digits.push_back(result.digits[j]);
    }

    if (!*this)
      sign = true;

    if (digits.size() > 5000) throw BigIntegerOverflow();
    return *this;
  }

  BigInteger &operator-=(const BigInteger &number) {
    return *this += -number;
  }

  BigInteger &operator++() {
    *this += static_cast <BigInteger> (1);
    return *this;
  }

  BigInteger &operator--() {
    *this -= static_cast <BigInteger> (1);
    return *this;
  }

  const BigInteger operator++(int) {
    BigInteger result = *this;

    *this += static_cast <BigInteger> (1);

    return result;
  }

  const BigInteger operator--(int) {
    BigInteger result = *this;

    *this -= static_cast <BigInteger> (1);

    return result;
  }

  BigInteger &operator*=(const BigInteger &number) {
    if (!*this || !number) {
      *this = 0;
      return *this;
    }

    BigInteger answer = 0;

    BigInteger result = 0;

    for (size_t i = 0; i < number.digits.size(); ++i) {
      if (number.digits[i]) {
        result.digits.clear();

        for (size_t j = 0; j < i; ++j)
          result.digits.push_back(0);

        for (size_t j = i; j < i + digits.size(); ++j)
          result.digits.push_back(digits[j - i]);

        int overflow = 0;

        for (size_t j = 0; j < digits.size(); ++j) {
          int newOverflow = (result.digits[j + i] * number.digits[i] + overflow) / BASE;
          result.digits[j + i] = (result.digits[j + i] * number.digits[i] + overflow) % BASE;
          overflow = newOverflow;
        }

        if (overflow)
          result.digits.push_back(overflow);

        answer += result;
      }
    }

    bool signN = (sign == number.sign || !*this) ? true : false;

    *this = answer;

    sign = signN;

    if (digits.size() > 5000) throw BigIntegerOverflow();
    return *this;
  }

  BigInteger &operator%=(const BigInteger &number) {
    BigInteger result = 0;
    BigInteger divisor = number;

    if (divisor < 0)
      divisor *= -1;

    size_t pos = digits.size();

    do {
      --pos;

      if (result) {
        result.digits.push_back(0);
        for (size_t i = result.digits.size() - 1; i >= 1; --i)
          result.digits[i] = result.digits[i - 1];
      }
      result.digits[0] = digits[pos];

      while (result >= divisor)
        result -= divisor;
    } while (pos);

    bool signN = sign;

    *this = result;

    sign = signN;

    if (digits.size() == 1 && !digits[0])
      sign = true;

    return *this;
  }

  std::string toString() {
    std::string answer;

    if (!sign)
      answer.push_back('-');

    if (!*this)
      answer.push_back('0');

    bool isNumberGreaterZero = false;

    size_t pos = digits.size();

    do {
      --pos;
      int divisor = BASE / 10;
      int digit = digits[pos];
      while (divisor) {
        if (pos != digits.size() - 1 || digit / divisor || isNumberGreaterZero) {
          answer.push_back(digit / divisor + '0');
          isNumberGreaterZero = true;
        }
        digit %= divisor;
        divisor /= 10;
      }
    } while (pos);

    return answer;
  }

  friend std::istream &operator>>(std::istream &inputStream, BigInteger &number);

  explicit operator bool() const {
    return (digits.size() == 1 && !digits[0]) ? false : true;
  }

  BigInteger &operator/=(const BigInteger &number);

  BigInteger sqrt() const;

  BigInteger &operator>>=(int) { //only for 1 circular shift
    digits[0] >>= 1;
    for (size_t i = 1, l = digits.size(); i < l; ++i) {
      if (digits[i] % 2 == 1) digits[i - 1] += BASE / 2;
      digits[i] >>= 1;
    }
    if (digits.back() == 0) digits.pop_back();
    return *this;
  }
};

std::ostream &operator<<(std::ostream &outputStream, BigInteger &number) {
  std::string answer = number.toString();

  outputStream << answer;

  return outputStream;
}

std::istream &operator>>(std::istream &inputStream, BigInteger &number) {
  number.digits.clear();

  std::string input;

  inputStream >> input;

  number.sign = true;

  if (input[0] == '-')
    number.sign = false;

  size_t pos = input.size() + 3;

  do {
    pos -= 4;
    int digit = 0;
    if (number.sign || pos > 0)
      digit += input[pos] - '0';
    if (pos >= 1 && (number.sign || pos > 1))
      digit += (input[pos - 1] - '0') * 10;
    if (pos >= 2 && (number.sign || pos > 2))
      digit += (input[pos - 2] - '0') * 100;
    if (pos >= 3 && (number.sign || pos > 3))
      digit += (input[pos - 3] - '0') * 1000;
    if ((pos >= 4 && (number.sign || pos > 4)) || digit)
      number.digits.push_back(digit);

  } while (pos > 3);

  if (!number.digits.size())
    number.digits.push_back(0);

  return inputStream;
}

const BigInteger operator+(const BigInteger &firstNumber, const BigInteger &secondNumber) {
  BigInteger result = firstNumber;

  return result += secondNumber;
}

const BigInteger operator-(const BigInteger &firstNumber, const BigInteger &secondNumber) {
  BigInteger result = firstNumber;

  return result -= secondNumber;
}

const BigInteger operator*(const BigInteger &firstNumber, const BigInteger &secondNumber) {
  BigInteger result = firstNumber;

  return result *= secondNumber;
}

const BigInteger operator/(const BigInteger &firstNumber, const BigInteger &secondNumber) {
  BigInteger result = firstNumber;

  return result /= secondNumber;
}

const BigInteger operator%(const BigInteger &firstNumber, const BigInteger &secondNumber) {
  BigInteger result = firstNumber;

  return result %= secondNumber;
}

BigInteger &BigInteger::operator/=(const BigInteger &number) {
  if (number == 0) throw BigIntegerOverflow();

  BigInteger numCpy = number;

  bool signN = (sign == number.sign || !*this) ? true : false;
  numCpy.sign = true;
  sign = true;

  size_t n1 = digits.size();
  size_t n2 = number.digits.size();
  BigInteger left(0), right(0);
  for (size_t i = 1; i < n1 - n2; ++i) right.digits.push_back(0);
  for (size_t i = 1; i < n1 - n2 + 2; ++i) left.digits.push_back(0);
  ++(right.digits.back());
  ++(left.digits.back());

  BigInteger middle;
  while (left > right + 1) {
    middle = (left + right);
    middle >>= 1;
    if (middle * numCpy > *this) std::swap(middle, left);
    else std::swap(middle, right);
  }

  std::swap(*this, right);
  sign = signN;
  return *this;
}

BigInteger BigInteger::sqrt() const {
  //if (sign == false) throw;

  size_t n1 = digits.size();
  BigInteger left(0), right(0);
  for (size_t i = 1; i < n1 / 2; ++i) right.digits.push_back(0);
  for (size_t i = 1; i < n1 / 2 + 2; ++i) left.digits.push_back(0);
  ++(right.digits.back());
  ++(left.digits.back());

  BigInteger middle;
  while (left > right + 1) {
    middle = (left + right);
    middle >>= 1;
    if (middle * middle > *this) std::swap(middle, left);
    else std::swap(middle, right);
  }

  return right;
}

inline BigInteger gcd(BigInteger a, BigInteger b) {
  return (b != 0 ? gcd(b, a % b) : a);
}