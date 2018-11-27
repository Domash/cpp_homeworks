#include <iostream>
#include <cstring>
#include <cmath>

#include "vector.hpp"

int main() {

  Vector<int> x({1, 2, 3, 4});
  Vector<int> y({5, 6, 7, 8});

  std::cout << x << std::endl;
  std::cout << y << std::endl;

  swap(x, y);
  swap(x, y);

  std::cout << x << std::endl;
  std::cout << y << std::endl;

  return 0;
}
