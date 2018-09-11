/* Tarjan algorithm calculates the strongly connected components of a directed
  graph in O(|E|+|V|) time.
  disc stores the discovery time of visited nodes.
  lowlink[v] is the smallest index of any node known to be reachable from
  v, including v itself.
  To cope with the random traversal order of the DFS (which can give wrong
  lowlinks) nodes are added to the stack as they are explored for the first
  time, and removed from the stack when a complete SCC is found.
*/

#include <iostream>
#include <stack>
#include <vector>
#include "../inc/graph.h"

#define NIL -1
using namespace std;

// =====================================================

// Graph public member function
template <typename T>
void Graph<T>::Tarjan_SCC() {
  int *disc = new int[size];
  int *lowlink = new int[size];
  bool *onStack = new bool[size];
  stack<T> *Q = new stack<T>();

  /** initialization */
  for (int i = 0; i < size; ++i) {
    disc[i] = lowlink[i] = NIL;
    onStack[i] = false;  // i-th node has not been visited yet
  }

/** For each non discovered node, call the recursive function to find the
 * correspondent SCC.
 */

#ifdef DEBUG
  cout << "\nnode(disc, lowlink) couples:\n";
#endif

  for (int i = 0; i < size; ++i) {
    if (disc[i] == NIL) {
      Tarjan_SCC_rec(i, disc, lowlink, Q, onStack);
    }
  }

  // setting the number of strongly connected components
  print_SCCs();
}

// Graph private recursive member function
template <typename T>
void Graph<T>::Tarjan_SCC_rec(int v, T *disc, T *lowlink, stack<T> *Q,
                              bool *onStack) {
  /** index counts the number of SCCs. It preserves its value even when out of
   * scope. */
  static int index = 0;

  /** update disc and lowlink */
  disc[v] = lowlink[v] = ++index;

  /** add the current node to the stack */
  Q->push(v);

  /** mark it as being on the stack */
  onStack[v] = true;

  /** To visit all the adjacent nodes we use an iterator on the adjacency list
   * of v. We have to specify typename, otherwise the compiler cannot interpret
   * T as a type. */
  for (typename list<T>::iterator it = adj[v].begin(); it != adj[v].end();
       ++it) {
    int w = *it;

    /** If w has not been discovered yet, call the recursive function and update
     * the lowlink. Else, if w is on the stack, only update the lowlink. */
    if (disc[w] == -1) {
      Tarjan_SCC_rec(w, disc, lowlink, Q, onStack);
      lowlink[v] = min(lowlink[v], lowlink[w]);
    } else if (onStack[w] == true) {
      lowlink[v] = min(lowlink[v], disc[w]);
    }
  }

  /** Check if we are at the start of a SCC. This is true whenever id equals the
   * lowlink. */
  int z = 0;
  if (lowlink[v] == disc[v]) {
    /** Pop all the nodes of the SCC off the stack and mark them as not being on
     * the stack.
     */
    vector<T> component;  // new scc

    // OLD CODE
    // n_SCCs++;
    // cout << endl << "\nSCC " << n_SCCs << ": ";

    while (Q->top() != v) {
      z = Q->top();
      onStack[z] = false;
      Q->pop();

      component.push_back(z);

#ifdef DEBUG
      cout << z << "(" << disc[z] << "," << lowlink[z] << ") ";
#endif
    }

    z = Q->top();

#ifdef DEBUG
    cout << z << "(" << disc[z] << "," << lowlink[z] << ") \n";
#endif

    onStack[z] = false;
    Q->pop();
    component.push_back(z);
    SCCs->push_back(component);
  }
}

// =====================================================

int main() {
  Graph<int> g1(5);
  g1.add_edge(1, 0);
  g1.add_edge(0, 2);
  g1.add_edge(2, 1);
  g1.add_edge(0, 3);
  g1.add_edge(3, 4);

  g1.print_edges();

  g1.Tarjan_SCC();

  return 0;
}