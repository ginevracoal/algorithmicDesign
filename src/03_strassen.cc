/**
 * Naive matrix multiplication algorithm and Strassen mutiplication algorithm.
 * The asympthotic complexities for naive and Strassen algorithms respectively
 * are O(N^3) and O(N^log_2(7)).
 * This method only applies to square matrices whose size is a power of 2.
*/

#include <time.h>
#include <cstdlib>  //only for cout
#include <iostream>

#define SIZE 4  // it always has to be a power of 2

// =====================================================
// FUNCTION DECLARATIONS

template <typename T>
void print_matrix(T* A, int size);

template <typename T>
void sum(T* A, T* B, T* C, int size);

template <typename T>
void diff(T* A, T* B, T* C, int size);

template <typename T>
void naive_matmul(T* A, T* B, T* C, int size);

template <typename T>
void strassen_matmul(T* A, T* B, T* D, int size);

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
void sum(T* A, T* B, T* C, int size) {
  // T* C{new T[size * size]};
  for (int i = 0; i < size; ++i)
    for (int j = 0; j < size; ++j)
      C[i * size + j] = A[i * size + j] + B[i * size + j];
}

template <typename T>
void diff(T* A, T* B, T* C, int size) {
  // T* C{new T[size * size]};
  for (int i = 0; i < size; ++i)
    for (int j = 0; j < size; ++j)
      C[i * size + j] = A[i * size + j] - B[i * size + j];
  // return C;
}

template <typename T>
void naive_matmul(T* A, T* B, T* C, int size) {
  // T* C{new T[size * size]};

  for (int i = 0; i < size; ++i)
    for (int j = 0; j < size; ++j)
      for (int k = 0; k < size; ++k)
        C[i * size + j] += A[i * size + j] * B[j * size + k];

  // return C;
}

template <typename T>
void strassen_matmul(T* A, T* B, T* D, int size) {
  int subsize = size * 0.5;

  T *A11{new T[subsize * subsize]}, *A12{new T[subsize * subsize]},
      *A21{new T[subsize * subsize]}, *A22{new T[subsize * subsize]};

  T *B11{new T[subsize * subsize]}, *B12{new T[subsize * subsize]},
      *B21{new T[subsize * subsize]}, *B22{new T[subsize * subsize]};

  // T *C11{new T[subsize * subsize]}, *C12{new T[subsize * subsize]},
  //     *C21{new T[subsize * subsize]}, *C22{new T[subsize * subsize]};

  // T* C{new T[size * size]};

  T *P1{new T[subsize * subsize]}, *P2{new T[subsize * subsize]},
      *P3{new T[subsize * subsize]}, *P4{new T[subsize * subsize]},
      *P5{new T[subsize * subsize]}, *P6{new T[subsize * subsize]},
      *P7{new T[subsize * subsize]};

  T *tmp1{new T[subsize * subsize]}, *tmp2{new T[subsize * subsize]};

  // A and B blocks initialization

  for (int i = 0; i < subsize; ++i) {
    for (int j = 0; j < subsize; ++j) {
      A11[i * subsize + j] = A[i * size + j];
      B11[i * subsize + j] = B[i * size + j];

      A12[i * subsize + j] = A[i * size + j + subsize];
      B12[i * subsize + j] = B[i * size + j + subsize];

      A21[i * subsize + j] = A[(i + subsize) * size + j];
      B21[i * subsize + j] = B[(i + subsize) * size + j];

      A22[i * subsize + j] = A[(i + subsize) * size + j + subsize];
      B22[i * subsize + j] = B[(i + subsize) * size + j + subsize];
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

  // P1 = A11 (B12 - B22)
  diff(B12, B22, tmp1, subsize);
  naive_matmul(A11, tmp1, P1, subsize);

  // P2 = (A11 + A12) B22
  sum(A11, A12, tmp1, subsize);
  naive_matmul(tmp1, B22, P2, subsize);

  // P3 = (A21 + A22) B11
  sum(A21, A22, tmp1, subsize);
  naive_matmul(tmp1, B11, P3, subsize);

  // P4 = A22 (B21 - B11)
  diff(B21, B11, tmp1, subsize);
  naive_matmul(A22, tmp1, P4, subsize);

  // P5 = (A11 + A22)(B11 + B22)
  sum(A11, A22, tmp1, subsize);
  sum(B11, B22, tmp2, subsize);
  naive_matmul(tmp1, tmp2, P5, subsize);

  // P6 = (A12 - A22)(B21 + B22)
  diff(A12, A22, tmp1, subsize);
  sum(B21, B22, tmp2, subsize);
  naive_matmul(tmp1, tmp2, P6, subsize);

  // P7 = (A11 - A21)(B11 + B12)
  diff(A11, A21, tmp1, subsize);
  sum(B11, B12, tmp2, subsize);
  naive_matmul(tmp1, tmp2, P7, subsize);

  // #ifdef DEBUG

  //   std::cout << "\nP1:\n";
  //   print_matrix(P1, subsize);
  //   std::cout << "\nP2:\n";
  //   print_matrix(P2, subsize);
  //   std::cout << "\nP3:\n";
  //   print_matrix(P3, subsize);
  //   std::cout << "\nP4:\n";
  //   print_matrix(P4, subsize);
  //   std::cout << "\nP5:\n";
  //   print_matrix(P5, subsize);
  //   std::cout << "\nP6:\n";
  //   print_matrix(P6, subsize);
  //   std::cout << "\nP7:\n";
  //   print_matrix(P7, subsize);

  // #endif

  for (int i = 0; i < subsize; ++i) {
    for (int j = 0; j < subsize; ++j) {
      // D11 = P5 + P4 - P2 + P6
      D[i * size + j] = P5[i * subsize + j] + P4[i * subsize + j] -
                        P2[i * subsize + j] + P6[i * subsize + j];

      // D12 = P1 + P2
      D[i * size + j + subsize] = P1[i * subsize + j] + P2[i * subsize + j];

      // D21 = P3 + P4
      D[(i + subsize) * size + j] = P3[i * subsize + j] + P4[i * subsize + j];

      // D22 = P1 + P5 - P3 - P7
      D[(i + subsize) * size + j + subsize] =
          P1[i * subsize + j] + P5[i * subsize + j] - P3[i * subsize + j] -
          P7[i * subsize + j];
    }
  }

  delete[] tmp1;
  delete[] tmp2;

  delete[] A11;
  delete[] A12;
  delete[] A21;
  delete[] A22;
  delete[] B11;
  delete[] B12;
  delete[] B21;
  delete[] B22;

  delete[] P1;
  delete[] P2;
  delete[] P3;
  delete[] P4;
  delete[] P5;
  delete[] P6;
  delete[] P7;

  // double elapsed = ((float)stop - start) * 1000.0 / CLOCKS_PER_SEC;
  // // double elapsed = (stop - start).count();
  // std::cout << "\nExecution time: " << elapsed << "s" << std::endl;

  // return C;
}

// ===================================================

int main() {
  int size = SIZE;
  int *A{new int[size * size]}, *B{new int[size * size]};
  int *C{new int[size * size]}, *D{new int[size * size]};

  clock_t start, stop;
  double elapsed;

  // INITIALIZATION

  for (int i = 0; i < size; ++i)
    for (int j = 0; j < size; ++j) {
      A[i * size + j] = i + 1;
      B[i * size + j] = i + j;
      C[i * size + j] = 0;
      D[i * size + j] = 0;
    }

#ifdef DEBUG
  std::cout << "\nA: \n";
  print_matrix(A, size);
  std::cout << "\nB: \n";
  print_matrix(B, size);
#endif

  // NAIVE ALGORITHM

  start = clock();
  naive_matmul(A, B, C, size);
  stop = clock();

#ifdef DEBUG
  std::cout << "\nNaive product:\n";
  print_matrix(C, size);
#endif

  elapsed = ((float)stop - start) * 1000.0 / CLOCKS_PER_SEC;
  std::cout << "\nNaive execution time: " << elapsed << "s" << std::endl;

  // STRASSEN ALGORITHM

  start = clock();
  strassen_matmul(A, B, D, size);
  stop = clock();

#ifdef DEBUG
  std::cout << "\nStrassen product:\n";
  print_matrix(D, size);
#endif

  elapsed = ((float)stop - start) * 1000.0 / CLOCKS_PER_SEC;
  std::cout << "\nStrassen execution time: " << elapsed << "s" << std::endl;

  delete[] A;
  delete[] B;
  delete[] C;
  delete[] D;

  return 0;
}