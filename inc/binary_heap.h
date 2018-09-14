/*
A Binary Min Heap is a complete binary tree with the following property:
the key at root must be minimum among all keys and the same property must hold
recursivey for the nodes inside the tree.
*/

#ifndef __BINARY_HEAP_HPP__
#define __BINARY_HEAP_HPP__

/*! \mainpage BinaryHeap C++ Implementation
 *
 * See Class List entry on top menu.
 */

#include <cstddef>
#include <iterator>
#include <memory>
#include <stdexcept>

/**
 * \class ValueComparator
 * \brief A basic comparator class
 * \tparam T type to be compared
 *
 * This template is meant to provide a static method to
 * compare two objects of the template parameter type.
 *
 */
template <typename T>
class ValueComparator {
 public:
  /**
   * A static method to compare two objects of type T.
   * @param a an object of type T.
   * @param b an object of type T.
   * @return if (a<b), then -1; if (b<a), then 1;
   *         otherwise 0
   */
  static int cmp(const T& a, const T& b) {
    if (a < b) {
      return -1;
    }

    if (b < a) {
      return 1;
    }

    return 0;
  }
};

/**
 * \class ReverseValueComparator
 * \brief Another basic comparator class
 * \tparam T type to be compared
 *
 * This template provides the inverse of the
 * method ValueComparator<T>::cmp.
 */
template <typename T>
class ReverseValueComparator {
 public:
  static int cmp(const T& a, const T& b) {
    return -ValueComparator<T>::cmp(a, b);
  }
};

/**
 * \class BinaryHeap
 * \brief An implementation for the binary heap data structure.
 * \tparam T type of the values stored by the heap
 * \tparam Comparator template that provides a method to compare objects of type
 * T
 *
 * This template implements the binary heap data structure.
 * It requires two parameters: the type of node keys and
 * a comparator for this class.
 */
template <typename T, template <typename> class Comparator = ValueComparator>
class BinaryHeap {
 protected:
  T* container;          /**< An array that stores the heap nodes */
  std::size_t max_size;  /**< The maximum number of nodes in the binary heap */
  std::size_t cont_size; /**< The number of nodes in the binary heap */

  /**
   * Returns true if the parameter is the index of the root.
   *
   * @param An index for the container array
   * @return True if the parameter is the index of the root of the binary heap
   */
  inline bool is_root(const size_t& index) const { return index == 0; }

  /** Returns the index of the left son of a node.
   *
   * @param index An index for the container array
   * @return the index of the left son of the node pointed by the parameter
   */
  inline size_t left_son(const size_t& index) const { return 2 * index + 1; }

  /**
   * Returns the index of the right son of a node.
   *
   * @param index An index for the container array
   * @return the index of the right son of the node pointed by the parameter
   */
  inline size_t right_son(const size_t& index) const { return 2 * (index + 1); }

  /**
   * Returns the index of the father of a node.
   *
   * @param index A index for the container array
   * @return the index of the father of the node pointed by the parameter
   */
  inline size_t father(const size_t index) const {
    if (is_root(index)) {
      return index;
    }

    return (index - 1) / 2;
  }

  /**
   * Fixes the heap property in a subtree.
   * When the subtrees rooted on the sons of a node <tt>n</tt> satisfy the heap
   * property,
   * this method fixes the heap property of the subtree rooted <tt>n</tt>
   * itself.
   * Let <tt>m</tt> be the son of <tt>n</tt> having the minimum value among its
   * siblings. If the value of <tt>m</tt> is greater than that of <tt>n</tt>,
   * then
   * the heap property is satisfied. Otherwise, this method swaps <tt>n</tt> and
   * <tt>m</tt> and recursively considers <tt>m</tt>.
   *
   * @param index the index of <tt>n</tt> in the container array
   */
  void heapify(size_t index) {
    if (index >= this->cont_size) {
      throw std::out_of_range("Index out of range.");
    }

    do {
      // compute the index of the son that has minimum value
      // among its siblings.

      // get the putative index of the left son of the
      // considered node
      size_t min_son_idx = left_son(index);

      // if the considered node has not a left son
      if (min_son_idx >= this->cont_size) {
        // get the putative index of the right son of the
        // considered node
        min_son_idx = right_son(index);

        // if the considered node has not a left son
        if (min_son_idx >= this->cont_size) {
          // the heap property is already preserved and
          // the method concludes its execution
          return;
        }

      } else {
        // get the putative index of the right son of the
        // considered node
        size_t right_idx = right_son(index);

        // if the considered node has both left and right sons and
        // the right son is smaller than the left one with respect
        // to their value
        if (right_idx < this->cont_size &&
            Comparator<T>::cmp(this->container[right_idx],
                               this->container[min_son_idx]) < 0) {
          // the minimal node is the right son.
          min_son_idx = right_idx;
        }
      }

      // if the son having the minimal value among its siblings has
      // a value greater than that of the considered node
      if (Comparator<T>::cmp(this->container[min_son_idx],
                             this->container[index]) >= 0) {
        // the heap property is already preserved and
        // the method concludes the method execution
        return;
      }

      // swap the son having the minimum value among its siblings
      // and the considered node.
      this->swap(min_son_idx, index);

      index = min_son_idx;
    } while (true);
  }

  /**
   * Fixes heap property over the whole binary heap.
   */
  void build_heap() {
    for (size_t i = this->cont_size / 2; i > 0; --i) {
      heapify(i);
    }
    heapify(0);
  }

  /**
   * Fixes heap property by moving the minimal value toward the root.
   * If we decrease the value of a node <tt>n</tt> with respect to the
   * template parameter <tt>Comparator</tt>, then we may need to
   * push the value <tt>n</tt> toward the root to fix the heap
   * property. This method performs this operation until the
   * heap property does not hold.
   *
   * @param index the index of <tt>n</tt> in the container array
   */
  void fix_heap(size_t index) {
    size_t findex = father(index);

    // while the current node is not the heap root and
    // its value is greater than that of its father
    while (index != 0 &&
           Comparator<T>::cmp(this->container[index], this->container[findex]) <
               0) {
      // swap the current node and its father
      this->swap(index, findex);

      // consider the current node father and repeat
      index = findex;
      findex = father(index);
    }
  }

  /**
   * Swap two node in the binary heap.
   * This method is virtual to easy BinaryHeap extensions.
   *
   * @param idx_a index in the container array of the first node to be swap
   * @param idx_a index in the container array of the second node to be swap
   */
  virtual void swap(const size_t idx_a, const size_t idx_b) {
    std::swap(this->container[idx_a], this->container[idx_b]);
  }

  /**
   * Copy all the elements of a generic container into this object's container.
   * Copy all the elements of a generic container into the <tt>container</tt>
   * member.
   * This method does not guarantee that the heap property holds.
   *
   * @tparam C type of the input container
   * @param container a generic container that stores all the value to be
   * inserted into the heap
   */
  template <template <typename, typename> class C>
  void fill_heap(const C<T, std::allocator<T> >& container) {
    // update the maximum size of this binary heap
    this->max_size = container.size();

    delete[] this->container;

    // allocate the array that will store heap nodes
    this->container = new T[this->max_size];

    // copy each value into the <tt>container</tt> member
    for (typename C<T, std::allocator<T> >::const_iterator it =
             std::begin(container);
         it != std::end(container); ++it) {
      this->container[this->cont_size++] = *it;
    }
  }

  /**
   * Insert a new node into the binary heap.
   * This method inserts a new node into the each and preserve the heap
   * property.
   *
   * @param value the value to be inserted into the binary heap.
   */
  void bh_insert(const T& value) {
    // if the maximum size of the binary heap has been reached
    if (this->cont_size == this->max_size) {
      // throw an exception
      throw std::out_of_range();
    }

    // update the size of the binary heap
    size_t idx = this->cont_size++;

    // insert the new value in the "last" leaf of the tree
    this->container[idx] = value;

    // fix the heap property upward
    fix_heap(idx);
  }

 public:
  /**
   * An empty constructor.
   */
  BinaryHeap() : container(NULL), max_size(0), cont_size(0) {}

  /**
   * A constructor that builds a heap from a container.
   *
   * This constructor builds a binary heap whose nodes contain all the
   * values stored in a container.
   *
   * @param container contains the values to be included into the heap.
   */
  template <template <typename, typename> class C>
  BinaryHeap(const C<T, std::allocator<T> >& container)
      : container(NULL), max_size(0), cont_size(0) {
    fill_heap(container);

    build_heap();
  }

  /**
   * A constructor that builds an empty heap.
   * This constructor builds an empty binary heap having a give
   * maximum size.
   *
   * @param max_size is the maximum size of the built heap.
   */
  BinaryHeap(const size_t max_size)
      : container(NULL), max_size(0), cont_size(0) {
    this->max_size = max_size;
    this->container = new T[this->max_size];
  }

  /**
   * The destructor.
   */
  virtual ~BinaryHeap() {
    cont_size = 0;
    max_size = 0;
    delete[] container;
  }

  /**
   * The destructor.
   */
  void insert(const T& key) { this->bh_insert(key); }

  /**
   * Return the value of the heap root.
   * This method returns the value of the root of the binary heap.
   *
   * @return the root value.
   */
  const T& root() const {
    if (this->cont_size == 0) {
      throw std::out_of_range("Index out of range.");
    }

    return this->container[0];
  }

  /**
   * Delete the root of the binary heap.
   * This method delete the heap root, preserving the heap property, and
   * returns its value.
   *
   * @return the value of the removed root.
   */
  const T& delete_root() {
    // if the heap is empty, then throw an exception
    if (this->cont_size == 0) {
      throw std::out_of_range("Index out of range.");
    }

    // decrease the heap size
    this->cont_size--;

    // if the heap is still not empty
    if (this->cont_size > 0) {
      // swap the root and the old valid node in the <tt>container</tt> array
      this->swap(0, this->cont_size);

      // fix the heap property downward
      heapify(0);
    }

    // return the value of the removed root
    return this->container[this->cont_size];
  }

  /**
   * Change the value of a node.
   * This method allows to decrease, according to the <tt>Comparator</tt> class,
   * the value of a node. If the new value is greater than that of the
   * considered node, then an exception is thrown.
   */
  void change_value(const size_t& index, const T& value) {
    if (this->cont_size <= index) {
      throw std::out_of_range("Index out of range.");
    }

    if (Comparator<T>::cmp(this->container[index], value) < 0) {
      throw std::runtime_error(
          "This data structure does not support this value assignament!!!");
    }

    // update the value
    this->container[index] = value;

    // fix the heap property toward root
    fix_heap(index);
  }

  /**
   * Return the size of the heap.
   *
   * @return the number of nodes in the heap.
   */
  inline size_t size() const { return this->cont_size; }

  /**
   * Index heap nodes.
   * This method allows to index the nodes in the binary heap.
   *
   * @param index index of the node to be accessed
   * @return the value of the node in position <tt>index</tt>
   */
  const T& operator[](const size_t index) const {
    if (index < this->cont_size) {
      return this->container[index];
    }

    throw std::out_of_range("Index out of range.");
  }

  /**
   * Assignment method
   * This method is used to copy a binary heap into a <tt>BinaryHeap</tt>
   * variable.
   *
   * @param orig the binary heap to be used as model
   * @return a reference to this object.
   */
  const BinaryHeap<T, Comparator>& operator=(
      const BinaryHeap<T, Comparator>& orig) {
    delete[] container;

    this->cont_size = orig.cont_size;
    this->max_size = orig.max_size;
    this->container = new T[this->max_size];

    std::copy(orig.container, orig.container + orig.max_size, this->container);

    return *this;
  }
};

/**
 * \class AssociativeBinaryHeap
 * \brief A BinaryHeap class that allows to find a specific value inside the
 * heap.
 * \tparam T type of the values stored by the heap
 * \tparam Comparator template that provides a method to compare objects of type
 * T
 *
 * This template extends the binary heap data structure and allows to
 * find the index of a specific node.
 */
template <typename T, template <typename> class Comparator = ValueComparator>
class AssociativeBinaryHeap : public BinaryHeap<T, Comparator> {
 protected:
  size_t* map;

  void swap(const size_t idx_a, const size_t idx_b) override {
    BinaryHeap<T, Comparator>::swap(idx_a, idx_b);
    std::swap(map[idx_a], map[idx_b]);
  }

 public:
  template <template <typename, typename> class C>
  AssociativeBinaryHeap(const C<T, std::allocator<T> >& container)
      : BinaryHeap<T, Comparator>(), map(NULL) {
    this->fill_heap(container);

    map = new size_t[this->max_size];

    for (size_t i = 0; i < this->max_size; i++) {
      map[i] = i;
    }

    this->build_heap();
  }

  AssociativeBinaryHeap(const size_t max_size)
      : BinaryHeap<T, Comparator>(max_size), map(NULL) {
    map = new size_t[this->max_size];
  }

  ~AssociativeBinaryHeap() { delete[] map; }

  void insert(const T& key) {
    this->map[this->cont_size] = this->cont_size;

    this->bh_insert(key);
  }

  const AssociativeBinaryHeap<T, Comparator>& operator=(
      const AssociativeBinaryHeap<T, Comparator>& orig) {
    BinaryHeap<T, Comparator>::operator=(orig);

    delete[] this->map;

    this->map = new T[this->max_size];

    for (size_t i = 0; i < this->max_size; i++) {
      this->map[i] = orig.map[i];
    }

    return *this;
  }

  const size_t& index(const size_t pos) const { return this->map[pos]; }
};

template <typename T, template <typename> class Comparator>
std::ostream& operator<<(std::ostream& out,
                         const BinaryHeap<T, Comparator>& H) {
  out << "BinaryHeap[";
  if (H.size() > 0) {
    out << H[0];
  }

  for (size_t i = 1; i < H.size(); i++) {
    out << "," << H[i];
  }

  out << "]";
  return out;
}

#endif
