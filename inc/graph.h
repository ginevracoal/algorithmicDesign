#ifndef __graph__
#define __graph__

#include <iostream>

// #ifdef STD
// #include <list>
#include <stack>
#include <vector>
#include "../inc/list.h"
// #endif

#define MaxSize 50
#define NIL -1
using namespace std;

template <typename T>
class Graph {
 private:
  // ###### BASIC GRAPH STRUCTURE ######

  // class Node; // too much complicated, not necessary.

  // Number of nodes
  int size;
  // array of adjacency lists (one list for each node)
  list<T> *adj;

  // Number of strongly connected components
  int n_SCCs;
  // SCCs
  vector<vector<T>> *SCCs;
  // SCCs indicator
  int SCC_idx[MaxSize];

  // Collapsed graph
  Graph<T> *collapsed_graph;

  // ###### UTILITY FUNCTIONS ######

  // Tarjan recursive function
  void Tarjan_SCC_rec(int v, T *disc, T *low, stack<T> *Q, bool *onStack);

  // Fischer Meyer utility functions
  Graph<T> collapse();
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

  ~Graph() {
    delete[] adj;
    delete[] SCCs;
  }

  // Adds the directed edge from node v to node w.
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
      for (auto node = scc->begin(); node != scc->end(); ++node) {
        cout << *node << " ";
      }
      cout << endl;
    }
  }

  // ###### MAIN ALGORITHMS ######

  // Finds the strongly connected components using Tarjan algorithm
  void Tarjan_SCC();

  // Computes the transitive closure using Fischer Meyer algorithm
  void Fischer_Meyer();
};

// =====================================================

// // NODE CLASS

// enum class color { white, grey, black };

// template <typename T>
// class Graph<T>::Node {
//   // Tarjan uses
//   T val;    // node value
//   int SCC;  // SCC index
//   color col;
//   int disc;
//   int lowlink;
//   vector<Node> adj;  // or should i use Node*?

//  public:
//   Node(T v) : val{v}, col{color::white}, disc{NIL}, lowlink{NIL} {}

//   void print() {
//     cout << "\nNode: (val=" << val << ", SCC=" << SCC << ", col=" << col
//          << ", disc=" << disc << ", lowlink=" << lowlink << ")";
//   }

//   // getters
//   color get_col() { return col; }
//   int get_disc() { return disc; }
//   int get_lowlink() { return lowlink; }

//   // setters
//   void set_col(color c) { col = c; }
//   void set_disc(int d) { disc = d; }
//   void set_lowlink(int l) { lowlink = l; }
// };

#endif