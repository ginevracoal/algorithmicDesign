// unique_ptr belongs to header memory
// std::unique_ptr is a smart pointer that owns and manages another object
// through a pointer and disposes of that object when the unique_ptr goes out of
// scope. std::unique_ptr is commonly used to manage the lifetime of objects.
// In this version unique_ptr manages a single object allocated with new.

#ifndef __unique_ptr__
#define __unique_ptr__

#include <iostream>

// const? noexcept?

template <typename T>
class unique_ptr {
  T* ptr;

 public:
  // CLASS CONSTRUCTORS
  unique_ptr() : ptr{nullptr} {}  // it is a nullptr if no object is owned

  unique_ptr(T* p) : ptr{p} {}

  // CLASS DESTRUCTOR
  // The owned object is destroyed
  ~unique_ptr() {
    // if (get() != nullptr) reset();  // posso usare anche get() e basta?
    delete ptr;
  }

  // MODIFIERS

  // Move constructor
  // Creates a new unique_ptr by transferring the ownership from u to *this
  unique_ptr(unique_ptr<T>&& u) {
    ptr = std::move(u.ptr);
    u.ptr = nullptr;
  }

  // Assignment operator
  // Transfers the ownership from ref to *this
  unique_ptr<T>& operator=(const unique_ptr<T>& u) {
    // unique_ptr<T> tmp = ref.release();
    if (this != u) {
      ptr = std::move(u.ptr);
      u.ptr = nullptr;
    }
    std::cout << "\n*this: " << *this;
    return *this;
  }

  // Releases the ownership of the managed object and returns a pointer to it
  T* release() {
    T* tmp = get();
    ptr = nullptr;  // prt releases the object
    return tmp;
  }

  // Replaces the managed object with a new one
  void reset(T* new_ptr = nullptr) {
    if (ptr != new_ptr) ptr = new_ptr;  // oppure ptr!=get() ?
  }

  void swap(unique_ptr<T> new_ptr) { std::swap(ptr, new_ptr); }

  // OBSERVERS

  // Returns a pointer to the managed object
  T* get() { return ptr; }

  // Checks if *this owns something or not. This is a conversion
  // operator, which allows to use *this as bool.
  operator bool() { return ptr != nullptr; }  // va bene anche return ptr?

  // DEREFERENCE OPERATORS

  // Returns the object owned (pointed to) by *this
  T& operator*() { return *ptr; }
  // Returns a pointer to the object onwed by *this
  T* operator->() { return get(); }

  // EXTRA FUNCTION
  // I wrote this just to understand how everything works.
  void understand() {
    // this == &ptr
    // ptr has access to its own memory address through this pointer.
    // so *this is the object of the pointer this, which is simply ptr.
    std::cout << "\nthis: " << this;
    std::cout << "\n&ptr: " << &ptr;
    // ptr == get()
    std::cout << "\nptr: " << ptr;
    std::cout << "\nget(): " << get();
    // ptr == **this
    std::cout << "\n*ptr: " << *ptr;
    std::cout << "\n**this: " << **this;
    // so what is *this? it is the unique_ptr itself!!
    std::cout << "\n*this: " << *this;
    // not allowed because this is not an object! it is just a reference
    std::cout << "\n";
  }
};

// Non-member functions

#endif