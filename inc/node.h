// #ifndef __NODE__
// #define __NODE__

// #include <iostream>
// #include <memory>  // for unique pointers
// #include <vector>
// #include "graph.h"

// template <typename T>
// class Graph<T>::Node {
//  private:
//   T value;
//   int weight;                // weight to the parent node
//   std::list<Node> adj_list;  // adjacency list for a node

//  public:
//   // NODE CONSTRUCTOR
//   // each time I enter a new node passing a ptr to the node to which I want
//   to
//   // append it and then update the two adjacency lists
//   Node(const T& v, size_t w = 0, Node* p)
//       : value{k}, weight{w}, left{nullptr}, right{nullptr}, parent{p} {}

//   // // COPY CONSTRUCTOR (deep copy)
//   // Node(Node* orig, Node* p) : Value{orig->Value}, parent{p} {
//   //   if (orig->left) left.reset(new Node{orig->left.get(), this});
//   //   if (orig->right) right.reset(new Node{orig->right.get(), parent});
//   // }

//   const T& getValue() const { return value; }
//   const T getWeight() const { return weight; }
//   Node* getParent() const { return parent; }

//   void setRight(Node* node) { right.reset(node); }

//   void insert(const T& k);
// };

// template <typename T>
// void Graph<T>::Node::insert(const T& k) {
//   if (k < Value) {
//     if (left == nullptr) {
//       left.reset(new Node{k, this});
//     } else {
//       left->insert(k);
//     }
//   } else if (k > Value) {
//     if (right == nullptr) {
//       right.reset(new Node{k, parent});
//     } else {
//       right->insert(k);
//     }
//   }
// }

// #endif