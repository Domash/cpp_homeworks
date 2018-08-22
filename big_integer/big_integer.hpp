#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <ostream>

class big_integer {
public:  

    big_integer();
    big_integer(long long val);
    big_integer(big_integer const &other);
    explicit big_integer(std::string const &str);

    big_integer &operator = (big_integer const &val);
    big_integer &operator += (big_integer const &val);
    big_integer &operator -= (big_integer const &val);
    big_integer &operator *= (big_integer const &val);

    friend bool operator == (big_integer const &a, big_integer const &b);
    friend bool operator != (big_integer const &a, big_integer const &b);
    friend bool operator >= (big_integer const &a, big_integer const &b);
    friend bool operator <= (big_integer const &a, big_integer const &b);
    friend bool operator > (big_integer const &a, big_integer const &b);
    friend bool operator < (big_integer const &a, big_integer const &b);

    friend big_integer operator + (big_integer const &a, big_integer const &b);
    friend big_integer operator - (big_integer const &a, big_integer const &b);
    friend big_integer operator * (big_integer const &a, big_integer const &b);
    friend big_integer operator / (big_integer const &a, big_integer const &b);
    friend big_integer operator % (big_integer const &a, big_integer const &b);

    friend std::string to_string(big_integer const &val);

private:

    bool sign = false;
    std::vector <int> data;
    static const int base = 10;

    bool is_zero() const;
    void shrink_zeroes();
    bool is_digit(char) const;
    big_integer abs() const;
    int get_digit(size_t) const;

};