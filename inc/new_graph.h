#ifndef __GRAPH__
#define __GRAPH__

#include <iostream>
#include <list>
#include <stack>
#include <vector>
// #include "list.h"

#define MaxSize 100
#define NIL -1
using namespace std;

template <typename T>
class Graph {
 private:
  // ###### BASIC GRAPH STRUCTURE ######

  // Nodes and edges
  int size;  // number of nodes
  // bool nodes[MaxSize];  // node values
  list<T> *adj;  // pointer to array of adjacency lists (one list for each node)
  list<pair<T, int>> *adj_list;  // for int weighted graphs

  class Node;
  vector<Graph<T>::Node> nodes;

  // Strongly connected components
  int n_SCCs;                 // number of SCCs
  vector<vector<T>> *SCCs;    // vector containing SCCs
  int SCC_idx[MaxSize];       // SCCs indicator
  Graph<T> *collapsed_graph;  // Collapsed graph

  // ###### UTILITY FUNCTIONS ######

  // Tarjan recursive function
  void Tarjan_SCC_rec(int, T *, T *, stack<T> *, bool *);

  // Fischer Meyer functions
  Graph<T> collapse();
  bool *UT_adj_matrix();
  void decollapse(T &);
  vector<vector<T>> *topological_sort();

 public:
  // Graph constructor and destructor
  Graph(int size) {
    this->size = size;  // parameter size shadows the class member with the same
                        // name, so the use of this-> is required

    adj = new list<T>[size + 1];  // allocates a new adjacency list
    adj_list = new list<pair<T, int>>[size + 1];

    SCCs = new vector<vector<T>>[size + 1];
  }

  ~Graph() {
    // deallocate the arrays
    delete[] adj;
    delete[] adj_list;
    delete[] SCCs;
    delete[] collapsed_graph;
  }

  // OBSERVERS

  void print_nodes() {
    // cout << "\nGraph nodes are: ";
    // for (int i = 0; i < size; ++i)
    //   if (nodes[i] == 1) cout << i << " ";
    // cout << endl;
  }

  void print_edges() {
    cout << "\nGraph edges are:";
    for (auto node = nodes.begin(); node != nodes.end(); ++node)
      for (auto it = node->adj.begin(); it != node->adj.end(); ++it)
        cout << endl << node << " -> " << *it;
    cout << endl;
  }

  // void print_weighted_edges() {
  //   cout << "\nWeighted graph edges are:";
  //   for (auto node = nodes.begin(); node != nodes.end(); ++node)
  //     for (auto it = adj[v].begin(); it != adj[v].end(); ++it)
  //       cout << endl
  //            << node << " ----[" << (*it).second << "]---> " << (*it).first;
  //   cout << endl;
  // }

  // void print_adj() {
  //   cout << "\nAdjacency lists:";
  //   for (auto node = nodes.begin(); node != nodes.end(); ++node) {
  //     cout << "\nadj[" << v << "] = ";
  //     for (auto it = adj[v].begin(); it != adj[v].end(); ++it)
  //       cout << *it << " ";
  //   }
  //   cout << endl;
  // }

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

  // Adds the directed edge from -> to
  void add_edge(T from, T to) {
    Node curr = nodes.at(from);
    if (!curr) nodes.push_back(from);
    curr->adj.push_back(to);
  }

  void add_edge(T from, T to, int weight) {
    adj_list[from].push_back(make_pair(to, weight));
  }

  // ###### MAIN ALGORITHMS ######

  // Search algorithms
  void BFS(int);
  void DFS(int);
  void DFS_recur(int, bool[]);

  // Finds the strongly connected components using Tarjan algorithm
  void Tarjan_SCC();

  // Computes the transitive closure using Fischer Meyer algorithm
  void Fischer_Meyer();

  // Solves single source shortest path problem using Dijkstra algorithm
  void Dijkstra(T src);  // takes a start node index

  // Solves single source shortest path problem using A* algorithm
  void Astar(T src);  // takes a start node index
};

template <typename T>
class Graph<T>::Node {
  // node value
  T value;

  // index of the SCC
  int scc;

  // weighted adjacency list
  list<pair<T, int>> adj;

 public:
  Node(int v) {
    value = v;
    scc = NIL;
    adj = new list<pair<T, int>>[size + 1];  // allocates a new adjacency list
  }
};

#endif
