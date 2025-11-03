#include <iostream>
#include <vector>
#include <algorithm> // for max()

// Function to compute the maximum weight of gold that can be carried
int maxGoldInBackpack(int W, const std::vector<int>& weights) {
    int n = weights.size();

    // dp[i][w] represents the maximum gold we can carry using first i bars with capacity w
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1, 0));

    // Build the DP table
    for (int i = 1; i <= n; ++i) {
        int currentWeight = weights[i - 1];  // current bar's weight

        for (int w = 0; w <= W; ++w) {
            // Option 1: Don't take current bar
            dp[i][w] = dp[i - 1][w];

            // Option 2: Take current bar, if it fits
            if (currentWeight <= w) {
                dp[i][w] = std::max(dp[i][w], dp[i - 1][w - currentWeight] + currentWeight);
            }
        }
    }

    // The bottom-right cell contains the answer
    return dp[n][W];
}

int main() {
  int n, W;
  std::cin >> W >> n;
  std::vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  std::cout << maxGoldInBackpack(W, w) << '\n';
}
