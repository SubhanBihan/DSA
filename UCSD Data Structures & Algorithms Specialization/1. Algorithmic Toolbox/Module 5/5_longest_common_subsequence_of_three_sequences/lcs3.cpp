#include <iostream>
#include <vector>
#include <algorithm>

int lcs3(const std::vector<int>& A, const std::vector<int>& B, const std::vector<int>& C) {
    int n = A.size();
    int m = B.size();
    int l = C.size();

    // 3D DP table: dp[i][j][k] = LCS length of A[0..i-1], B[0..j-1], C[0..k-1]
    std::vector<std::vector<std::vector<int>>> dp(
        n + 1, std::vector<std::vector<int>>(m + 1, std::vector<int>(l + 1, 0))
    );

    // Fill the DP table
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int k = 1; k <= l; ++k) {
                if (A[i - 1] == B[j - 1] && A[i - 1] == C[k - 1]) {
                    dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1;
                } else {
                    dp[i][j][k] = std::max({
                        dp[i - 1][j][k],
                        dp[i][j - 1][k],
                        dp[i][j][k - 1]
                    });
                }
            }
        }
    }

    return dp[n][m][l];
}

int main() {
  size_t an;
  std::cin >> an;
  std::vector<int> a(an);
  for (size_t i = 0; i < an; i++) {
    std::cin >> a[i];
  }
  size_t bn;
  std::cin >> bn;
  std::vector<int> b(bn);
  for (size_t i = 0; i < bn; i++) {
    std::cin >> b[i];
  }
  size_t cn;
  std::cin >> cn;
  std::vector<int> c(cn);
  for (size_t i = 0; i < cn; i++) {
    std::cin >> c[i];
  }
  std::cout << lcs3(a, b, c) << std::endl;
}
