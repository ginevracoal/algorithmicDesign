#include <iostream>

#include "../inc/dijkstra.h"
// #include "../inc/graph.h"

int main() {
  Graph<int> g(5);

  g.add_edge(1, 0, 2);
  g.add_edge(0, 2, 0);
  g.add_edge(2, 1, 6);
  g.add_edge(0, 3, 3);
  g.add_edge(3, 4, 1);

  g.print_weighted_edges();

  g.Dijkstra(1);

  return 0;
}