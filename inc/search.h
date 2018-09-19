#ifndef __search__
#define __search__

#include "graph.h"

template <typename T>
void print_list(list<T> l) {  // it cannot modify any member of list
  for (auto it = l.begin(); it != l.end(); ++it) cout << *it << " ";
  cout << endl;
}

template <typename T>
void Graph<T>::BFS(int s) {  // Node search in O(|V|+|E|)
  cout << "\n###### Breadth First Search ######\n";
  cout << "\nBFS(" << s << "): ";

  bool *visited = new bool[size]{false};  // marks visited nodes
  list<int> queue;                        // creates a queue for visited nodes

  // Current node has been visited and is inside the queue
  visited[s] = true;
  queue.push_back(s);

  // for (int j = 0; j < 4; j++) {
  while (!queue.empty()) {
#ifdef DEBUG
    cout << "\nVisited nodes: ";
    for (int i = 0; i < size; ++i) cout << visited[i] << " ";
    cout << "\nCurrent queue: ";
    // queue.print(); // list.h member function
    print_list(queue);
    cout << endl;
#endif

    int curr = queue.front();
    cout << curr << " ";
    queue.pop_front();

#ifdef DEBUG
    cout << "\nAfter pop queue: ";
    // queue.print();// list.h member function
    print_list(queue);
    cout << "adj(" << curr << "): ";
#endif

    for (auto it = adj[curr].begin(); it != adj[curr].end(); it++) {
#ifdef DEBUG
      cout << *it << " ";
#endif
      if (!visited[*it]) {  // node has not been visited
        visited[*it] = true;
        queue.push_back(*it);
      }
    }
  }

  cout << endl;

  delete visited;
}

template <typename T>
void Graph<T>::DFS_recur(int curr, bool visited[]) {
  visited[curr] = true;
  cout << curr << " ";

  for (auto it = adj[curr].begin(); it != adj[curr].end(); it++)
    if (!visited[*it]) DFS_recur(*it, visited);
}

template <typename T>
void Graph<T>::DFS(int s) {  // Node search in O(|V|+|E|)
  cout << "\n###### Depth First Search ######\n";
  cout << "\nDFS(" << s << "): ";

  bool *visited = new bool[size]{false};  // marks visited nodes

  DFS_recur(s, visited);
  cout << endl;
}

#endif