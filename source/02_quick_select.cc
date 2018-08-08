/* TO DO:

 - l'indice finale è avanti di un numeros
 - controllare se funziona con due indici uguali
 - scegliere cosa stampare nel debug
 - definire una classe pair!!
*/

// =====================================================

/* Quickselect algorithm finds the kth smallest element in an unordered list. It
 uses the same approach of quicksort, choosing one element as a pivot and
 partitionting the data in two based on this pivot.
 This method only makes recursion on the half containing the element on
 interest, thus reducing the worst case complexity from O(n logn) to O(n).
*/

#include <math.h>   // ceil function
#include <cstdlib>  // only for cout
#include <iostream>

// =====================================================
// FUNCTION DECLARATIONS

template <typename T>
void print(T* A, int length);

template <typename T>
void insertion_sort(T* A, int begin, int end);

template <typename T>
int select_pivot(T* A, int j, int begin, int end);

template <typename T>
void swap(T& a, T& b);

template <typename T>
std::pair<int, int> tri_partition(T* A, int begin, int end, int pivotIdx);

template <typename T>
int select(T* A, int j, int begin, int end);

// =====================================================
// FUNCTION DEFINITIONS

template <typename T>
void print(T* A, int begin, int end) {
  for (int i = begin; i < end; ++i) {
    std::cout << A[i] << " ";
  }
  // std::cout << std::endl;
}

template <typename T>
void insertion_sort(T* A, int begin, int end) {
#ifdef DEBUG
  std::cout << "\n  Insertion sort: ";
  print(A, begin, end);
#endif

  int i, j, k;
  for (j = begin; j < end; ++j) {
    k = A[j];
    i = j - 1;
    while (i >= begin && A[i] > k) {
      A[i + 1] = A[i];
      i--;
    }
    A[i + 1] = k;
  }

#ifdef DEBUG
  std::cout << "-> ";
  print(A, begin, end);
  std::cout << std::endl;
#endif
}

// finds the median of the medians from begin to end, given the index j, which
// is the maximum size of each block
template <typename T>
int select_pivot(T* A, int begin, int end, int j) {
  int n_blocks = ceil((end - begin) / (double)j);

  std::cout << "\n\n[select pivot(A, " << begin << ", " << end << ", " << j
            << ")]";
  std::cout << "\n n blocks: " << n_blocks << std::endl;
  // array contaning the medians for each block
  int* medians = new T[n_blocks];
  // std::vector<int> medians;

  int cbegin, cend;
  for (int i = 0; i < n_blocks; i++) {
    // beginning point for each block
    cbegin = begin + j * i;
    if (cbegin + j < end)
      cend = cbegin + j;
    else
      cend = end;

#ifdef DEBUG
    std::cout << "\n  indexes " << cbegin << "-" << cend;
#endif

    // apply IS to each block
    insertion_sort(A, cbegin, cend);

    // store the i-th median
    medians[i] = A[(cend + cbegin) / 2];
  }

  // calculate the median of the medians
  std::cout << "\n Medians: ";
  print(medians, 0, n_blocks);
  T median = select(medians, j, 0, n_blocks);
  delete[] medians;  // the array has to be deallocated
  return median;
}

// swap elements on an array given two indexes
template <typename T>
void swap(T& a, T& b) {
  T tmp = a;
  a = b;
  b = tmp;
}

// tri_partition partitions A[] in three parts:
// 1) A[begin,...,k_1-1] contains all elements smaller than the pivot
// 2) A[k_1,..., k_2] contains all occurrences of the pivot
// 3) A[k_2+1,...,end] contains all elements greater than the pivot
// finally it returns k_1 and k_2
template <typename T>
std::pair<int, int> tri_partition(T* A, int begin, int end, int pivotIdx) {
  T pivot = A[pivotIdx];  // pivot value
  swap(A[pivotIdx], A[end - 1]);

#ifdef DEBUG
  std::cout << "\ntri-partition on A: ";
  print(A, begin, end);
  std::cout << "\n\n pivot = " << pivot;
#endif

  std::pair<int, int> k(begin, begin);
  for (int i = begin; i < end; i++) {
#ifdef DEBUG
    std::cout << "\n A: ";
    print(A, begin, end);
    std::cout << ", A[i] = " << A[i];
#endif

    if (A[i] < pivot) {
      swap(A[i], A[k.first]);
      k.first++;
      k.second++;
    } else if (A[i] == pivot && A[i] == A[i - 1]) {
      // swap(A[i], A[  k.second]);
      k.second++;
    }
  }

  swap(A[k.first], A[end - 1]);

  std::cout << "\n A: ";
  print(A, begin, end);
  std::cout << "\n k_1 = " << k.first << " and k_2 = " << k.second << std::endl;
  return k;
}

// returns the j-th smaller element of the array
template <typename T>
int select(T* A, int j, int begin, int end) {
  std::cout << "\n\nSelect on: ";
  print(A, begin, end);

  // if the block has dimension smaller than j
  if (end - begin < j) {
    insertion_sort(A, begin, end);
    return A[begin];
  }

  int pivot = select_pivot(A, begin, end, j);
  std::pair<int, int> k = tri_partition(A, begin, end, pivot);

  if (j < k.first)
    return select(A, j, begin, k.first - 1);
  else if (j > k.second)
    return select(A, j, k.second + 1, end);
  else if (j >= k.first && j <= k.second) {
    std::cout << std::endl
              << j << "-th smallest element is " << A[j] << std::endl;
    return A[j];
  }
}

// =====================================================

int main() {
  int A[] = {1, 5, 26, 7, 32, 2, 14, 8, 17, 15, 20, 22, 54};
  int length = 13;
  int idx = 5;

  std::cout << "\nInitial array: ";
  print(A, 0, length);

  select(A, idx, 0, length);

  return 0;
}