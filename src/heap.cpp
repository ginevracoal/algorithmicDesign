#include "../inc/binary_heap.h"
#include "../inc/heapsort.h"

#include <iostream>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& V) {
  out << "[" << V[0];

  for (size_t i = 1; i < V.size(); i++) {
    out << "," << V[i];
  }

  out << "]";

  return out;
}

int main(int argc, char* argv[]) {
  std::vector<int> A = {2, 1, -4, 7, 8, 5, 1, 100, 70, 35, 80, 64};

  {
    std::cout << "MinHeap" << std::endl
              << " - build minHeap from " << A << std::endl;

    BinaryHeap<int> Hmin(A);

    size_t node = 7;
    int value = -9;

    std::cout << "   " << Hmin << std::endl
              << " - decrease value of node " << node << " to " << value
              << std::endl;

    Hmin.change_value(node, value);

    std::cout << "   " << Hmin << std::endl << " - delete root" << std::endl;

    Hmin.delete_root();

    std::cout << "   " << Hmin << std::endl;
  }

  {
    std::cout << "MaxHeap" << std::endl
              << " - build maxHeap from " << A << std::endl;

    BinaryHeap<int, ReverseValueComparator> Hmax(A);

    size_t node = 7;
    int value = 900;

    std::cout << "   " << Hmax << std::endl
              << " - increase value of node " << node << " to " << value
              << std::endl;

    Hmax.change_value(node, value);

    std::cout << "   " << Hmax << std::endl << " - delete root" << std::endl;

    Hmax.delete_root();

    std::cout << "   " << Hmax << std::endl;
  }

  {
    std::cout << "AssociativeMinHeap" << std::endl;
    AssociativeBinaryHeap<int> AHmin(A);

    std::cout << "   " << AHmin << std::endl;

    std::cout << "   "
              << "[" << AHmin.index(0);

    for (size_t i = 1; i < AHmin.size(); i++) {
      std::cout << "," << AHmin.index(i);
    }

    std::cout << "]" << std::endl;

    for (size_t i = 0; i < AHmin.size(); i++) {
      std::cout << "   " << AHmin[i] << " == " << A[AHmin.index(i)];
      if (AHmin[i] == A[AHmin.index(i)]) {
        std::cout << "\tOK" << std::endl;
      } else {
        std::cout << "\tNO" << std::endl;
      }
    }

    size_t node = 7;
    int value = -9;

    std::cout << "   " << AHmin << std::endl
              << " - decrease value of node " << node << " to " << value
              << std::endl;

    AHmin.change_value(node, value);

    std::cout << "   " << AHmin << std::endl << " - delete root" << std::endl;

    AHmin.delete_root();

    std::cout << "   " << AHmin << std::endl;
  }

  {
    std::cout << "HeapSort(" << A << ") = ";

    heapsort(A);

    std::cout << A << std::endl;
  }

  return 0;
}
