// #include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;

#define NUMCHARS 5

int counts[NUMCHARS] = {};
int cumulative[NUMCHARS];
vector<vector<int>> sym_counts(NUMCHARS - 1);

inline int index(char c) {
  switch (c) {
    case '$': return 0;
    case 'A': return 1;
    case 'C': return 2;
    case 'G': return 3;
    case 'T': return 4;
    default:  return -1;
  }
}

void PreprocessBWT(const string& bwt) {
  for (auto c: bwt) {
    counts[index(c)]++;

    for (int i = 0; i < sym_counts.size(); i++) {
      sym_counts[i].push_back(counts[i + 1]);
    }
  }

  cumulative[0] = counts[0];
  for (size_t i = 1; i < NUMCHARS; i++) {
    cumulative[i] = cumulative[i - 1] + counts[i];
  }
}

// auto NumOccur(const string& bwt, const string& pattern) {
//   int top = 0, bottom = bwt.size() - 1;

//   for (auto it = pattern.rbegin(); it != pattern.rend(); it++) {
//     auto ind = index(*it) - 1;
//     if (sym_counts[ind][max(top - 1, 0)] != sym_counts[ind][bottom]) {      // Meaning there's an occurence of the symbol between top and bottom
//       top    = cumulative[ind] + max(sym_counts[ind][top] - 1, 0);
//       bottom = cumulative[ind] + max(sym_counts[ind][bottom] - 1, 0);
//     }
//     else {
//       return 0;
//     }
//   }

//   return bottom - top + 1;
// }

int NumOccur(const string& bwt, const string& pattern) {
    int top = 0;
    int bottom = (int)bwt.size() - 1;

    for (auto it = pattern.rbegin(); it != pattern.rend(); ++it) {
        int ind = index(*it) - 1;  // A,C,G,T → 0..3

        int occ_top = (top == 0) ? 0 : sym_counts[ind][top - 1];
        int occ_bot = sym_counts[ind][bottom];

        // no occurrence in [top, bottom]
        if (occ_bot <= occ_top) {
            return 0;
        }

        top    = cumulative[ind] + occ_top;
        bottom = cumulative[ind] + occ_bot - 1;
    }

    return bottom - top + 1;
}


int main() {
  string bwt;
  cin >> bwt;

  // string bwt = "TCCTCTATGAGATCCTATTCTATGAAACCTTCA$GACCAAAATTCTCCGGC";

  for (auto& v: sym_counts) {
    v.reserve(bwt.size());
  }

  PreprocessBWT(bwt);

  int pattern_count;
  cin >> pattern_count;

  for (int pi = 0; pi < pattern_count; ++pi) {
    string pattern;
    cin >> pattern;
    auto ans = NumOccur(bwt, pattern);
    printf("%d ", ans);
  }

  // int pattern_count = 5;
  // vector<string> patterns = {"CCT", "CAC", "GAG", "CAG", "ATC"};
  // for (const auto& pattern: patterns) {
  //   auto ans = NumOccur(bwt, pattern);
  //   printf("%d ", ans);
  // }

  return 0;
}