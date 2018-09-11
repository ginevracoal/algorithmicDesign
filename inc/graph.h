
// =====================================================

// TO DO
// - descrivere l'header
// - implementare std::vector e stack

#ifndef __graph__
#define __graph__

#include <iostream>

// #ifdef STD
// #include <list>
#include <stack>
#include <vector>
#include "../inc/list.h"
// #endif

#define NIL -1
using namespace std;

template <typename T>
class Graph {
 private:
  class Node;

  // Number of nodes
  int size;

  // Number of strongly connected components
  int n_SCCs;

  // SCCs
  vector<vector<T>> *SCCs;

  // array of adjacency lists (one list for each node)
  list<T> *adj;

  // // vector of node, each one containing its list of adjacent nodes
  // vector<Node> nodes;

  // Tarjan recursive function
  void Tarjan_SCC_rec(int v, T *disc, T *low, stack<T> *Q, bool *onStack);
  // void Tarjan_SCC_rec_new();  // now using Node class

  // Fischer Meyer utility functions
  Graph collapse();
  bool *UT_adj_matrix();
  void decollapse(T &M);

 public:
  // Constructor
  Graph(int size) {
    // parameter size shadows the class member with the same name, so the use of
    // this-> is required
    this->size = size;
    adj = new list<T>[size];  // allocates a new adjacency list
    SCCs = new vector<vector<T>>[size];
  }

  // Adds the edge from node v to node w to the graph.
  void add_edge(T v, T w) { adj[v].push_back(w); }

  void print_edges() {
    cout << "\nGraph edges are:";
    for (int v = 0; v < size; ++v) {
      for (typename list<T>::iterator i = adj[v].begin(); i != adj[v].end();
           ++i) {
        cout << endl << v << " -> " << *i;
      }
    }
    cout << endl;
  }

  void print_SCCs() {
    n_SCCs = SCCs->size();
    cout << "\n\nThere are " << n_SCCs
         << " strongly connected components:" << endl;
    for (auto scc = SCCs->begin(); scc != SCCs->end(); ++scc) {
      // for (unsigned int j = 0; j < SCCs[i]->size(); j++) {
      // cout << SCCs[i][j] << " ";
      for (auto node = scc->begin(); node != scc->end(); ++node) {
        cout << *node << " ";
      }
      cout << endl;
    }
  }

  // Finds the strongly connected components using Tarjan algorithm
  void Tarjan_SCC();

  // Computes the transitive closure using Fischer Meyer algorithm
  void Fischer_Meyer();
};

// NEW NODE CLASS

enum class color { white, grey, black };

template <typename T>
class Graph<T>::Node {
  // Tarjan uses
  T val;    // node value
  int SCC;  // SCC index
  color col;
  int disc;
  int lowlink;
  vector<Node> adj;  // or should i use Node*?

 public:
  Node(T v) : val{v}, col{color::white}, disc{NIL}, lowlink{NIL} {}

  void print() {
    cout << "\nNode: (val=" << val << ", SCC=" << SCC << ", col=" << col
         << ", disc=" << disc << ", lowlink=" << lowlink << ")";
  }

  // getters
  color get_col() { return col; }
  int get_disc() { return disc; }
  int get_lowlink() { return lowlink; }

  // setters
  void set_col(color c) { col = c; }
  void set_disc(int d) { disc = d; }
  void set_lowlink(int l) { lowlink = l; }
};

#endif