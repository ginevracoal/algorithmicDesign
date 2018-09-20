#include <cstring>  // strlen
#include "../inc/longest_common_prefix.h"
#include "../inc/suffix_array.h"

int main() {
  char string[] = "banana";
  int n = strlen(string);
  cout << "\nString = '" << string << "'\n";

  int *suffix_array = Suffix_Array(string, n);

  LCP(string, n, suffix_array);

  return 0;
}