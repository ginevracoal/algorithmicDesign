/** Tarjan algorithm calculates the strongly connected components of a directed
 * graph in O(|E|+|V|) time.
 * disc stores the discovery time of visited nodes.
 * lowlink[v] is the smallest index of any node known to be reachable from v,
 * including v itself.
 * To cope with the random traversal order of the DFS (which can give wrong
 * lowlinks) nodes are added to the stack as they are explored for the first
 * time, and removed from the stack when a complete SCC is found.
*/

// ============ TO DO ==============
// implementare stack e list

#include <iostream>
// #include <list>
#include <memory>  // for unique_ptr
#include <stack>
#include "../inc/list.h"

#define NIL -1

using namespace std;

template <typename T>
class Graph {
 private:
  /** Number of nodes */
  int size;
  int SCCs;

  /** Adjacency list of nodes */
  list<T> *adj;

  /** Node color identify their state: white has not been visited, grey has been
   * visited, black has been visited along with all its adjacent nodes. */
  // enum class color { white, grey, black };

  /** Recursive function used by Tarjan_SCC */
  void Tarjan_SCC_rec(int v, T *disc, T *low, stack<T> *Q, bool *onStack);

 public:
  /** Constructor */
  Graph(int size) {
    /** parameter size shadows the class member with the same name, so the
     * use of this-> is required */
    this->size = size;
    adj = new list<T>[size];  // allocates a new adjacency list
  }

  /** Adds the edge from node v to node w to the graph. */
  void add_edge(T v, T w) { adj[v].push_back(w); }

  void print_edges() {
    cout << "\nGraph edges are:";
    for (int v = 0; v < size; ++v) {
      for (typename list<T>::iterator i = adj[v].begin(); i != adj[v].end();
           ++i) {
        cout << endl << v << " " << *i;
      }
    }
    cout << endl;
  }

  /** Finds the strongly connected components */
  void Tarjan_SCC();
};

// =====================================================
/** Member functions
*/

template <typename T>
void Graph<T>::Tarjan_SCC() {
  cout << "\nTarjan SCCs are:\n";
  int *disc = new int[size];
  int *lowlink = new int[size];
  bool *onStack = new bool[size];
  stack<T> *Q = new stack<T>();

  /** initialization */
  for (int i = 0; i < size; ++i) {
    disc[i] = lowlink[i] = NIL;
    onStack[i] = false;
  }

  /** For each non discovered node, call the recursive function to find the
   * correspondent SCC.
   */
  for (int i = 0; i < size; ++i) {
    if (disc[i] == NIL) {
      Tarjan_SCC_rec(i, disc, lowlink, Q, onStack);
    }
  }
  cout << "\nThe number of SCCs is " << SCCs << ".\n";
}

template <typename T>
void Graph<T>::Tarjan_SCC_rec(int v, T *disc, T *lowlink, stack<T> *Q,
                              bool *onStack) {
  /** index counts the number of SCCs. It preserves its value even when out of
   * scope. */
  static int index = 0;

  /** update id and lowlink */
  disc[v] = lowlink[v] = ++index;

  /** add the current node to the stack */
  Q->push(v);

  /** mark it as being on the stack */
  onStack[v] = true;

  /** To visit all the adjacent nodes we use an iterator on the adjacency list
   * of v. We have to specify typename, otherwise the compiler cannot interpret
   * T as a type. */
  // typename list<T>::iterator it;
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
    SCCs++;
    while (Q->top() != v) {
      z = Q->top();
      cout << z << " ";
      onStack[z] = false;
      Q->pop();
      // We also want all the nodes from the same SCC to have the same id.
      disc[z] = index;  // potrebbe essere sbagliato
    }
    z = Q->top();
    cout << z << endl;
    onStack[z] = false;
    Q->pop();
  }
}

// =====================================================

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