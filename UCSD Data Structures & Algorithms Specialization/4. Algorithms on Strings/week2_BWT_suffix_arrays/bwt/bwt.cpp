#include <algorithm>
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
// using std::pair;

// using Pair = pair<char, char>;

auto BWT(const string& text) {
  vector<string> bwt;
  bwt.reserve(text.size());

  for (size_t i = 0; i < text.size(); i++) {
    bwt.push_back(text.substr(i) + text.substr(0, i));
  }

  std::sort(bwt.begin(), bwt.end());

  string result;
  result.reserve(text.size());
  
  for (const auto s: bwt) {
    result.push_back(s.back());
  }

  return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;

  return EXIT_SUCCESS;
}