// #include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

#define NUMCHARS 5

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


string InverseBWT(const string& bwt) {
  int counts[NUMCHARS] = {};
  vector<vector<int>> sym_counts(NUMCHARS - 1);
  for (auto& v: sym_counts) {
    v.reserve(bwt.size());
  }

  for (auto c: bwt) {
    counts[index(c)]++;

    for (int i = 0; i < sym_counts.size(); i++) {
      sym_counts[i].push_back(counts[i + 1]);
    }
  }

  int cumulative[NUMCHARS];
  cumulative[0] = counts[0];
  for (size_t i = 1; i < NUMCHARS; i++) {
    cumulative[i] = cumulative[i - 1] + counts[i];
  }

  string text;
  text.resize(bwt.size());
  text.back() = '$';

  int ind = 0;        // Last to first column index

  for (int i = bwt.size() - 2; i >= 0; i--) {
    auto c = text[i] = bwt[ind];
    auto j = index(c) - 1;
    ind = cumulative[j] + sym_counts[j][ind] - 1;
  }

  return text;
}

int main() {
  string bwt;
  cin >> bwt;
  auto text = InverseBWT(bwt);
  cout << text << endl;
  
  return EXIT_SUCCESS;
}
