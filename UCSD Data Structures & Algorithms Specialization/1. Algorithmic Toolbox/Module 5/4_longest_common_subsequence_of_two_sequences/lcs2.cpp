#include <iostream>
#include <vector>
#include <algorithm>

// Function to compute LCS length
int longestCommonSubsequence(const std::vector<int>& A, const std::vector<int>& B) {
    int n = A.size();
    int m = B.size();

    // dp[i][j] = LCS length of A[0..i-1], B[0..j-1]
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

    // Fill dp table
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1; // match
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]); // skip A or skip B
            }
        }
    }

    return dp[n][m];
}


int main() {
  size_t n;
  std::cin >> n;
  std::vector<int> a(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  size_t m;
  std::cin >> m;
  std::vector<int> b(m);
  for (size_t i = 0; i < m; i++) {
    std::cin >> b[i];
  }

  std::cout << longestCommonSubsequence(a, b) << std::endl;
}
