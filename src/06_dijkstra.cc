#include <iostream>

#include "../inc/dijkstra.h"
// #include "../inc/graph.h"

int main() {
  Graph<int> g(5);

  g.add_edge(1, 0);
  g.add_edge(0, 2);
  g.add_edge(2, 1);
  g.add_edge(0, 3);
  g.add_edge(3, 4);

  g.print_edges();

  // g.Dijkstra(1);

  return 0;
}