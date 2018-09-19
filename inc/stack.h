// #ifndef __stack__
// #define __stack__

// #include <array>
// #include <iostream>
// using namespace std;

// #define MAX_SIZE 1000

// template <typename T>
// class stack {
//  public:
//   typedef typename array<T, MAX_SIZE>::size_type size_type;

//   stack();                        // Default Constuctor
//   stack(const stack&) = default;  // Copy Constructor
//   ~stack() = default;             // Descructor

//   stack& operator=(const stack&) = default;  // Assignment Operator

//   void push(T x);
//   T pop();
//   bool isEmpty();
//   T peek();
//   void print();

//  private:
//   array<T, MAX_SIZE> a;
//   size_type top;
// };

// #endif