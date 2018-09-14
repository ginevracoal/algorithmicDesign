#ifndef __HEAPSORT_HPP__
#define __HEAPSORT_HPP__

#include <memory>

#include "binary_heap.h"

/**
 * An implementation for the heapsort algorithm.
 *
 * @param container the container to be sorted (must be indexable).
 * @return a reference to the sorted container.
 */
template <typename T, template <typename, typename> class C>
C<T, std::allocator<T> >& heapsort(C<T, std::allocator<T> >& container) {
  BinaryHeap<T, ReverseValueComparator> H(container);

  while (H.size() > 0) {
    container[H.size()] = H.delete_root();
  }

  return container;
}

#endif  // __HEAPSORT_HPP__
