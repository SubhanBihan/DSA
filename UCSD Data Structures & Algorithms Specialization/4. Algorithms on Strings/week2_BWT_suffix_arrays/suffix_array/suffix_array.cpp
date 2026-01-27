#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::vector;

using Pair = pair<string, int>;

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> BuildSuffixArray(const string& text) {
  vector<int> result;
  result.reserve(text.size());

  vector<Pair> suffixes;

  for (size_t i = 0; i < text.size(); i++) {
    suffixes.push_back({text.substr(i), i});
  }

  std::sort(suffixes.begin(), suffixes.end(), [](const Pair& p1, const Pair& p2){return p1.first < p2.first;});

  for (const auto& s: suffixes) {
    result.push_back(s.second);
  }

  return result;
}

int main() {
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}
