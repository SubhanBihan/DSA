#include <iostream>
#include <vector>
#include <algorithm>

// Function to compute min number of operations and path to reach 'n'
void minOperationsSequence(int n) {
    std::vector<int> dp(n + 1);       // dp[i] = min ops to reach i
    std::vector<int> prev(n + 1);     // prev[i] = previous number in optimal path

    dp[1] = 0;
    prev[1] = 0;

    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1] + 1;
        prev[i] = i - 1;

        if (i % 2 == 0 && dp[i / 2] + 1 < dp[i]) {
            dp[i] = dp[i / 2] + 1;
            prev[i] = i / 2;
        }

        if (i % 3 == 0 && dp[i / 3] + 1 < dp[i]) {
            dp[i] = dp[i / 3] + 1;
            prev[i] = i / 3;
        }
    }

    // Print the number of operations
    std::cout << dp[n] << std::endl;

    // Reconstruct the sequence
    std::vector<int> sequence;
    for (int i = n; i != 0; i = prev[i]) {
        sequence.push_back(i);
    }
    std::reverse(sequence.begin(), sequence.end());

    // Print the sequence
    for (int x : sequence) {
        std::cout << x << " ";
    }
    // std::cout << std::endl;
}

int main() {
  int n;
  std::cin >> n;
  // vector<int> sequence = optimal_sequence(n);
  // std::cout << sequence.size() - 1 << std::endl;
  // for (size_t i = 0; i < sequence.size(); ++i) {
  //   std::cout << sequence[i] << " ";
  // }
  minOperationsSequence(n);
}
