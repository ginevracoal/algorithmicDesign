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
int select_pivot(T* A, int begin, int end, int j);

template <typename T>
void swap(T& a, T& b);

template <typename T>
std::pair<int, int> tri_partition(T* A, int begin, int end, int pivot);

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
  for (j = begin; j < end; j++) {
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

  // std::cout << "\n\n[select pivot(A, " << begin << ", " << end << ", " << j
  //           << ")]";
  std::cout << "\n n blocks: " << n_blocks << std::endl;
  // array contaning the medians for each block
  int* medians = new T[n_blocks];
  // std::vector<int> medians;

  int cbegin, cend;
  for (int i = 0; i < n_blocks; ++i) {
    // beginning point for each block
    cbegin = begin + j * i;
    if (cbegin + j - 1 < end)
      cend = cbegin + j;
    else
      cend = end;

#ifdef DEBUG
    std::cout << "\n  indexes " << cbegin << "-" << cend;
#endif

    // reorder each block
    insertion_sort(A, cbegin, cend);

    // calculate the i-th median
    medians[i] = A[(cend + cbegin) / 2];
  }

  std::cout << "\n Medians: ";
  print(medians, 0, n_blocks);

  // median of the medians
  T median = select(medians, 0, n_blocks, (n_blocks + 1) / 2);
  delete[] medians;  // the array has to be deallocated
  return median;     // the median of the medians is the new pivot
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
std::pair<int, int> tri_partition(T* A, int begin, int end, int pivot) {
// T pivot = A[pivotIdx];  // pivot value
// swap(A[pivot], A[end]);

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

    if (A[i] <= pivot) {
      swap(A[i], A[k.first]);
      k.first++;
    }
  }

  // swap(A[k.first], A[end]);

  k.second = k.first;
  while (A[k.second] == pivot) {
    k.second++;
  }
  // k.second--;

  std::cout << "\n A: ";
  print(A, begin, end);
  std::cout << "\n k_1 = " << k.first << " and k_2 = " << k.second << std::endl;

  return k;
}

// returns the j-th smaller element of the array
template <typename T>
int select(T* A, int begin, int end, int j) {
  if (end - begin == 1 || j == 1) {
    return A[begin];
  }

  std::cout << "\n\nSelect on: ";
  print(A, begin, end);

  // if the block has dimension smaller than j
  // if (end - begin <= j) {
  //   std::cout << "\nblock smaller than j";
  //   insertion_sort(A, begin, end);
  //   // return A[(begin + end + 1) / 2];
  //   // return A[end - begin];
  //   return A[end];
  // }

  int pivot = select_pivot(A, begin, end, j);
  std::cout << "\n median of the medians: " << pivot;

  std::pair<int, int> k = tri_partition(A, begin, end, pivot);

  if (j < k.first) {
    std::cout << "\n j=" << j << " < k_1";
    return select(A, begin, k.first - 1, j);
  } else if (j > k.second) {
    std::cout << "\n j=" << j << " > k_2";
    return select(A, k.second, end, j);
  } else {
    std::cout << "\n j=" << j;
    return pivot;  // same as A[j]
  }
}

// =====================================================

int main() {
  // the first element is discarded
  int A[] = {1, 5, 26, 4, 32, 2, 14, 6, 8, 17, 15, 20, 22, 54, 23};
  int length = 15;
  int idx = 3;

  std::cout << "\nInitial array: ";
  print(A, 0, length);

  std::cout << "\n\n"
            << idx << "-th smallest element is " << select(A, 0, length, idx)
            << std::endl;

  return 0;
}