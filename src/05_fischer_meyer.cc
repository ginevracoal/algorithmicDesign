/**
Descrizione generale dell'algoritmo e della complessità
*/

#include <iostream>
#include "../inc/fischer_meyer.h"
#include "../inc/graph.h"

int main() {
  Graph<int> g(5);

  g.add_edge(1, 0);
  g.add_edge(0, 2);
  g.add_edge(2, 1);
  g.add_edge(0, 3);
  g.add_edge(3, 4);

  g.print_edges();

  g.Fischer_Meyer();

  return 0;
}