#include "String.h"

String::String() {

}

String::String(String&& other) noexcept {
  
}

String::String(const char* data) {

}

String::String(const char* data, const size_t size) {

}

String::~String() {

}

size_t String::size() const { 
  return size_;
}

size_t String::capacity() const { 
  return capacity_;
}

bool String::empty() const {
  return size_ == 0u;
}


int main() {

  int* x = new int(5);

  std::cout << x << std::endl;

  safe_delete(x);

  std::cout << x << std::endl;

}