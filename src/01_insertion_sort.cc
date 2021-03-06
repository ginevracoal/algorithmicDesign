/* Insertion Sort
time complexity O(n^2)
*/

// #include <cstdlib>
#include <iostream>

// print an array of size n
template <typename T>
void print_array(T* array, int n) {
  for (int i = 0; i < n; ++i) {
    std::cout << array[i] << " ";
  }
  std::cout << std::endl;
}

template <typename T>
void insertion_sort(T* array, int n) {  // O(n^2)
  int i, j, k;
  for (j = 1; j < n; ++j) {           // n times
    k = array[j];                     // O(1)
    i = j - 1;                        // O(1)
    while (i >= 0 && array[i] > k) {  // at most j-1 times
      array[i + 1] = array[i];        // O(1)
      i--;                            // O(1)
    }
    array[i + 1] = k;  // O(1)
  }
}

int main() {
  int array[] = {1, 5, 26, 7, 32, 2, 14, 8};
  int length = 8;

  std::cout << "\nInitial array: ";
  print_array(array, length);

  insertion_sort(array, length);

  std::cout << "\nSorted array: ";
  print_array(array, length);
  return 0;
}