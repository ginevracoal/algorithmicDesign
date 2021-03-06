/*
A* algorithm for single source shortest path problem on directed
non-negative weighted graphs.
It is based on the use of an heuristic distance, giving an initial guess of the
effective distance between nodes. The heuristic is admissible if it never
overestimates the actual real distance.
The worst case performance with a min-heap priority queue is O(|E|).
Dijkstra is a particular case of A* with null heuristic distance.
*/

#ifndef __A_star__
#define __A_star__

#include "graph.h"

template <typename T>
void Graph<T>::Dijkstra(T src) {
  cout << "\n###### Dijkstra ######";
  Astar(src, 0);
}

template <typename T>
void Graph<T>::Astar(T src, int my_heuristic) {
  if (my_heuristic == 1) cout << "\n######  A* ######";

  // It will hold the shortest distance between src and i
  int dist[size];

  // The heuristic distance is a guess of the distance of the final node from
  // the source
  int heur[size];

  // Indicates if vertex i is a predecessor inside the shortest path
  bool proc[size];

  for (int i = 0; i < size; ++i) {
    dist[i] = MaxSize;
    proc[i] = false;
    heur[i] = 0;
  }

  // src has distance 0 from itself
  dist[src] = 0;
  int min_dist;

  if (my_heuristic == 1) {
#ifdef DEBUG
    cout << "\n\nUsing Custom heuristic!\n";
#endif
    // MY HEURISTIC
    // Initialize the heuristic distance of each node as the minimum weight of
    // edges directed to i. I have to explore all the adj lists of the nodes for
    // that.
    for (int to = 0; to < size; ++to) {
      min_dist = MaxSize;
      for (int from = 0; from < size; ++from)
        for (auto it = adj_list[from].begin(); it != adj_list[from].end(); ++it)
          if ((*it).first == to && (*it).second < min_dist) {
            min_dist = (*it).second;
            heur[to] = min_dist;
          }
    }
  }

#ifdef DEBUG
  cout << "\nInitialization:";
  for (int i = 0; i < size; ++i) {
    cout << "\ndist[" << i << "] = " << dist[i];
    cout << ", proc[" << i << "] = " << proc[i];
    cout << ", heur[" << i << "] = " << heur[i];
  }
  cout << endl;
#endif

  // Calculate the shortest path from src to all the other graph nodes
  int u, v, weight;
  for (int count = 0; count < size; ++count) {
    // Initialize the minimum distance for all the nodes
    min_dist = MaxSize;
    u = 0;

    // Pick the minimum distance vertex u from the set of unvisited vertices
    // (basically I build a min heap)
    for (int i = 0; i < size; ++i) {
      if (proc[i] == false && dist[i] + heur[i] <= min_dist) {
        min_dist = dist[i] + heur[i];
        u = i;
#ifdef DEBUG
        cout << "\nu = " << i << " and min_dist = " << min_dist;
#endif
      }
    }

    // Mark the vertex u as visited in the shortest papth
    proc[u] = true;
#ifdef DEBUG
    cout << "\nproc[" << u << "] = true";
#endif

    // Update the dist[v] of each v adjacent to u, but only if it's not
    // in the shortest path to src and there is a path from src to v with
    // distance smaller that dist[v]
    for (auto it = adj_list[u].begin(); it != adj_list[u].end(); ++it) {
      v = (*it).first;        // node index
      weight = (*it).second;  // weight of edge u-v

      if (proc[v] == false && dist[u] + heur[u] != MaxSize &&
          dist[u] + weight + heur[u] < dist[v])
        dist[v] = dist[u] + weight;

#ifdef DEBUG
      cout << "\nupdated dist[" << v << "] = " << dist[v];
#endif
    }
  }

  // Print the resulting distance array
  cout << "\n\nShortest path distances from source array are:\n";
  for (int i = 0; i < size; ++i) {
    cout << src << " -> " << i << " : " << dist[i] << endl;
  }
}

#endif