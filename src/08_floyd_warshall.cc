#include <time.h>
#include <iostream>
#include "../inc/floyd_warshall.h"

int main() {
  clock_t start, stop;
  double elapsed;

  Graph<int> g(4);

  g.add_edge(0, 3, 10);
  g.add_edge(0, 1, 5);
  g.add_edge(1, 2, 3);
  g.add_edge(2, 3, 1);

  g.print_weighted_edges();

  start = clock();
  g.Floyd_Warshall();
  stop = clock();
  elapsed = ((float)stop - start) * 1000.0 / CLOCKS_PER_SEC;
  cout << "\nExecution time: " << elapsed << "s" << endl;

  return 0;
}
