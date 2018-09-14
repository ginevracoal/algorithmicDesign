#ifndef __graph__
#define __graph__

#include <iostream>
#include <stack>
#include <vector>
#include "../inc/list.h"

#define MaxSize 50
#define NIL -1
using namespace std;

template <typename T>
class Graph {
 private:
  // ###### BASIC GRAPH STRUCTURE ######

  // class Node;

  // Nodes and edges
  int size;      // number of nodes
  list<T> *adj;  // pointer to array of adjacency lists (one list for each node)

  // Strongly connected components
  int n_SCCs;                 // number of SCCs
  vector<vector<T>> *SCCs;    // vector containing SCCs
  int SCC_idx[MaxSize];       // SCCs indicator
  Graph<T> *collapsed_graph;  // Collapsed graph

  // Dijkstra variables
  // T *parent;             // array containing parent indexes
  // vector<double> *dist;  // distances from current node to all other nodes

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
    SCCs = new vector<vector<T>>[size];
    // parent = new T[size];
    // dist = new vector<double>[size];
  }

  ~Graph() {
    delete[] adj;
    delete[] SCCs;
    // delete[] parent;
    // delete[] dist;
  }

  // OBSERVERS

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

  // double get_dist(T v, T w) { return dist[v][w]; }
  // T get_parent(T v) { return parent[v]; }

  // MODIFIERS

  // Adds the directed edge from node v to node w.
  void add_edge(T v, T w) { adj[v].push_back(w); }

  // void set_dist(T v, T w, double d) { *dist[v][w] = d; }
  // void set_parent(T n, T p) { *parent[n] = p; }

  // ###### MAIN ALGORITHMS ######

  // Finds the strongly connected components using Tarjan algorithm
  void Tarjan_SCC();

  // Computes the transitive closure using Fischer Meyer algorithm
  void Fischer_Meyer();

  // Solves single source shortest path problem using Dijkstra algorithm
  // void Dijkstra(T s);  // takes a start node index
};

// template <typename T>
// class Graph<T>::Node {
//   T val;         // node value
//   list<T> *adj;  // pointer to array of adjacency lists (one list for each
//   node)

//  public:
// };

#endif