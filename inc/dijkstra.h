/*
Dijkstra algorithm for single source shortest path problem.
*/

#ifndef __dijkstra__
#define __dijkstra__

// #include "binary_heap.h"
#include "graph.h"
// #include "heapsort.h"
#define INFTY -1

template <typename T>
void Graph<T>::Dijkstra(T src) {
  cout << "\n###### Dijkstra ######\n";

  // It will hold the shortest distance between src and i
  int dist[size];

  // Indicates if vertex i is inside the shortest path
  bool in_spath[size];

  for (int i = 0; i < size; ++i) {
    dist[i] = INFTY;
    in_spath[i] = false;
  }

  // src has distance 0 from itself
  dist[src] = 0;

#ifdef DEBUG
  cout << "\nInitialization:";
  for (int i = 0; i < size; ++i) {
    cout << "\ndist[" << i << "] = " << dist[i];
    cout << ", in_spath[" << i << "] = " << in_spath[i];
  }
  cout << endl;
#endif

  // Calculate the shortest path from src to all the other graph nodes
  for (int j = 0; j < size; ++j) {
    // Initialize the minimum distance for all the nodes
    int min_dist = INFTY, u = 0;

    // Pick the minimum distance vertex u from the set of vertices not yet
    // visited(which is src itself in the first iteration)
    for (int i = 0; i < size; ++i) {
      if (in_spath[i] == false && dist[i] <= min_dist) {
        min_dist = dist[i];
        u = i;
#ifdef DEBUG
        cout << "\nupdated u = " << i;
#endif
      }
    }

    // Mark the vertex u as traversed in the shortest papth
    in_spath[u] = true;

    // Update the dist[v] of each v adjacent to u, but only if it's not
    // in the shortest path to src and there is a path from src to v with
    // distance smaller that dist[v]
    for (auto it = adj_list[u].begin(); it != adj_list[u].end(); ++it) {
      if (in_spath[(*it).first] == false && (*it).second != 0 &&
          dist[u] != INFTY && dist[u] + (*it).second < dist[(*it).first])
        dist[(*it).first] = dist[u] + (*it).second;

#ifdef DEBUG
      cout << "\nupdated dist[" << (*it).first
           << "] = " << dist[u] + (*it).second;
#endif
    }
  }

  // Print the resulting distance array
  cout << "\n\nDistances from source array are:\n";
  for (int i = 0; i < size; ++i) {
    cout << src << " -> " << i << " : " << dist[i] << endl;
  }
}

#endif