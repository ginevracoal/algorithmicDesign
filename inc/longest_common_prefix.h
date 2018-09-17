/*
This algorithm finds the longest common prefix using SA in
O(m+log n). This is also known as Kasai algorithm.
Text T has length n, while pattern P has length m.
*/

#ifndef __LCP__
#define __LCP__

#include <iostream>
#include "suffix_array.h"

void LCP(char* string, int n, int* SA) {
  cout << "\n###### LCP ######\n";

  int* lcp = new int[n];     // LCP array
  int* inv_SA = new int[n];  // SA in inverse order
  int k = 0;                 // stores the length of LCP

  for (int i = 0; i < n; ++i) {
    lcp[i] = 0;
    inv_SA[SA[i]] = i;
  }

  for (int i = 0; i < n; ++i)  // for each suffix in SA
  {
    // If current suffix is at n-1 it means that there is no LCP to compute for
    // it.
    if (inv_SA[i] == n - 1) k = 0;

    // j is the index of the next substring we have to consider in the suffix
    // array
    int j = SA[inv_SA[i] + 1];

    //
    while (i + k < n && j + k < n && string[i + k] == string[j + k]) k++;

    lcp[inv_SA[i]] = k;

    if (k > 0) k--;
  }

  cout << "\nLCP array = ";
  print_array(lcp, n);

  // return lcp;
}

#endif
