#include <stdexcept>
#include <iostream>
#include <cstdint>

namespace LinkedList {

  template <class T>
  struct Node {
    Node(T value) {
      _value = value;
      _next = nullptr;
    }

    T _value;
    Node <T> *_next;
  };

  template <class T>
  class LinkedList {
  public:
    LinkedList();
    ~LinkedList();

    void print();
    void clear();

    bool remove();
    void add(T value);

    size_t size() const;
    bool isEmpty() const;

    T& at(int32_t index);
    const T& at(int32_t index) const;

  private:
    Node <T> *_first;
  };

  template <class T>
  LinkedList<T>::LinkedList() {
    _first = nullptr;
  }

  template <class T>
  LinkedList<T>::~LinkedList() {
    clear();
  }

  template <class T>
  void LinkedList<T>::add(T value) {
    Node<T> *newNode = new Node<T>(value);
    Node<T> *currentNode = _first;

    if(currentNode == nullptr) {
      _first = newNode;
    } else {
      while(currentNode -> _next != nullptr) {
        currentNode = currentNode -> _next;
      }
      currentNode -> _next = newNode;
    }
  }

  template <class T>
  bool LinkedList<T>::remove() {
    if(_first == nullptr) return false;

    Node<T> *prevNode = nullptr;
    Node<T> *currentNode = _first;
    while(currentNode -> _next != nullptr) {
      prevNode = currentNode;
      currentNode = currentNode -> _next;
    }

    if(prevNode == nullptr) {
      delete(_first);
      _first = nullptr;
    } else {
      prevNode -> _next = nullptr;
      delete(currentNode);
    }
    return true;
  }

  template <class T>
  void LinkedList<T>::print() {
    Node<T> *currentNode = _first;
    while(currentNode != nullptr) {
      std::cout << currentNode -> _value << ' ';
      currentNode = currentNode -> _next;
    }
    std::cout << std::endl;
  }

  template <class T>
  void LinkedList<T>::clear() {
    Node <T> *currentNode = _first;
    while(currentNode != nullptr) {
      currentNode = currentNode -> _next;
      delete(_first);
      _first = currentNode;
    }
  }

  template <class T>
  bool LinkedList<T>::isEmpty() const {
    if(_first == nullptr) return true;
    return false;
  }

  template <class T>
  size_t LinkedList<T>::size() const {
    size_t length = 0;
    Node<T> *currentNode = _first;
    while(currentNode != nullptr) {
      length++;
      currentNode = currentNode -> _next;
    }
    return length;
  }

  template <class T>
  T& LinkedList<T>::at(int32_t index) {
    if(index < 1 || index > size()) {
      throw std::out_of_range("Bad Index\n");
    }
    int32_t currentIndex = 1;
    Node<T> *currentNode = _first;
    while(currentIndex != index) {
      currentNode = currentNode -> _next;
      currentIndex++;
    }
    return currentNode -> _value;
  }

  template <class T>
  const T& LinkedList<T>::at(int32_t index) const {
    if(index < 1 || index > size()) {
      throw std::out_of_range("Bad Index\n");
    }
    int32_t currentIndex = 1;
    Node<T> *currentNode = _first;
    while(currentIndex != index) {
      currentNode = currentNode -> _next;
      currentIndex++;
    }
    return currentNode -> _value;
  }
}

using namespace LinkedList;

int main() {

  LinkedList<int> *list = new LinkedList<int>();

  std::cout << std::boolalpha << list -> isEmpty() << std::endl;

  list -> add(10);
  list -> add(-20);

  std::cout << list -> at(2) << std::endl;
  std::cout << list -> at(-1) << std::endl;
}
