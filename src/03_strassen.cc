/* Here I both implement the naive matrix multiplication algorithm and Strassen
algorithm. */

/* to do:
- prendere i tempi di esecuzione e confrontarli
-
*/

#include <time.h>
// #include <chrono>

#include <cstdlib>  //only for cout
#include <iostream>

#define SIZE 10

// =====================================================
// FUNCTION DECLARATIONS

// double elapsed(clock_t start, clock_t end);

template <typename T>
void print_matrix(T* A, int size);

template <typename T>
void sum(T* A, T* B, int size);

template <typename T>
void naive_matmul(T* A, T* B, T* C, int size);

template <typename T>
void strassen_matmul(T* A, T* B, T* C, int size);

// =====================================================
// FUNCTION DEFINITIONS

template <typename T>
void print_matrix(T* A, int size) {
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      std::cout << A[i * size + j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

template <typename T>
void naive_matmul(T* A, T* B, T* C, int size) {
  std::cout << "\nNaive matrix multiplication.";

  clock_t start = clock();
  // auto start = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < size; ++i)
    for (int j = 0; j < size; ++j)
      for (int k = 0; k < size; ++k) {
        C[i * size + j] += A[i * size + k] * B[k * size + j];
      }

  clock_t stop = clock();
// auto stop = std::chrono::high_resolution_clock::now();

#ifdef DEBUG
  std::cout << "\nC: \n";
  print_matrix(C, size);
#endif

  double elapsed = ((float)stop - start) * 1000.0 / CLOCKS_PER_SEC;
  // double elapsed = (stop - start).count();
  std::cout << "\nExecution time: " << elapsed << "s" << std::endl;
}

template <typename T>
void strassen_matmul(T* A, T* B, T* C, int N) {
  int subsize = N * 0.5;

  T *A11{new T[subsize * subsize]}, *A12{new T[subsize * subsize]},
      *A21{new T[subsize * subsize]}, *A22{new T[subsize * subsize]};

  T *B11{new T[subsize * subsize]}, *B12{new T[subsize * subsize]},
      *B21{new T[subsize * subsize]}, *B22{new T[subsize * subsize]};

  T *C11{new T[subsize * subsize]}, *C12{new T[subsize * subsize]},
      *C21{new T[subsize * subsize]}, *C22{new T[subsize * subsize]};

  T *P1{new T[subsize * subsize]}, *P2{new T[subsize * subsize]},
      *P3{new T[subsize * subsize]}, *P4{new T[subsize * subsize]},
      *P5{new T[subsize * subsize]}, *P6{new T[subsize * subsize]},
      *P7{new T[subsize * subsize]};

  delete[] P1, P2, P3, P4, P5, P6, P7;
}

// =====================================================

int main() {
  int size = SIZE;
  int *A{new int[size * size]}, *B{new int[size * size]},
      *C{new int[size * size]};

  for (int i = 0; i < size; ++i)
    for (int j = 0; j < size; ++j) {
      A[i * size + j] = i + 1;
      B[i * size + j] = j + 1;
      C[i * size + j] = 0;
    }

#ifdef DEBUG
  std::cout << "\nA: \n";
  print_matrix(A, size);
  std::cout << "\nB: \n";
  print_matrix(B, size);
  std::cout << "\nC: \n";
  print_matrix(C, size);
#endif

  naive_matmul(A, B, C, size);

  delete[] A;
  delete[] B;
  delete[] C;

  return 0;
}