#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

vector<int> fast_count_segments(const vector<int>& starts, const vector<int>& ends, const vector<int>& points) {
  vector<int> result;
  for (int point : points) {
    int left = std::upper_bound(starts.begin(), starts.end(), point) - starts.begin();
    int right = std::lower_bound(ends.begin(), ends.end(), point) - ends.begin();
    result.push_back(left - right);
  }
  return result;
}

int main() {
  int n, m;
  std::cin >> n >> m;

  vector<int> starts(n), ends(n);
  for (int i = 0; i < n; i++) {
    std::cin >> starts[i] >> ends[i];
    if (starts[i] > ends[i]) std::swap(starts[i], ends[i]);
  }

  vector<int> points(m);
  for (int i = 0; i < m; i++) std::cin >> points[i];

  std::sort(starts.begin(), starts.end());
  std::sort(ends.begin(), ends.end());

  vector<int> counts = fast_count_segments(starts, ends, points);
  for (int c : counts)
    std::cout << c << " ";
}
