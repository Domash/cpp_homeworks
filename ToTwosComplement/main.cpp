#include <algorithm>
#include <iostream>
#include <cstdint>
#include <vector>
#include <cmath>

struct ToTwosComplement {
  ToTwosComplement(long long x) {
    bool sign = false;
    if(x < 0) sign = true, x *= -1;
    do {
      digits.push_back(x & 1);
      x >>= 1;
    } while(x);

    // filling to full binary form
    const int32_t len = digits.size();
    for(size_t i = 0; i < SIZE - len; ++i) {
      digits.push_back(0);
    }

    if(sign) {
      invertBits(digits);
      bool carry = false, one = true;
      for(size_t i = 0; i < SIZE; ++i) {
        digits[i] = digits[i] ^ carry ^ one;
        carry = (digits[i] & one) | ((digits[i] ^ one) & carry);
      }
    }
  }

  ToTwosComplement(std::vector<bool> digits_) {
    digits = digits_;
  }

  static void invertBits(std::vector<bool>& digits) {
    for(size_t i = 0; i < SIZE; ++i) {
      digits[i] = digits[i] ^ true;
    }
  }

  static long long toDecimal(const ToTwosComplement& number) {

  }

  static std::string toBinary(const ToTwosComplement& number) {
    std::string result = "";
    for(const auto& digit : number.digits) {
      result += (digit + '0');
    }
    std::reverse(result.begin(), result.end());
    return result;
  }

  friend ToTwosComplement operator + (const ToTwosComplement& f, const ToTwosComplement& s) {
    std::vector<bool> result(SIZE);
    bool carry = false;
    for(size_t i = 0; i < f.digits.size(); ++i) {
      result[i] = f.digits[i] ^ s.digits[i] ^ carry;
      carry = (f.digits[i] & s.digits[i]) | ((f.digits[i] ^ s.digits[i]) & carry);
    }
    return ToTwosComplement(result);
  }

  friend ToTwosComplement operator - (const ToTwosComplement& f, const ToTwosComplement& s) {
    //TODO
  }

  friend ToTwosComplement operator * (const ToTwosComplement& f, const ToTwosComplement& s) {
    //TODO
  }

  std::vector<bool> digits;
  static constexpr int32_t SIZE = 16;
};

/*
  Multiplication -> a * x = sum(1..x)(a);
  Division -> a / x = a - x while a > x sum of iterations
*/



int32_t main() {

  long long x, y;
  std::cin >> x >> y;

  ToTwosComplement xx(x);
  ToTwosComplement yy(y);

  std::cout << ToTwosComplement::toBinary(xx) << std::endl;
  std::cout << ToTwosComplement::toBinary(yy) << std::endl;

  std::cout << ToTwosComplement::toBinary(xx + yy) << std::endl;

  return 0;
}
