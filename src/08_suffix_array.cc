#include <cstring>  // strlen
#include "../inc/suffix_array.h"

int main() {
  char string[] = "banana";
  int n = strlen(string);
  cout << "\nstring = '" << string << "'\n";

  int *suffix_array = Suffix_Array(string, n);
  cout << "\n\nSuffix array = ";
  print_array(suffix_array, n);

  return 0;
}