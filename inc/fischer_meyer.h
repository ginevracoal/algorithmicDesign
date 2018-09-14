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

// Compute the SCC collapsed graph, obtaining an acyclic graph.
template <typename T>
Graph<T> Graph<T>::collapse() {
  cout << "\n###### collapse ######\n";

  // I also have to consider an additional space for the NULL terminator!
  // otherwise it gives a memory error.
  Graph<T> collapsed_graph(n_SCCs + 1);

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
        // If they do not belong to the same SCC and tadd the edge to the new
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

          // The collapsed graph now contains at least one node from the scc.
          SCC_node_inserted[SCC_idx[*from]] = true;
        }
      }
    }
  }
  return collapsed_graph;
}

// Convert adjacency list into upper triangular adjacency matrix.
template <typename T>
bool* Graph<T>::UT_adj_matrix() {
  cout << "\n###### UT_adj_matrix ######\n";
  bool* adj_matrix[size * size];

  // Initialize all nodes as only being adjacent to themselves.
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      if (i == j)
        *adj_matrix[i * size + j] = true;
      else
        *adj_matrix[i * size + j] = false;
    }
  }

  // now i should iterate according to topological sort

  //  DA FINIRE

  return *adj_matrix;
}

// Compute the transitive closure of the adjacency matrix.
template <typename T>
void Graph<T>::decollapse(T& M) {
  cout << "\n###### decollapse ######\n";
}

template <typename T>
void Graph<T>::Fischer_Meyer() {
  // Find the strongly connected components using Tarjan algorithm.
  this->Tarjan_SCC();  // Theta(|V|+|E|)

  // Calculate the collapsed graph from the SCCs
  // Graph<T> collapsed_graph(this->n_SCCs);
  Graph<T> collapsed_graph = this->collapse();  // O(|V|^2) as topological sort
  collapsed_graph.print_edges();
  collapsed_graph.print_adj();

  // Create an upper triangular adjacency matrix
  bool* M = collapsed_graph.UT_adj_matrix();  // time complexity????

  //   // Get the transitive closure of the matrix
  //   return this->decollapse(&M);  // O(|V|^2)
}

#endif