#ifndef __floyd_warshall__
#define __floyd_warshall__

#include <iostream>
#include "graph.h"

#define INF 9999

template <typename T>
void print_matrix(T* A, const int size) {
  int i, j;
  cout << endl;
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      if (A[i * size + j] == INF)
        cout << "INF"
             << "\t";
      else
        cout << A[i * size + j] << "\t";
    }
    cout << endl;
  }
}

template <typename T>
void Graph<T>::Floyd_Warshall() {
  cout << "\n###### Floyd_Warshall ######\n";

  int* dist{new int[size * size]};  // distances matrix
  int i, j;

  // Initialization
  for (i = 0; i < size; i++)
    for (j = 0; j < size; j++) {
      if (i == j)
        dist[i * size + j] = 0;
      else
        dist[i * size + j] = INF;
    }

  // Adj matrix values
  for (i = 0; i < size; ++i)
    for (auto it = adj_list[i].begin(); it != adj_list[i].end(); ++it)
      dist[i * size + (*it).first] = (*it).second;

#ifdef DEBUG
  cout << "\nInitialization:";
  print_matrix(dist, size);
#endif

  // Actual algorithm
  for (int k = 0; k < size; ++k)
    for (int from = 0; from < size; ++from)
      for (int to = 0; to < size; ++to)
        if (dist[from * size + k] + dist[k * size + to] <
            dist[from * size + to])
          dist[from * size + to] = dist[from * size + k] + dist[k * size + to];

  cout << "\nAll pair shortest paths:";
  print_matrix(dist, size);

  delete[] dist;
}

#endif