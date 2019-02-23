#include <iostream>
#include "../inc/list.h"

int main() {
  list<int> list{};

  list.insert(3);
  list.insert(5);

  list.print();

  return 0;
}