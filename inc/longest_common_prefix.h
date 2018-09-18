/*
This algorithm finds the longest common prefix between
suffixes in O(m+log n). This is also known as Kasai algorithm.
Text T has length n, while pattern P has length m.
*/

#ifndef __LCP__
#define __LCP__

#include <iostream>
#include "suffix_array.h"

void print_strings(char* string, int n, int* idx_array) {
  cout << "\ni \tidx \tsuffix";
  for (int i = 0; i < n; ++i) {
    cout << endl << i << " \t" << idx_array[i] << "\t";
    for (int j = idx_array[i]; j < n; j++) cout << string[j];
  }
  cout << endl;
}

void LCP(char* string, int n, int* SA) {
  cout << "\n###### LCP ######\n";

  int* lcp = new int[n];  // LCP array

  // this represents SA in inverse order of indexes and allows to access the
  // next suffix in the correct order
  int* inv_SA = new int[n];

  int k = 0;  // stores the length of LCP

  // Initalization
  for (int i = 0; i < n; ++i) {
    lcp[i] = 0;
    inv_SA[SA[i]] = i;
  }

#ifdef DEBUG
  cout << "\nSA:\n";
  print_strings(string, n, SA);
  cout << "\ninv_SA:\n";
  print_strings(string, n, inv_SA);
#endif

  // Read all already computed suffixes
  for (int i = 0; i < n; ++i) {
    // If current suffix is at n-1 it means that there is no LCP to compute for
    // it (it is the last character of the string).
    if (inv_SA[i] == n - 1) k = 0;

    // j is the index of the next substring we have to consider in the suffix
    // array
    int j = SA[inv_SA[i] + 1];

    // While characters starting from k match (they surely match till k)
    // increment k
    while (i + k < n && j + k < n && string[i + k] == string[j + k]) k++;

    lcp[inv_SA[i]] = k;  // lcp for current suffix

    // the next lcp value will be at least k-1, so we initialize it
    if (k > 0) k--;
  }

#ifdef DEBUG
  for (int i = 0; i < n; ++i) {
    cout << "\nlcp[" << i << "] = longest common prefix of '";
    for (int z = SA[i]; z < n; ++z) cout << string[z];
    cout << "' and '";
    for (int z = SA[i + 1]; z < n; ++z) cout << string[z];
    cout << "' = " << lcp[i];
  }
  cout << endl;
#endif

  cout << "\nLCP array = ";
  print_array(lcp, n);

  // return lcp;
}

#endif
