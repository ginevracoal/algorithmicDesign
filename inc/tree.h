#ifndef __TREE__
#define __TREE__

#include <chrono>
#include <iostream>
#include <iterator>  // to use std::iterator
#include <memory>    // for unique pointers
#include <vector>

using namespace std::chrono;  // for a more precise clock, which counts in ms

// =====================================================================
template <typename k_T>
class Tree {
 private:
  struct Node {
   private:
    k_T key;
    std::unique_ptr<Node> left, right;

    // parent points to node parent
    Node* parent;

   public:
    // NODE CONSTRUCTOR
    Node(const k_T& k, Node* p)
        : key{k}, left{nullptr}, right{nullptr}, parent{p} {}

    // COPY CONSTRUCTOR (deep copy)
    Node(Node* orig, Node* p) : key{orig->key}, parent{p} {
      if (orig->left) left.reset(new Node{orig->left.get(), this});
      if (orig->right) right.reset(new Node{orig->right.get(), parent});
    }

    const k_T& getKey() const { return key; }

    Node* getLeft() const { return left.get(); }
    Node* getRight() const { return right.get(); }
    Node* getParent() const { return parent; }

    void setLeft(Node* node) { left.reset(node); }
    void setRight(Node* node) { right.reset(node); }

    void insert(const k_T& k);
    void insert(const std::vector<k_T>& k, unsigned int lb, unsigned int le,
                unsigned int rb, unsigned int re);

    Node* leftmost() {
      if (left != nullptr) return left->leftmost();
      return this;
    }
  };

  std::unique_ptr<Node> root;

 public:
  Tree() : root{nullptr} {}

  // =====================================================================
  // COPY AND MOVE SEMANTICS

  // COPY CONSTRUCTOR (deep copy)
  Tree(const Tree& other) {
    std::cout << " [tree copy ctor]\n";
    if (other.root != nullptr) root.reset(new Node{other.root.get(), nullptr});
  }

  // COPY ASSIGNMENT
  Tree& operator=(const Tree& tree) {
    std::cout << " [tree copy assignment]\n";
    if (this != &tree) root.reset(new Node{tree.root.get(), nullptr});
    return *this;
  }

  // MOVE CONSTRUCTOR
  Tree(Tree&& other) noexcept : root{std::move(other.root)} {
    std::cout << " [tree move ctor]\n";
  }

  // MOVE ASSIGNMENT
  Tree& operator=(Tree&& other) noexcept {
    std::cout << " [tree move assignment]\n";
    root = std::move(other.root);
    return *this;
  }

  // =====================================================================
  // Iterators

  class Iterator;

  Iterator begin() {
    if (root != nullptr)
      return Iterator{root->leftmost()};
    else
      return Iterator{nullptr};
  }

  Iterator end() { return Iterator{nullptr}; }

  class ConstIterator;

  ConstIterator cbegin() const;
  ConstIterator cend() const;

  // =====================================================================

  void insert(const k_T& k) {
    if (root.get() == nullptr)
      root.reset(new Node{k, nullptr});
    else
      root->insert(k);
  }

  void clear() { root.reset(); }

  void balance();

  ConstIterator find(const k_T& k, Node* node) const;
  ConstIterator find(const k_T& k) const;

  void print() const {
    if (root) {
      using ConstIterator = Tree<k_T>::ConstIterator;
      ConstIterator it = this->cbegin();
      ConstIterator it_end = this->cend();
      for (; it != it_end; ++it)
        std::cout << "(" << (*it).first << "," << (*it).second << ") ";
      std::cout << std::endl;
    } else {
      std::cout << "The tree is empty.\n";
    }
  }
};

// =====================================================================
// MEMBER FUNCTIONS

// INSERT
template <typename k_T>
void Tree<k_T>::Node::insert(const k_T& k) {
  if (k < key) {
    if (left == nullptr) {
      left.reset(new Node{k, this});
    } else {
      left->insert(k);
    }
  } else if (k > key) {
    if (right == nullptr) {
      right.reset(new Node{k, parent});
    } else {
      right->insert(k);
    }
  }
}

// BALANCE
template <typename k_T>
void Tree<k_T>::balance() {
  std::cout << "\n[Balancing the tree]\n";

  // Create a vector containing all the nodes in increasing order.
  std::vector<k_T> v_nodes;

  auto it = begin();
  auto it_end = end();
  for (; it != it_end; ++it) v_nodes.emplace_back(*it);

  int lb = 0;
  int le = v_nodes.size() / 2;
  int rb = v_nodes.size() / 2 + 1;
  int re = v_nodes.size() - 1;

  // Set the new root to the middle node.
  auto mid = v_nodes[(lb + re) / 2];
  root.reset(new Node{mid.first, mid.second, nullptr});
  root->insert(v_nodes, lb, le, rb, re);
}

// BALANCE INSERT
template <typename k_T>
void Tree<k_T>::Node::insert(const std::vector<k_T>& v, unsigned int lb,
                             unsigned int le, unsigned int rb,
                             unsigned int re) {
  if (lb < le) {
    left.reset(new Node{v[(lb + le) / 2].first, v[(lb + le) / 2].second, this});
    left->insert(v, lb, (lb + le) / 2, (lb + le) / 2 + 1, le);
  }

  if (rb < re) {
    right.reset(
        new Node{v[(rb + re) / 2].first, v[(rb + re) / 2].second, parent});
    right->insert(v, rb, (rb + re) / 2, (rb + re) / 2 + 1, re);
  }

  // insert the last value on the right
  if (rb == (v.size() - 1)) {
    right.reset(new Node{v[re].first, v[re].second, parent});
    right->insert(v[re].first, v[re].second);
  }
}

// =====================================================================
// Iterator definition

template <typename k_T>
class Tree<k_T>::Iterator
    : public std::iterator<std::forward_iterator_tag, k_T> {
  using Node = Tree<k_T>::Node;
  Node* current;

 public:
  // constructor
  Iterator(Node* node) : current{node} {}

  // dereference operator
  const k_T& operator*() const { return current->getPair(); }

  // ++it
  Iterator& operator++() {
    if (current->getRight()) {
      current = current->getRight()->leftmost();
    } else {
      current = current->getParent();
    }
    return *this;
  }

  // it++
  Iterator operator++(int) {
    Iterator it{current};
    ++(*this);
    return it;
  }

  bool operator==(const Iterator& other) {
    return this->current == other.current;
  }

  bool operator!=(const Iterator& other) { return !(*this == other); }
};

template <typename k_T>
class Tree<k_T>::ConstIterator Tree<k_T>::find(const k_T& k, Node* node) const {
  if (node == nullptr) {
    std::cout << "\nKey " << k << " not found. ";
    return cend();
  } else if (node->getKey() > k) {
    return find(k, node->getLeft());
  } else if (node->getKey() < k) {
    return find(k, node->getRight());
  } else {
    std::cout << "\nKey " << k << " found. ";
    return ConstIterator{node};
  }
}

template <typename k_T>
class Tree<k_T>::ConstIterator Tree<k_T>::find(const k_T& k) const {
  high_resolution_clock::time_point start = high_resolution_clock::now();
  auto it = find(k, root.get());
  high_resolution_clock::time_point stop = high_resolution_clock::now();

  double elapsed = (stop - start).count();
  std::cout << "Lookup time: " << elapsed << std::endl;

  return it;
}

// =====================================================================
// ConstIterator definition
template <typename k_T>
class Tree<k_T>::ConstIterator : public Tree<k_T>::Iterator {
  using Iterator = Tree<k_T>::Iterator;

 public:
  using Iterator::Iterator;
  const k_T& operator*() const { return Iterator::operator*(); }
};

template <typename k_T>
class Tree<k_T>::ConstIterator Tree<k_T>::cbegin() const {
  if (root != nullptr)
    return ConstIterator{root->leftmost()};
  else
    return ConstIterator{nullptr};
}

template <typename k_T>
class Tree<k_T>::ConstIterator Tree<k_T>::cend() const {
  return ConstIterator{nullptr};
}

#endif