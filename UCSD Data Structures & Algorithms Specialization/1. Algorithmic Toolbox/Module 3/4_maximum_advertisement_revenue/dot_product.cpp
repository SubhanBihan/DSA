#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>

using std::vector;

long long max_dot_product(vector<int>& a, vector<int>& b) {
  // write your code here
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  return std::inner_product(
    a.begin(), a.end(), b.begin(), 0LL,
    std::plus<>(),
    [](int64_t x, int64_t y) { return x * y; }
);
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> a(n), b(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  for (size_t i = 0; i < n; i++) {
    std::cin >> b[i];
  }
  std::cout << max_dot_product(a, b) << std::endl;
}
