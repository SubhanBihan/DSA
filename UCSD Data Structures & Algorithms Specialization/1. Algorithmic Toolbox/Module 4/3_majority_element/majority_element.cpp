#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using std::vector;

int get_majority_element(vector<int> &a) {
  if (a.empty()) return -1;
  if (a.size() == 1) return a[0];
  //write your code here
  std::map<int, unsigned> counts;

  for (const auto &elem : a) {
    counts[elem]++;
  }

  auto max_it = std::max_element(counts.begin(), counts.end(), [](const auto &a, const auto &b) { return a.second < b.second; });
  return max_it->second > a.size() / 2 ;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << get_majority_element(a) << '\n';
}
