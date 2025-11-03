#include <iostream>
#include <vector>
using std::vector;

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    long long sum = 0;

    long long current = 0;
    long long next  = 1;

    for (long long i = 0; i <= to; ++i) {
        if (i >= from) {
            sum += current;
        }

        long long new_current = next;
        next = next + current;
        current = new_current;
    }

    return sum % 10;
}

int fibonacci_p_sum_ld(long long m, long long n) {
    if (m > n)
        return 0;

    n = (n + 2) % 60;
    m = (m + 1) % 60;

    int k = std::max(n, m);

    if (k <= 1)
        return (10 + n - m) % 10;
    
    int j = std::min(n, m);
    
    int S_min = (j > 0);
    
    long long previous = 0;
    long long current = 1;
    for (int i = 2; i <= k; ++i) {
        long long new_current = previous + current;
        previous = current;
        current = new_current;
        if (i == j) S_min = current;
    }

    return (n > m) ? (current - S_min) % 10 : (10 + S_min % 10 - current % 10) % 10;
}

int main() {
    long long from, to;
    std::cin >> from >> to;
    // std::cout << get_fibonacci_partial_sum_naive(from, to) << '\n';
    std::cout << fibonacci_p_sum_ld(from, to) << '\n';
}
