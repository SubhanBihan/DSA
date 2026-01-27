#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where 
// the pattern starts in the text.
vector<int> find_pattern(const string& pattern, const string& text) {
  vector<int> result;
  
  if (pattern.size() <= text.size()) {
    const string combined = pattern + '$' + text;
    result.reserve(text.size() - pattern.size() + 1);

    vector<int> s(combined.size());

    s.front() = 0;
    int border = 0;

    for (int i = 1; i < combined.size(); i++) {
      while (border > 0 && combined[i] != combined[border]) {
        border = s[border - 1];
      }

      s[i] = border = (combined[i] == combined[border]) ? border + 1 : 0;

      if (s[i] == pattern.size()) 
        result.push_back(i - 2 * pattern.size());
    }
  }

  return result;
}

int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;
  auto result = find_pattern(pattern, text);
  for (const auto& i: result) {
    printf("%d ", i);
  }
  printf("\n");
  return 0;
}
