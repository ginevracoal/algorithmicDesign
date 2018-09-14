/*
Dijkstra algorithm for single source shortest path problem.
*/

#ifndef __dijkstra__
#define __dijkstra__

#include "graph.h"
#define INFTY 100

template <typename T>
void Graph<T>::Dijkstra(T src) {
  cout << "\n###### Dijkstra ######\n";

  // It will hold the shortest distance between src and i
  int dist[size];

  // Indicates if vertex i is a predecessor inside the shortest path
  bool pred[size];

  for (int i = 0; i < size; ++i) {
    dist[i] = INFTY;
    pred[i] = false;
  }

  // src has distance 0 from itself
  dist[src] = 0;

#ifdef DEBUG
  cout << "\nInitialization:";
  for (int i = 0; i < size; ++i) {
    cout << "\ndist[" << i << "] = " << dist[i];
    cout << ", pred[" << i << "] = " << pred[i];
  }
  cout << endl;
#endif

  // Calculate the shortest path from src to all the other graph nodes
  for (int count = 0; count < size; ++count) {
    // Initialize the minimum distance for all the nodes
    int min_dist = INFTY, u = 0;

    // Pick the minimum distance vertex u from the set of unvisited vertices
    // (basically I build a min heap)
    for (int i = 0; i < size; ++i)
      if (pred[i] == false && dist[i] <= min_dist) {
        min_dist = dist[i];
        u = i;
#ifdef DEBUG
        cout << "\nu = " << i << " and min_dist = " << dist[i];
#endif
      }

    // Mark the vertex u as visited in the shortest papth
    pred[u] = true;
#ifdef DEBUG
    cout << "\npred[" << u << "] = true";
#endif

    // Update the dist[v] of each v adjacent to u, but only if it's not
    // in the shortest path to src and there is a path from src to v with
    // distance smaller that dist[v]
    for (auto it = adj_list[u].begin(); it != adj_list[u].end(); ++it) {
      if (pred[(*it).first] == false && dist[u] != INFTY &&
          dist[u] + (*it).second < dist[(*it).first])
        dist[(*it).first] = dist[u] + (*it).second;

#ifdef DEBUG
      cout << "\nupdated dist[" << (*it).first
           << "] = " << dist[u] + (*it).second;
#endif
    }
  }

  // Print the resulting distance array
  cout << "\nShortest paths distances from source array are:\n";
  for (int i = 0; i < size; ++i) {
    cout << src << " -> " << i << " : " << dist[i] << endl;
  }
}

#endif