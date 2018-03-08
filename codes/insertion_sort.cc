#include <cstdlib>
#include <iostream>

void print_array(int array[], int length) {
  for (int i = 0; i < length; ++i) {
    std::cout << array[i] << " ";
  }
  std::cout << std::endl;
}

void insertion_sort(int array[], int length) {
  int i, j, k, tmp;
  for (j = 1; j < length; ++j) {
    k = array[j];
    i = j - 1;
    while (i >= 0 && array[i] > k) {
      array[i + 1] = array[i];
      i--;
    }
    array[i + 1] = k;
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