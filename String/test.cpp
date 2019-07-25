#include "String.h"

int main() {

  int* x = new int(5);

  std::cout << x << std::endl;

  safe_delete(x);

  std::cout << x << std::endl;

  return 0;
}