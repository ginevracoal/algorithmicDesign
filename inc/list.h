/** Lists are sequence containers that allow constant time insert and erase
 * operations anywhere within the sequence, and iteration in both directions.*/

#ifndef __list__
#define __list__

#include <iostream>
#include <memory>  // for unique_ptr
using namespace std;
// #include "unique_ptr.h"

template <typename T>
class list {
  struct node {
    T val;
    // pointers to previous and next nodes
    unique_ptr<node> next;
    node(const T& v, node* n = nullptr) : val{v}, next{n} {};
    // ~node();
  };

  unique_ptr<node> head;
  unsigned int size;

 public:
  // Default constructor and destructor
  list() : head{nullptr}, size{0} {}  // calls node ctor

  // Modifiers
  // Passing by const reference so that no new list is created and that the
  // function cannot change the value of the object.
  void push_back(const T&);   // push from the head
  void push_front(const T&);  // push from the tail
  void pop_back();
  void pop_front();
  // void clear();
  void insert(const T&);
  T& front();
  T& back();

  // Iterators
  class iterator;
  iterator begin() { return head.get(); }
  iterator end() { return iterator{nullptr}; }

  // const iterators return a const iterator and are const functions, so they
  // cannot modify the private members of the class.
  class const_iterator;
  const_iterator cbegin() const { return head.get(); }
  const_iterator cend() const { return iterator{nullptr}; }

  // Observers
  void print();
  bool empty() { return head.get() == nullptr; }

  // ~list();
};

// ITERATORS
template <typename T>
class list<T>::iterator {
  using node = list<T>::node;
  node* current;

 public:
  iterator(node* n) : current{n} {}

  // dereference operator
  T& operator*() const { return current->val; }

  // ++it operator
  // it's safe to return a reference because current lives outside the scope
  iterator& operator++() {
    current = current->next.get();
    return *this;  // same as current?
  }

  // it++ operator
  iterator operator++(int) {
    iterator it{current};
    ++(*this);  // same as it
    return it;
  }

  // it cannot modify the value of the argument
  bool operator!=(const iterator& other) {
    return this->current != other.current;
  }

  bool operator==(const iterator& other) {
    return this->current == other.current;
  }
};

template <typename T>
class list<T>::const_iterator : public list<T>::iterator {
  using parent = list<T>::iterator;

 public:
  using parent::iterator;

  const T& operator*() const { return parent::operator*(); }
};

// MEMBER FUNCTIONS

template <typename T>
void list<T>::push_front(const T& v) {
  head.reset(new node{v, head.release()});
  ++size;
}

template <typename T>
void list<T>::push_back(const T& v) {
  node* tmp{head.get()};
  while (tmp->next.get() != nullptr) tmp = tmp->next.get();
  tmp->next.reset(new node{v});
  ++size;
}

// remove the first element in the container
template <typename T>
void list<T>::pop_back() {
  if (!empty()) {
    node* tmp = head.get();
    node* prev = nullptr;
    while (tmp->next != nullptr) {
      prev = tmp;
      tmp = tmp->next.get();
    }
    prev->next.reset(nullptr);
  }
}

template <typename T>
void list<T>::pop_front() {
  if (!empty()) {
    node* tmp = head->next.get();
    head.reset(tmp);
  }
}

template <typename T>
T& list<T>::back() {
  node* tmp = head.get();
  while (tmp->next != nullptr) tmp = tmp->next.get();
  return tmp->val;
}

template <typename T>
T& list<T>::front() {
  return head->val;
}

template <typename T>
void list<T>::insert(const T& v) {
  if (head.get() == nullptr) {
    head.reset(new node{v});
  } else
    push_back(v);
}

template <typename T>
void list<T>::print() {  // it cannot modify any member of list
  for (auto it = this->begin(); it != this->end(); ++it) cout << *it << " ";
  cout << endl;
}

#endif
