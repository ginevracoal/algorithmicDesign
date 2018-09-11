#ifndef __fischer_meyer__
#define __fischer_meyer__

#include "graph.h"
#include "tarjan.h"

// Compute the SCC collapsed graph, obtaining an acyclic graph.
template <typename T>
Graph<T> Graph<T>::collapse() {
  cout << "\n###### collapse ######\n";

  Graph<T> collapsed_graph(this->n_SCCs);

  for (auto scc = this->SCCs->begin(); scc != SCCs->end(); ++scc) {
    // each SCC represents a node in the new graph.

    for (auto from = scc->begin(); from != scc->end(); ++from) {
      for (typename list<T>::iterator to = adj[*from].begin();
           to != adj[*from].end(); ++to) {
        // If they do not belong to the same SCC add the edge to the new
        // adjacency list.
        if (SCC_idx[*from] != SCC_idx[*to])
          collapsed_graph.add_edge(*from, *to);
      }
    }
  }

  return collapsed_graph;
}

// Convert adjacency list into upper triangular adjacency matrix.
template <typename T>
bool* Graph<T>::UT_adj_matrix() {
  cout << "\n###### UT_adj_matrix ######\n";

  return false;
}

// Compute the transitive closure from the adjacency matrix.
template <typename T>
void Graph<T>::decollapse(T& M) {
  cout << "\n###### decollapse ######\n";
}

template <typename T>
void Graph<T>::Fischer_Meyer() {
  // Find the strongly connected components using Tarjan algorithm
  this->Tarjan_SCC();  // Theta(|V|+|E|)

  // Calculate the collapsed graph from the SCCs
  // Graph<T> collapsed_graph(this->n_SCCs);
  Graph<T> collapsed_graph = collapse();  // O(|V|^2) as topological sort
  collapsed_graph.print_edges();

  //   // Create an upper triangular adjacency matrix
  //   bool* M = collapsed_graph.UT_adj_matrix();  //????

  //   // Get the transitive closure of the matrix
  //   return this->decollapse(&M);  // O(|V|^2)
}

#endif