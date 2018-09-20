// /*
// Dijkstra algorithm for single source shortest path problem on directed
// non-negative weighted graphs.
// The complexity of this algorithm is O(|E|+|V|log_2|V|) using a min-heap
// priority
// queue.
// */

// #ifndef __dijkstra__
// #define __dijkstra__

// #include "graph.h"
// // #define INFTY MaxSize

// template <typename T>
// void Graph<T>::Dijkstra(T src) {
//   cout << "\n###### Dijkstra ######";

//   // It will hold the shortest distance between src and i
//   int dist[size];

//   // Indicates if vertex i is a predecessor inside the shortest path
//   bool proc[size];

//   for (int i = 0; i < size; ++i) {
//     dist[i] = MaxSize;
//     proc[i] = false;
//   }

//   // src has distance 0 from itself
//   dist[src] = 0;

// #ifdef DEBUG
//   cout << "\nInitialization:";
//   for (int i = 0; i < size; ++i) {
//     cout << "\ndist[" << i << "] = " << dist[i];
//     cout << ", proc[" << i << "] = " << proc[i];
//   }
//   cout << endl;
// #endif

//   // Calculate the shortest path from src to all the other graph nodes
//   int min_dist, u, v, weight;
//   for (int count = 0; count < size; ++count) {
//     // Initialize the minimum distance for all the nodes
//     min_dist = MaxSize;
//     u = 0;

//     // Pick the minimum distance vertex u from the set of unvisited vertices
//     // (basically I build a min heap)
//     for (int i = 0; i < size; ++i) {
//       if (proc[i] == false && dist[i] <= min_dist) {
//         min_dist = dist[i];
//         u = i;
// #ifdef DEBUG
//         cout << "\nu = " << i << " and min_dist = " << min_dist;
// #endif
//       }
//     }

//     // Mark the vertex u as visited in the shortest papth
//     proc[u] = true;
// #ifdef DEBUG
//     cout << "\nproc[" << u << "] = true";
// #endif

//     // Update the dist[v] of each v adjacent to u, but only if it's not
//     // in the shortest path to src and there is a path from src to v with
//     // distance smaller that dist[v]
//     for (auto it = adj_list[u].begin(); it != adj_list[u].end(); ++it) {
//       v = (*it).first;        // node index
//       weight = (*it).second;  // weight of edge u-v

//       if (proc[v] == false && dist[u] != MaxSize && dist[u] + weight <
//       dist[v])
//         dist[v] = dist[u] + weight;

// #ifdef DEBUG
//       cout << "\nupdated dist[" << v << "] = " << dist[v];
// #endif
//     }
//   }

//   // Print the resulting distance array
//   cout << "\n\nShortest path distances from source array are:\n";
//   for (int i = 0; i < size; ++i) {
//     cout << src << " -> " << i << " : " << dist[i] << endl;
//   }
// }

// #endif