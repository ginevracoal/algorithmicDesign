/** Lists are sequence containers that allow constant time insert and erase
 * operations anywhere within the sequence, and iteration in both directions.*/

#ifndef __list__
#define __list__

#include <iostream>

// choose if I want to use std library or my implementations
// #ifdef STD
#include <memory>  // for unique_ptr
using namespace std;
// #else
// #include "unique_ptr.h"
// #endif

template <typename T>
class list {
  struct node {
    T val;
    // pointers to previous and next nodes
    unique_ptr<node> prev, next;
    node(const T& v, node* p = nullptr, node* n = nullptr)
        : val{v}, prev{p}, next{n} {};
    // ~node();
  };

  unique_ptr<node> head, tail;
  unsigned int size;

 public:
  // Default constructor and destructor
  list() : head{nullptr}, tail{nullptr}, size{0} {}  // calls node ctor

  // Modifiers
  // Passing by const reference so that no new list is created and that the
  // function cannot change the value of the object.
  void push_back(const T& v);   // push from the head
  void push_front(const T& v);  // push from the tail
  void pop_back();
  void pop_front();
  void clear();

  // Iterators
  class iterator;
  class const_iterator;

  iterator begin() { return head.get(); }
  iterator end() { return tail.get(); }

  // const iterators return a const iterator and are const functions, so they
  // cannot modify the private members of the class.
  const_iterator cbegin() const { return head.get(); }
  const_iterator cend() const { return tail.get(); }

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
    ++(it);  // same as *this
    return it;
  }

  // it cannot modify the value of the argument
  bool operator!=(const iterator& other) {
    return this->current != other.current;
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
void list<T>::push_back(const T& v) {
  // // create a new node pointing to the head
  // node* tmp = new node(v, nullptr, head.get());
  // // reset the previous node of current head to the new node
  // head->prev.reset(tmp);
  // // update the head
  // head.reset(tmp);
  head.reset(new node{v, nullptr, head.release()});
  ++size;
}

template <typename T>
void list<T>::push_front(const T& v) {
  // node* tmp = new node(v, tail.get(), nullptr);
  // tail->prev.reset(tmp);
  // tail.reset(tmp);
  tail.reset(new node{v, tail.release(), nullptr});
  ++size;
}

void pop_back();
void pop_front();
void clear();

// template <typename T>
// list<T>::~list() {
//   node* tmp;
//   while (head) {
//     tmp = head.get();
//     delete tmp;
//   }
// }

#endif
