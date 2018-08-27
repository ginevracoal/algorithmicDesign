/* Here I both implement the naive matrix multiplication algorithm and Strassen
algorithm. */

/*
- differenza tra malloc e new?
- fare una seconda versione che usa una specie di unique ptr
*/

#include <time.h>
// #include <chrono>

#include <cstdlib>  //only for cout
#include <iostream>

#define SIZE 4

// =====================================================
// FUNCTION DECLARATIONS

// double elapsed(clock_t start, clock_t end);

template <typename T>
void print_matrix(T* A, int size);

template <typename T>
void sum(T* A, T* B, T* C, int size);

template <typename T>
void diff(T* A, T* B, T* C, int size);

template <typename T>
T* naive_matmul(T* A, T* B, int size);

template <typename T>
T* strassen_matmul(T* A, T* B, int size);

// =====================================================
// FUNCTION DEFINITIONS

template <typename T>
void print_matrix(T* M, int size) {
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      std::cout << M[i * size + j] << "\t";
    }
    std::cout << std::endl;
  }
}

template <typename T>
T* naive_matmul(T* A, T* B, int size) {
  std::cout << "\n\nNaive matrix multiplication.";

  T* C{new T[size * size]};

  clock_t start = clock();
  // auto start = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < size; ++i)
    for (int j = 0; j < size; ++j)
      for (int k = 0; k < size; ++k) {
        C[i * size + j] += A[i * size + k] * B[k * size + j];
      }

  clock_t stop = clock();
  // auto stop = std::chrono::high_resolution_clock::now();

  double elapsed = ((float)stop - start) * 1000.0 / CLOCKS_PER_SEC;
  // double elapsed = (stop - start).count();
  std::cout << "\nExecution time: " << elapsed << "s" << std::endl;

  return C;
}

template <typename T>
T* strassen_matmul(T* A, T* B, int size) {
  std::cout << "\n\nStrassen matrix multiplication.";
  int subsize = size * 0.5;

  T *A11{new T[subsize * subsize]}, *A12{new T[subsize * subsize]},
      *A21{new T[subsize * subsize]}, *A22{new T[subsize * subsize]};

  T *B11{new T[subsize * subsize]}, *B12{new T[subsize * subsize]},
      *B21{new T[subsize * subsize]}, *B22{new T[subsize * subsize]};

  T *C11{new T[subsize * subsize]}, *C12{new T[subsize * subsize]},
      *C21{new T[subsize * subsize]}, *C22{new T[subsize * subsize]};
  T* C{new T[size * size]};

  T *P1{new T[subsize * subsize]}, *P2{new T[subsize * subsize]},
      *P3{new T[subsize * subsize]}, *P4{new T[subsize * subsize]},
      *P5{new T[subsize * subsize]}, *P6{new T[subsize * subsize]},
      *P7{new T[subsize * subsize]};

  T *temp1{new T[subsize * subsize]}, *temp2{new T[subsize * subsize]};

  // A and B blocks initialization

  for (int i = 0; i < subsize; ++i) {
    for (int j = 0; j < subsize; ++j) {
      A11[i * subsize + j] = A[i * size + j];
      B11[i * subsize + j] = B[i * size + j];
      C11[i * subsize + j] = 0;
    }
  }

  for (int i = 0; i < subsize; ++i) {
    for (int j = 0; j < subsize; ++j) {
      A12[i * subsize + j] = A[i * size + j + subsize];
      B12[i * subsize + j] = B[i * size + j + subsize];
      C12[i * subsize + j] = 0;
    }
  }

  for (int i = 0; i < subsize; ++i) {
    for (int j = 0; j < subsize; ++j) {
      A21[i * subsize + j] = A[(i + subsize) * size + j];
      B21[i * subsize + j] = B[(i + subsize) * size + j];
      C21[i * subsize + j] = 0;
    }
  }

  for (int i = 0; i < subsize; ++i) {
    for (int j = 0; j < subsize; ++j) {
      A22[i * subsize + j] = A[(i + subsize) * size + j + subsize];
      B22[i * subsize + j] = B[(i + subsize) * size + j + subsize];
      C22[i * subsize + j] = 0;
    }
  }

  // #ifdef DEBUG

  //   std::cout << "\nA11: \n";
  //   print_matrix(A11, subsize);
  //   std::cout << "\nA12: \n";
  //   print_matrix(A12, subsize);
  //   std::cout << "\nA21: \n";
  //   print_matrix(A21, subsize);
  //   std::cout << "\nA22: \n";
  //   print_matrix(A22, subsize);

  //   std::cout << "\nB11: \n";
  //   print_matrix(B11, subsize);
  //   std::cout << "\nB12: \n";
  //   print_matrix(B12, subsize);
  //   std::cout << "\nB21: \n";
  //   print_matrix(B21, subsize);
  //   std::cout << "\nB22: \n";
  //   print_matrix(B22, subsize);

  // #endif

  clock_t start = clock();

  for (int i = 0; i < subsize; ++i) {
    for (int j = 0; j < subsize; ++j) {
      for (int k = 0; k < subsize; ++k) {
        // P1 = A11 (B12 - B22)
        P1[i * subsize + k] = A11[i * subsize + j] *
                              (B12[j * subsize + k] + B22[j * subsize + k]);
        // P2 = (A11 + A12) B22
        P2[i * subsize + k] = (A11[i * subsize + j] + A12[i * subsize + j]) *
                              B22[j * subsize + k];
        // P3 = (A21 + A22) B11
        P3[i * subsize + k] = (A21[i * subsize + j] + A22[i * subsize + j]) *
                              B11[j * subsize + k];
        // P4 = A22 (B21 - B11)
        P4[i * subsize + k] = A22[i * subsize + j] *
                              (B21[j * subsize + k] - B11[j * subsize + k]);
        // P5 = (A11 + A22)(B11 + B22)
        P5[i * subsize + k] = (A11[i * subsize + j] + A22[i * subsize + j]) *
                              (B11[j * subsize + k] + B22[j * subsize + k]);
        // P6 = (A12 - A22)(B21 + B22)
        P6[i * subsize + k] = (A12[i * subsize + j] - A22[i * subsize + j]) *
                              (B21[j * subsize + k] + B22[j * subsize + k]);
        // P7 = (A11 - A21)(B11 + B12)
        P7[i * subsize + k] = (A11[i * subsize + j] - A21[i * subsize + j]) *
                              (B11[j * subsize + k] + B12[j * subsize + k]);
      }
    }
  }

  // #ifdef DEBUG

  //   std::cout << "\nP1: \n";
  //   print_matrix(P1, subsize);
  //   std::cout << "\nP2: \n";
  //   print_matrix(P2, subsize);
  //   std::cout << "\nP3: \n";
  //   print_matrix(P3, subsize);
  //   std::cout << "\nP4: \n";
  //   print_matrix(P4, subsize);
  //   std::cout << "\nP5: \n";
  //   print_matrix(P5, subsize);
  //   std::cout << "\nP6: \n";
  //   print_matrix(P6, subsize);
  //   std::cout << "\nP7: \n";
  //   print_matrix(P7, subsize);

  // #endif

  for (int i = 0; i < subsize; ++i) {
    for (int j = 0; j < subsize; ++j) {
      // C11 = P5 + P4 - P2 + P6
      C[i * size + j] += P5[i * subsize + j] + P4[i * subsize + j] -
                         P2[i * subsize + j] + P6[i * subsize + j];
      // C12 = P1 + P2
      C[(i + subsize) * size + j] += P1[i * subsize + j] + P2[i * subsize + j];
      // C21 = P3 + P4
      C[i * size + j + subsize] += P3[i * subsize + j] + P4[i * subsize + j];

      // C22 = P1 + P5 - P3 - P7
      C[(i + subsize) * size + j + subsize] +=
          P1[i * subsize + j] + P5[i * subsize + j] - P3[i * subsize + j] -
          P7[i * subsize + j];
    }
  }

  clock_t stop = clock();

  delete[] temp1;
  delete[] temp2;

  delete[] P1;
  delete[] P2;
  delete[] P3;
  delete[] P4;
  delete[] P5;
  delete[] P6;
  delete[] P7;

  double elapsed = ((float)stop - start) * 1000.0 / CLOCKS_PER_SEC;
  // double elapsed = (stop - start).count();
  std::cout << "\nExecution time: " << elapsed << "s" << std::endl;

  return C;
}

// ===================================================

int main() {
  int size = SIZE;
  int *A{new int[size * size]}, *B{new int[size * size]};
  int *C, *D;

  for (int i = 0; i < size; ++i)
    for (int j = 0; j < size; ++j) {
      A[i * size + j] = i + 1;
      B[i * size + j] = i + j;
      // C[i * size + j] = 0;
    }

#ifdef DEBUG
  std::cout << "\nA: \n";
  print_matrix(A, size);
  std::cout << "\nB: \n";
  print_matrix(B, size);
#endif

  C = naive_matmul(A, B, size);
#ifdef DEBUG
  std::cout << "\nProduct:\n";
  print_matrix(C, size);
#endif

  D = strassen_matmul(A, B, size);
#ifdef DEBUG
  std::cout << "\nProduct:\n";
  print_matrix(D, size);
#endif

  delete[] A;
  delete[] B;
  delete[] C;
  delete[] D;

  return 0;
}