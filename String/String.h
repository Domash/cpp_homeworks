#include <iostream>

#define safe_delete(x) { \
  delete x;              \
  x = nullptr;           \
}

class String {

public:

  String();
  String(String &&) noexcept;
  String(const char*);
  String(const char*, size_t);
  
  ~String();

  size_t size() const;
  size_t capacity() const;

  void clear();
  void resize(size_t);

  bool empty() const;

  //size_t index(char c) const;

  friend bool operator == (const String&, const String&);
  friend bool operator != (const String&, const String&);
  friend bool operator >  (const String&, const String&);
  friend bool operator <  (const String&, const String&);
  friend bool operator >= (const String&, const String&);
  friend bool operator <= (const String&, const String&);

private:

  char*   data_;
  size_t  size_;
  size_t  capacity_;

};