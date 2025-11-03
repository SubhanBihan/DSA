#include <iostream>
#include <vector>
#include <algorithm>

long long MaxPairwiseProduct(const std::vector<int>& numbers) {
    if (numbers.size() < 2) {
        return 0; // Not enough numbers to form a pair
    }

    // Find the two largest numbers
    int max1 = 0, max2 = 0;
    for (int x : numbers) {
        if (x > max1) {
            max2 = max1; // Update second largest
            max1 = x;    // Update largest
        } else if (x > max2) {
            max2 = x;    // Update second largest
        }
    }

    return static_cast<long long>(max1) * max2;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }

    std::cout << MaxPairwiseProduct(numbers);
    return 0;
}
