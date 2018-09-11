/* Tarjan algorithm calculates the strongly connected components of a directed
  graph in O(|E|+|V|) time.
  disc stores the discovery time of visited nodes.
  lowlink[v] is the smallest index of any node known to be reachable from
  v, including v itself.
  To cope with the random traversal order of the DFS (which can give wrong
  lowlinks) nodes are added to the stack as they are explored for the first
  time, and removed from the stack when a complete SCC is found.
*/

// Right now it only works on int nodes

#include <iostream>
// #include <stack>
// #include <vector>
#include "../inc/graph.h"
#include "../inc/tarjan.h"

// #define NIL -1
// using namespace std;

int main() {
  Graph<int> g(5);

  g.add_edge(1, 0);
  g.add_edge(0, 2);
  g.add_edge(2, 1);
  g.add_edge(0, 3);
  g.add_edge(3, 4);

  g.print_edges();

  g.Tarjan_SCC();

  return 0;
}