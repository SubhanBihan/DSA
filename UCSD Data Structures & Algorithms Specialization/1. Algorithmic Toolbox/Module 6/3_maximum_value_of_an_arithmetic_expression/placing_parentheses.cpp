#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>

using namespace std;

// Apply arithmetic operation
long long eval(long long a, long long b, char op) {
    // if (op == '+') return a + b;
    // if (op == '-') return a - b;
    // return a * b; // op == '*'

    return (op == '+') ? a + b : (op == '-') ? a - b : a * b;
}

// Compute min and max for subexpression [i...j]
pair<long long, long long> minAndMax(int i, int j, const vector<vector<long long>>& min_dp, const vector<vector<long long>>& max_dp, const vector<char>& ops) {
    long long min_val = LONG_LONG_MAX;
    long long max_val = LONG_LONG_MIN;

    for (int k = i; k < j; ++k) {
        char op = ops[k];
        long long a = eval(max_dp[i][k], max_dp[k+1][j], op);
        long long b = eval(max_dp[i][k], min_dp[k+1][j], op);
        long long c = eval(min_dp[i][k], max_dp[k+1][j], op);
        long long d = eval(min_dp[i][k], min_dp[k+1][j], op);

        min_val = min({min_val, a, b, c, d});
        max_val = max({max_val, a, b, c, d});
    }

    return {min_val, max_val};
}

long long getMaxValue(const string& expr) {
    vector<int> digits;
    vector<char> ops;

    for (size_t i = 0; i < expr.size(); ++i) {
        if (i % 2 == 0)
            digits.push_back(expr[i] - '0');
        else
            ops.push_back(expr[i]);
    }

    int n = digits.size();
    vector<vector<long long>> min_dp(n, vector<long long>(n));
    vector<vector<long long>> max_dp(n, vector<long long>(n));

    for (int i = 0; i < n; ++i)
        min_dp[i][i] = max_dp[i][i] = digits[i];

    for (int l = 2; l <= n; ++l) {
        for (int i = 0; i <= n - l; ++i) {
            int j = i + l - 1;
            auto [min_val, max_val] = minAndMax(i, j, min_dp, max_dp, ops);
            min_dp[i][j] = min_val;
            max_dp[i][j] = max_val;
        }
    }

    return max_dp[0][n - 1];
}

int main() {
    string s;
    cin >> s;
    cout << getMaxValue(s) << endl;
}
