#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
  double value = 0.0;

  // write your code here
  std::vector<std::pair<double, int>> value_per_weight(weights.size());
  std::transform(weights.begin(), weights.end(), values.begin(), value_per_weight.begin(),
                 [](int weight, int value) { return weight == 0 ? std::make_pair(0.0, 0) : std::make_pair(static_cast<double>(value) / weight, weight); });

  std::sort(value_per_weight.begin(), value_per_weight.end(), [](const auto& a, const auto& b) {return a.first > b.first;});

  int capacity_left = capacity;

  for (const auto& [value_per_unit, weight] : value_per_weight) {
    if (capacity_left == 0) break;

    int weight_to_take = std::min(weight, capacity_left);
    value += weight_to_take * value_per_unit;
    capacity_left -= weight_to_take;
  } 

  return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
