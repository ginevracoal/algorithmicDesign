#ifndef __GRAPH__
#define __GRAPH__

#include <iostream>
#include <stack>
#include <vector>
// #include "binary_heap.h"
#include "list.h"

#define MaxSize 50
#define NIL -1
using namespace std;

template <typename T>
class Graph {
 private:
  // ###### BASIC GRAPH STRUCTURE ######

  // Nodes and edges
  int size;      // number of nodes
  list<T> *adj;  // pointer to array of adjacency lists (one list for each node)
  list<pair<T, int>> *adj_list;  // for int weighted graphs

  // Strongly connected components
  int n_SCCs;                 // number of SCCs
  vector<vector<T>> *SCCs;    // vector containing SCCs
  int SCC_idx[MaxSize];       // SCCs indicator
  Graph<T> *collapsed_graph;  // Collapsed graph

  // ###### UTILITY FUNCTIONS ######

  // Tarjan recursive function
  void Tarjan_SCC_rec(int, T *, T *, stack<T> *, bool *);

  // Fischer Meyer utility functions
  Graph<T> collapse();
  bool *UT_adj_matrix();
  void decollapse(T &);

 public:
  // Graph constructor and destructor
  Graph(int size) {
    this->size = size;  // parameter size shadows the class member with the same
                        // name, so the use of this-> is required
    adj = new list<T>[size];  // allocates a new adjacency list
    adj_list = new list<pair<T, int>>[size];
    SCCs = new vector<vector<T>>[size];
  }

  ~Graph() {
    delete[] adj;
    delete[] adj_list;
    delete[] SCCs;
  }

  // OBSERVERS

  void print_edges() {
    cout << "\nGraph edges are:";
    for (int v = 0; v < size; ++v) {
      for (typename list<T>::iterator it = adj[v].begin(); it != adj[v].end();
           ++it) {
        cout << endl << v << " -> " << *it;
      }
    }
    cout << endl;
  }

  void print_weighted_edges() {
    cout << "\nWeighted graph edges are:";
    for (int v = 0; v < size; ++v) {
      for (auto it = adj_list[v].begin(); it != adj_list[v].end(); ++it) {
        cout << endl
             << v << " ----[" << (*it).second << "]---> " << (*it).first;
      }
    }
    cout << endl;
  }

  void print_adj() {
    cout << "\nAdjacency lists:";
    for (int v = 0; v < size; ++v) {
      cout << "\nadj[" << v << "] = ";
      for (typename list<T>::iterator i = adj[v].begin(); i != adj[v].end();
           ++i)
        cout << *i << " ";
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

  // MODIFIERS

  // Adds the directed edge from node v to node w.
  void add_edge(T v, T w) { adj[v].push_back(w); }

  void add_edge(T from, T to, int weight) {
    adj_list[from].push_back(make_pair(to, weight));
  }

  // ###### MAIN ALGORITHMS ######

  // Finds the strongly connected components using Tarjan algorithm
  void Tarjan_SCC();

  // Computes the transitive closure using Fischer Meyer algorithm
  void Fischer_Meyer();

  // Solves single source shortest path problem using Dijkstra algorithm
  void Dijkstra(T src);  // takes a start node index
};

#endif