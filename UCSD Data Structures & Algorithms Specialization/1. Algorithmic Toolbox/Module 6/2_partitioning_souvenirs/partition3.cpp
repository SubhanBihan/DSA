#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric>

using namespace std;

// Helper function for memoization key
string makeKey(int i, int a, int b) {
    return to_string(i) + "-" + to_string(a) + "-" + to_string(b);
}

// Recursive function with memoization
bool canPartition(int i, int a, int b, const vector<int>& nums, int target, unordered_map<string, bool>& memo) {
    if (i == nums.size()) {
        // If both subset A and B reach the target, the rest must be target too
        int total = accumulate(nums.begin(), nums.end(), 0);
        int c = total - a - b;
        return a == target && b == target && c == target;
    }

    string key = makeKey(i, a, b);
    if (memo.count(key)) return memo[key];

    int val = nums[i];
    bool res = false;

    // Try adding to subset A
    if (a + val <= target)
        res |= canPartition(i + 1, a + val, b, nums, target, memo);

    // Try adding to subset B
    if (!res && b + val <= target)
        res |= canPartition(i + 1, a, b + val, nums, target, memo);

    // Try adding to subset C (implicitly)
    if (!res)
        res |= canPartition(i + 1, a, b, nums, target, memo);

    return memo[key] = res;
}

bool is3PartitionPossible(vector<int>& nums) {
    int total = accumulate(nums.begin(), nums.end(), 0);
    if (total % 3 != 0) return false;

    int target = total / 3;
    unordered_map<string, bool> memo;
    return canPartition(0, 0, 0, nums, target, memo);
}

int main() {
  int n;
  std::cin >> n;
  vector<int> A(n);
  for (size_t i = 0; i < A.size(); ++i) {
    std::cin >> A[i];
  }
  std::cout << is3PartitionPossible(A) << '\n';
}
