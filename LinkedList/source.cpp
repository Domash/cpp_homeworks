#include <stdexcept>
#include <iostream>
#include <cstdint>
#include <utility>

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

    // constructors & destructor

    LinkedList();
    LinkedList(const LinkedList<T>&);
    LinkedList(const LinkedList<T>*);
    ~LinkedList();

    // methods

    void print();
    void clear();

    bool remove();
    void add(const T&);

    size_t size() const;
    bool isEmpty() const;

    T& at(int32_t);
    const T& at(int32_t) const;

    // operators

    LinkedList<T>& operator = (const LinkedList<T>&);

    // friend

    template <class T1> friend void swap(LinkedList<T1>&, LinkedList<T1>&);
    template <class T1> friend bool operator == (LinkedList<T1>&, LinkedList<T1>&);
    template <class T1> friend bool operator != (LinkedList<T1>&, LinkedList<T1>&);

    /*template <class... Args>
    void emplace_back(Args&&... args) {
      this -> add(std::move(T({ args... })));
    }*/

  private:
    Node <T> *_first = nullptr;

    Node<T>* frontNode() const;
  };

  template <class T>
  LinkedList<T>::LinkedList() {
    _first = nullptr;
  }

  template <class T>
  LinkedList<T>::LinkedList(const LinkedList<T>& object) {
    Node<T>* currentNode = object.frontNode();
    while(currentNode != nullptr) {
      this -> add(currentNode -> _value);
      currentNode = currentNode -> _next;
    }
  }

  template <class T>
  LinkedList<T>::LinkedList(const LinkedList<T>* object) {
    Node<T>* currentNode = object -> frontNode();
    while(currentNode != nullptr) {
      this -> add(currentNode -> _value);
      currentNode = currentNode -> _next;
    }
  }

  template <class T>
  LinkedList<T>::~LinkedList() {
    clear();
  }

  template <class T>
  void LinkedList<T>::add(const T& value) {
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

  template <class T>
  Node<T>* LinkedList<T>::frontNode() const {
    return this -> _first;
  }

  template<class T>
  LinkedList<T>& LinkedList<T>::operator = (const LinkedList<T>& object) {
    this -> clear();
    Node<T>* currentNode = object.frontNode();
    while(currentNode != nullptr) {
      this -> add(currentNode -> _value);
      currentNode = currentNode -> _next;
    }
    return *this;
  }

  template <class T>
  bool operator == (LinkedList<T>& object_1, LinkedList<T>& object_2) {
    if(object_1.size() != object_2.size())
      return false;
    for(int32_t i = 1; i <= object_1.size(); ++i) {
      if(object_1.at(i) != object_2.at(i))
        return false;
    }
    return true;
  }

  template <class T>
  bool operator != (LinkedList<T>& object_1, LinkedList<T>& object_2) {
    return !(object_1 == object_2);
  }

}

using namespace LinkedList;

int main() {

  LinkedList<int> *list = new LinkedList<int>();

  list -> add(10);
  list -> add(10);
  list -> add(10);

  LinkedList<int> *list2 = new LinkedList<int>();

  list2 -> add(20);
  list2 -> add(20);
  list2 -> add(20);

  *list = *list2;

  list -> print();

  /*LinkedList<int> list;

  //std::cout << std::boolalpha << list.isEmpty() << std::endl;

  list.add(10);
  list.add(-20);

  LinkedList<int> list2;

  list2.add(10);
  list2.add(111);
  list2.add(123);

  list = list2;

  list.print();*/

}
