#include <iostream>
#include <vector>
#include <climits>

// Function to compute minimum number of coins to make change
int minCoins(const std::vector<int>& coins, int amount) {
    const int INF = INT_MAX - 1; // Prevent overflow in dp[i - c] + 1
    std::vector<int> dp(amount + 1, INF);

    dp[0] = 0; // Base case: 0 coins needed to make amount 0

    for (int i = 1; i <= amount; ++i) {
        for (int c : coins) {
            if (i >= c && dp[i - c] != INF) {
                dp[i] = std::min(dp[i], dp[i - c] + 1);
            }
        }
    }

    return (dp[amount] == INF) ? -1 : dp[amount];
}

int main() {
  int m;
  std::vector<int> coins = {1, 3, 4};
  std::cin >> m;
  std::cout << minCoins(coins, m) << '\n';
}
