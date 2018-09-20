#include <time.h>
#include <iostream>
#include "../inc/a_star.h"
// #include "../inc/dijkstra.h"

int main() {
  clock_t start, stop;
  double elapsed;

  Graph<int> g(7);

  g.add_edge(1, 0, 2);
  g.add_edge(0, 2, 8);
  g.add_edge(2, 1, 6);
  g.add_edge(0, 3, 3);
  g.add_edge(3, 4, 1);
  g.add_edge(4, 5, 0);
  g.add_edge(4, 6, 4);
  g.add_edge(1, 4, 5);
  g.add_edge(2, 7, 8);
  g.add_edge(3, 1, 3);
  g.add_edge(5, 6, 2);

  g.print_weighted_edges();

  start = clock();
  g.Dijkstra(1);
  stop = clock();
  elapsed = ((float)stop - start) * 1000.0 / CLOCKS_PER_SEC;
  cout << "\nDijkstra execution time: " << elapsed << "s" << endl;

  start = clock();
  g.Astar(1);
  stop = clock();
  elapsed = ((float)stop - start) * 1000.0 / CLOCKS_PER_SEC;
  std::cout << "\nA* execution time: " << elapsed << "s" << std::endl;

  return 0;
}