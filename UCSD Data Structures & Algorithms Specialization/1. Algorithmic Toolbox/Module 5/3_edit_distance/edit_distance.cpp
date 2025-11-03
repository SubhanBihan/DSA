#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int editDistance(const std::string& s1, const std::string& s2) {
    int n = s1.size(), m = s2.size();

    // dp[i][j] = min operations to convert s1[0..i-1] to s2[0..j-1]
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));

    // Base cases
    for (int i = 0; i <= n; ++i) dp[i][0] = i;  // delete all characters
    for (int j = 0; j <= m; ++j) dp[0][j] = j;  // insert all characters

    // Bottom-up DP
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                // No operation needed
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = std::min({
                    dp[i - 1][j] + 1,     // Delete
                    dp[i][j - 1] + 1,     // Insert
                    dp[i - 1][j - 1] + 1  // Replace
                });
            }
        }
    }

    return dp[n][m];
}


int main() {
  std::string str1;
  std::string str2;
  std::cin >> str1 >> str2;
  std::cout << editDistance(str1, str2) << std::endl;
  return 0;
}
