/**
Fischer Meyer algorithm solves the transitive closure problem with complexity
O(|V|^log_2(7)) instead of the O(|V|^2|E|) given by the classical search.
The steps are the following ones:
- compute the SCC collapsed graph in order to get an acyclic graph
- sort the nodes of this collapsed graph in such a way that the adjacency
matrix
is upper triangular.
- split the matrix in 4 blocks and compute the transitive closure on them
- reconstruct the transitive closure of G knowing that all the elements in a
SCC
have the same reachability set
*/

#ifndef __fischer_meyer__
#define __fischer_meyer__

#include "graph.h"
#include "tarjan.h"

template <typename T>
void print_matrix(T* M, int size) {
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      std::cout << M[i * size + j] << "\t";
    }
    std::cout << std::endl;
  }
}

// ============ Collapse ============

// Compute the SCC collapsed graph, obtaining an acyclic graph.
template <typename T>
Graph<T> Graph<T>::collapse() {
#ifdef DEBUG
  cout << "\n###### collapse ######\n";
#endif
  // I also have to consider an additional space for the NULL terminator!
  // otherwise it gives a memory error.
  Graph<T> collapsed_graph(size);  // size should be n_SCCS, but graph is
                                   // such that if I want number k in my
                                   // graph I have to allocate k spaces.

  // For each SCC this tells me if it has already been inserted as a node in the
  // collapsed graph.
  bool SCC_node_inserted[n_SCCs]{false};

  // Each SCC represents a node in the collapsed graph.
  for (auto scc = SCCs->begin(); scc != SCCs->end(); ++scc) {
    // Scanning all the nodes of the SCC.
    for (auto from = scc->begin(); from != scc->end(); ++from) {
      // scanning the adj list of the current node
      for (typename list<T>::iterator to = adj[*from].begin();
           to != adj[*from].end(); ++to) {
        // If they do not belong to the same SCC and add the edge to the new
        // adjacency list.
        if (SCC_idx[*from] != SCC_idx[*to] &&
            SCC_node_inserted[SCC_idx[*from]] == false) {
#ifdef DEBUG
          cout << "\nNode " << *from << " belongs to component "
               << SCC_idx[*from] << ", while node " << *to
               << " belongs to component " << SCC_idx[*to];
          cout << "\nNo node of SCC " << SCC_idx[*from]
               << " has been inserted yet. Adding adge (" << *from << "," << *to
               << ") to the collapsed graph.\n";
#endif
          collapsed_graph.add_edge(*from, *to);

          // The collapsed graph contains one representative node from the
          scc.SCC_node_inserted[SCC_idx[*from]] = true;
        }
      }
    }
  }

  return collapsed_graph;
}

// ============ Adjacency matrix ============

// Convert adjacency list into upper triangular adjacency matrix.
template <typename T>
bool* Graph<T>::UT_adj_matrix() {
#ifdef DEBUG
  cout << "\n###### UT_adj_matrix ######\n";
#endif

  bool* adj_matrix = new bool[n_SCCs * n_SCCs];

  // Apply topological sort to the SCC in order to get a UT matrix
  list<T> sorted_nodes = topological_sort();

  // #ifdef DEBUG
  //   cout << "\nSorted SCCs:\n";
  //   for (auto it = sorted_nodes.begin(); it != sorted_nodes.end(); ++it) {
  //     for (auto node = adj[*it].begin(); node != adj[*it].end(); ++node) {
  //       cout << *node << " ";
  //     }
  //     // cout << *it << " ";
  //     cout << endl;
  //   }
  // #endif

  // Initialize all nodes as only being adjacent to themselves.
  for (int i = 0; i < n_SCCs; ++i) {
    for (int j = 0; j < n_SCCs; ++j) {
      if (i == j)
        adj_matrix[i * n_SCCs + j] = true;
      else
        adj_matrix[i * n_SCCs + j] = false;
    }
  }

  // Fill the adjacency matrix
  for (int i = 0; i < n_SCCs; ++i)
    for (auto it = adj[i].begin(); it != adj[i].end(); ++it) {
      adj_matrix[i * n_SCCs + *it] = true;
    }

#ifdef DEBUG
  // print the adjacency matrix
  for (int i = 0; i < n_SCCs; ++i) {
    for (int j = 0; j < n_SCCs; ++j) cout << adj_matrix[i * size + j] << " ";
    cout << endl;
  }
#endif

  return adj_matrix;
  // delete[] adj_matrix;
}

// Returns the topological sort of the SCCs
// I can apply topological sort only on the collapsed graph since it is DAG.
template <typename T>
list<T> Graph<T>::topological_sort() {
  bool* visited = new bool[size];
  list<T> sorted_nodes;

  for (int i = 0; i < size; ++i)
    if (nodes[i] == 1) visited[i] = false;

  for (int i = 0; i < size; ++i)
    if (nodes[i] == 1 && visited[i] == false)
      topological_sort_rec(i, visited, sorted_nodes);

  return sorted_nodes;
}

template <typename T>
void Graph<T>::topological_sort_rec(int i, bool visited[],
                                    list<T> sorted_nodes) {
  visited[i] = true;

  // recur on the i-th adjacency list
  for (auto it = adj[i].begin(); it != adj[i].end(); ++it)
    if (nodes[i] == 1 && !visited[*it])
      topological_sort_rec(*it, visited, sorted_nodes);

  sorted_nodes.push_back(i);
  cout << i << " ";
}

// ============ Decollapse ============

// Compute the transitive closure of the adjacency matrix.
template <typename T>
void Graph<T>::decollapse(T& M) {
#ifdef DEBUG
  cout << "\n###### decollapse ######\n";
#endif
}

// ============ Main algorithm ============

template <typename T>
void Graph<T>::Fischer_Meyer() {
  // Find the strongly connected components using Tarjan algorithm.
  this->Tarjan_SCC();  // Theta(|V|+|E|)

  // Calculate the collapsed graph from the SCCs
  Graph<T> collapsed_graph = this->collapse();  // O(|V|^2) as topological sort

#ifdef DEBUG
  cout << "\nCollapsed graph.\n";
  collapsed_graph.print_nodes();
  collapsed_graph.print_edges();
  collapsed_graph.print_adj();
#endif

  // Create an upper triangular adjacency matrix
  bool* M = collapsed_graph.UT_adj_matrix();  // complexity????

  //   // Compute the transitive closure of the matrix
  //   return this->decollapse(&M);  // O(|V|^2)

  // delete[] M;
}

#endif