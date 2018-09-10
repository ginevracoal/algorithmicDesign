#ifndef __graph__
#define __graph__

#include <iostream>

#ifdef STD
#include <list>
#else
#include "../inc/list.h"
#endif

// #define NIL -1

using namespace std;

template <typename T>
class Graph {
 private:
  // Number of nodes
  int size;

  // Number of strongly connected components
  int SCCs;

  // Adjacency list of nodes
  list<T> *adj;

  // Recursive function used by Tarjan_SCC
  void Tarjan_SCC_rec(int v, T *disc, T *low, stack<T> *Q, bool *onStack);

 public:
  // Constructor
  Graph(int size) {
    /** parameter size shadows the class member with the same name, so the
     * use of this-> is required */
    this->size = size;
    adj = new list<T>[size];  // allocates a new adjacency list
  }

  // Adds the edge from node v to node w to the graph.
  void add_edge(T v, T w) { adj[v].push_back(w); }

  void print_edges() {
    cout << "\nGraph edges are:";
    for (int v = 0; v < size; ++v) {
      for (typename list<T>::iterator i = adj[v].begin(); i != adj[v].end();
           ++i) {
        cout << endl << v << " " << *i;
      }
    }
    cout << endl;
  }

  // Finds the strongly connected components using Tarjan algorithm
  void Tarjan_SCC();
};

#endif