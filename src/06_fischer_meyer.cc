/*Fischer Meyer algorithm solves the transitive closure problem with complexity
O(|V|^log_2(7)) instead of the O(|V|^2|E|) given by the classical search.
*/

#include <iostream>
#include "../inc/fischer_meyer.h"

int main() {
  Graph<int> g(5);  // size 5 graph constructor

  g.add_edge(1, 0);
  g.add_edge(0, 3);
  g.add_edge(3, 1);
  g.add_edge(0, 4);
  g.add_edge(4, 2);

  g.print_edges();

  // g.Fischer_Meyer();

  return 0;
}