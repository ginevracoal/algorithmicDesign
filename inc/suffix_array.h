/*
Suffix array algorithm.
*/

#ifndef __suffix_array__
#define __suffix_array__

#include <algorithm>  // std::sort
#include <iostream>   // std::cout

using namespace std;

// Suffix structure
struct suffix {
  int index;    // suffix index
  int rank[2];  // rank and next rank
};

// Compare two suffixes based on their rank couples and return 1 if the first
// pair is smaller, 0 otherwise
int cmp(struct suffix t1, struct suffix t2) {
  if (t1.rank[0] == t2.rank[0])
    return t1.rank[1] < t2.rank[1];
  else
    return t1.rank[0] < t2.rank[0];
}

// Builds the suffix array on a given string
int* Suffix_Array(char* string, int n) {
  cout << "\n###### Suffix Array ######";

  // Array of suffixes for the given string
  struct suffix suffixes[n];

  // Array of sorted suffixes indexes
  int* suffix_array = new int[n];

  // indexes array used for sorting
  int idx[n];

  // Extract all suffixes and store the index information
  // rank is letter index inside the alphabet
  for (int i = 0; i < n; ++i) {
    suffixes[i].index = i;
    suffixes[i].rank[0] = string[i] - 'a';
    if (i + 1 < n)
      suffixes[i].rank[1] = string[i + 1] - 'a';
    else
      suffixes[i].rank[1] = -1;  // end of the suffix
  }

#ifdef DEBUG
  cout << "\nindex \tsuffix \trank \tnext rank";
  for (int i = 0; i < n; ++i) {
    cout << endl << suffixes[i].index << "\t";
    for (int j = suffixes[i].index; j < n; j++) cout << string[j];
    cout << "\t" << suffixes[i].rank[0] << "\t" << suffixes[i].rank[1];
  }
#endif

  // Sort the suffixes according to the first 2 characters (rank, next rank)
  sort(suffixes, suffixes + n, cmp);

#ifdef DEBUG
  cout << "\n\nAfter sorting:\n";
  cout << "\nindex \tsuffix \trank \tnext rank";
  for (int i = 0; i < n; ++i) {
    cout << endl << suffixes[i].index << "\t";
    for (int j = suffixes[i].index; j < n; j++) cout << string[j];
    cout << "\t" << suffixes[i].rank[0] << "\t" << suffixes[i].rank[1];
  }

  cout << "\n\nUpdating new rank:\n";
  cout << "\nindex \tnew rank \t(rank, next rank)";
#endif

  // Sort the suffixes according to the first 2k characters, for each k
  for (int k = 4; k < n; k = k * 2) {
    // Assigning rank and index values to first suffix
    int rank = 0;
    // at each step store the old rank to compare it with the new one
    int old_rank = suffixes[0].rank[0];
    suffixes[0].rank[0] = rank;
    idx[suffixes[0].index] = 0;

    // Update rank for all suffixes
    for (int i = 1; i < n; i++) {
#ifdef DEBUG
      cout << endl << suffixes[i].index << "\t" << rank;
      cout << "\t\t(" << suffixes[i].rank[0] << "," << suffixes[i].rank[1]
           << ") ";
#endif

      // If the new rank couple is equal to the old one, assign the same new
      // rank to the suffix
      if (suffixes[i].rank[0] == old_rank &&
          suffixes[i].rank[1] == suffixes[i - 1].rank[1]) {
        old_rank = suffixes[i].rank[0];
        suffixes[i].rank[0] = rank;
      } else {  // Otherwise rank increases
        old_rank = suffixes[i].rank[0];
        suffixes[i].rank[0] = ++rank;
      }
      idx[suffixes[i].index] = i;
    }

    // Update next rank for every suffix
    for (int i = 0; i < n; i++) {
      int next_idx = suffixes[i].index + k / 2;
      if (next_idx < n)
        suffixes[i].rank[1] = suffixes[idx[next_idx]].rank[0];
      else
        suffixes[i].rank[1] = -1;
    }

#ifdef DEBUG
    cout << "\n\nAlso updating next rank:\n";
    cout << "\nindex \trank \tnext rank";
    for (int i = 0; i < n; ++i) {
      cout << endl << suffixes[i].index << "\t";
      for (int j = suffixes[i].index; j < n; j++) cout << string[j];
      cout << "\t" << suffixes[i].rank[0] << "\t" << suffixes[i].rank[1];
    }
#endif

    // Sort the suffixes according to first k characters
    sort(suffixes, suffixes + n, cmp);

#ifdef DEBUG
    cout << "\n\nAfter sorting:\n";
    cout << "\nindex \trank \tnext rank";
    for (int i = 0; i < n; ++i) {
      cout << endl << suffixes[i].index << "\t";
      for (int j = suffixes[i].index; j < n; j++) cout << string[j];
      cout << "\t" << suffixes[i].rank[0] << "\t" << suffixes[i].rank[1];
    }
#endif
  }

  // Store suffix array indexes
  for (int i = 0; i < n; ++i) {
    suffix_array[i] = suffixes[i].index;
  }

  return suffix_array;
}

void print_array(int* p, int n) {
  for (int i = 0; i < n; i++) cout << p[i] << " ";
  cout << endl;
}

// void print_status(struct suffixes, int n) {
//   cout << "\nindex \tsuffix \trank \tnext rank";
//   for (int i = 0; i < n; ++i) {
//     cout << endl << suffixes[i].index << "\t";
//     for (int j = suffixes[i].index; j < n; j++) cout << string[j];
//     cout << "\t" << suffixes[i].rank[0] << "\t" << suffixes[i].rank[1];
//   }
// }

#endif