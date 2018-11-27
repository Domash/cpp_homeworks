#include <initializer_list>
#include <exception>
#include <iostream>
#include <utility>
#include <cstdint>
#include <cstring>
#include <cmath>

class TryingToPopFromEmptyVector : public std::exception {
private:
  virtual const char* what() const throw() {
    return "\nVector Exception: Trying to pop from empty vector!\n";
  }
};

class InvalidIndex : public std::exception {
public:
  InvalidIndex(uint64_t size) : vector_size(size) {}
private:
  uint64_t vector_size;
  virtual const char* what() const throw() {
    if(vector_size)
      return "\nVector Exception: Out of range!\n";
    return "\nVector Exception: Vector is empty\n";
  }
};

template <class T>
class Vector {
public:

  Vector() noexcept;
  explicit Vector(size_t);
  Vector(size_t, const T&);
  Vector(const Vector<T>&);
  Vector(Vector<T> &&) noexcept;
  Vector(const std::initializer_list<T>&);

  ~Vector();

  void clear();
  bool isEmpty() const;
  uint64_t size() const;
  uint64_t capacity() const;
  int64_t find(const T&) const;

  void popBack();
  void pushBack(const T&);

  T& operator [](int64_t);
  const T& operator [](int64_t) const;

  Vector<T>& operator = (Vector<T> &&); //?
  Vector<T>& operator = (const Vector<T> &);
  Vector<T>& operator = (std::initializer_list<T>); //?

  template <class... Args> void emplaceBack(Args&&...); //?

  template <class U> friend void swap (Vector<U>&, Vector<U>&);
  template <class U> friend bool operator == (Vector<U>&, Vector<U>&);
  template <class U> friend bool operator != (Vector<U>&, Vector<U>&);

  friend std::ostream& operator << (std::ostream&, const Vector<T>&);

private:

  T *Data_;
  uint64_t Log_;
  uint64_t Size_;
  uint64_t Capacity_;

  inline void Reallocate();
  static inline uint64_t calculateLog(size_t);
};

template <class T>
Vector<T>::Vector() noexcept {
  Log_ = 0;
  Size_ = 0;
  Capacity_ = 1;
  Data_ = new T[Capacity_];
}

template <class T>
Vector<T>::Vector(size_t size) {
  Size_ = size;
  Log_ = calculateLog(size);
  Capacity_ = (1 << Log_);
  Data_ = new T[Capacity_];
}

template <class T>
Vector<T>::Vector(size_t size, const T& initial_value) {
  Size_ = size;
  Log_ = calculateLog(size);
  Capacity_ = (1 << Log_);
  Data_ = new T[Capacity_];
  for(size_t i = 0; i < Size_; ++i) {
    Data_[i] = initial_value;
  }
}

template <class T>
Vector<T>::Vector(const Vector<T> &object) {
  Log_ = object.Log_;
  Size_ = object.Size_;
  Capacity_ = object.Capacity_;
  Data_ = new T[Capacity_];
  for(size_t i = 0; i < Size_; ++i) {
    Data_[i] = object.Data_[i];
  }
}

template <class T>
Vector<T>::Vector(Vector<T> &&object) noexcept {
  Log_ = std::move(object.Log_);
  Size_ = std::move(object.Size_);
  Capacity_ = std::move(object.Capacity_);
  Data_ = new T[Capacity_];
  for(size_t i = 0; i < Size_; ++i) {
    Data_[i] = std::move(object.Data_[i]);
  }
}

template <class T>
Vector<T>::Vector(const std::initializer_list<T>& object) {
  Size_ = object.size();
  Log_ = calculateLog(object.size());
  Capacity_ = (1 << Log_);
  Data_ = new T[Capacity_];

  size_t index = 0;
  for(const auto& it : object) {
    this -> Data_[index] = it;
    index++;
  }
}

template <class T>
Vector<T>::~Vector() {
  this -> clear();
}

template <class T>
void Vector<T>::clear() {
  if(Capacity_) delete[] Data_;
  else delete Data_;
  Size_ = Capacity_ = Log_ = 0;
}

template <class T>
bool Vector<T>::isEmpty() const {
  return Size_ == 0;
}

template <class T>
uint64_t Vector<T>::size() const {
  return this -> Size_;
}

template <class T>
uint64_t Vector<T>::capacity() const {
  return this -> Capacity_;
}

template <class T>
int64_t Vector<T>::find(const T& value) const {
  for(size_t i = 0; i < Size_; ++i) {
    if(Data_[i] == value) {
      return i;
    }
  }
  return -1;
}

template <class T>
void Vector<T>::popBack() {
  if(Size_ == 0)
    throw TryingToPopFromEmptyVector();
  Size_--;
  Data_[Size_].~T();
  if(Size_ < (1 << (Log_ - 2))) {
    Log_--;
    Reallocate();
  }
}

template <class T>
void Vector<T>::pushBack(const T& value) {
  if(Size_ == Capacity_) {
    Log_++;
    Reallocate();
  }
  Data_[Size_++] = value;
}

template <class T>
T& Vector<T>::operator [](int64_t index) {
  if(index < 0 || Size_ <= index)
    throw InvalidIndex(Size_);
  return Data_[index];
}

template <class T>
const T& Vector<T>::operator [](int64_t index) const {
  if(index < 0 || Size_ <= index)
    throw InvalidIndex(Size_);
  return Data_[index];
}

template <class T>
Vector<T>& Vector<T>::operator = (const Vector<T> &object) {
  delete[] Data_;
  Log_ = object.Log_;
  Size_ = object.Size_;
  Capacity_ = object.Capacity_;
  Data_ = new T[Capacity_];
  for(size_t i = 0; i < Size_; ++i) {
    Data_[i] = object.Data_[i];
  }
}

/*template <class T>
template <class... Args>
void Vector<T>::emplaceBack(Args&&... args) {
  this -> pushBack(T(args...));
}*/

template <class T>
void Vector<T>::Reallocate() {
  Capacity_ = (1 << Log_);
  T *Data = new T[Capacity_];
  memcpy(Data, Data_, Size_ * sizeof(T));
  if(Capacity_) delete[] Data_;
  else delete Data_;
  Data_ = Data;
}

template <class T>
uint64_t Vector<T>::calculateLog(size_t size) {
  uint64_t Log = ceil(log(static_cast<double>(size)) / log(static_cast<double>(2)));
  return Log;
}

template <class U>
void swap(Vector<U>& object_1, Vector<U>& object_2) {
  std::swap(object_1.Log_, object_2.Log_);
  std::swap(object_1.Size_, object_2.Size_);
  std::swap(object_1.Capacity_, object_2.Capacity_);
  std::swap(object_1.Data_, object_2.Data_);
}

template <class U>
bool operator == (Vector<U>& object_1, Vector<U>& object_2) {
  if(object_1.size() != object_2.size())
    return false;
  for(size_t i = 0; i < object_1.size(); ++i) {
    if(object_1[i] != object_2[i])
      return false;
  }
  return true;
}

template <class U>
bool operator != (Vector<U>& object_1, Vector<U>& object_2) {
  return !(object_1 == object_2);
}

template <class T>
std::ostream& operator << (std::ostream& os, Vector<T>& object) {
  os << "[ ";
  for(size_t i = 0; i < object.size(); ++i) {
    os << object[i];
    os << " ";
  }
  os << "]";
  return os;
}
