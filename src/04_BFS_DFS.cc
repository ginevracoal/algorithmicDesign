#include <iostream>
#include "../inc/graph.h"

int main() {
  Graph<int> g(4);

  g.add_edge(0, 1);
  g.add_edge(0, 2);
  g.add_edge(1, 2);
  g.add_edge(2, 0);
  g.add_edge(2, 3);
  g.add_edge(3, 3);

  g.print_edges();

  g.BFS(2);
  g.DFS(2);

  return 0;
}