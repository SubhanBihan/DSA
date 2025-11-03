#include <iostream>
#include <cassert>

int get_fibonacci_last_digit_naive(int n) {
    if (n <= 1)
        return n;

    int previous = 0;
    int current  = 1;

    for (int i = 0; i < n - 1; ++i) {
        int tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % 10;
}

int get_fibonacci_last_digit_fast(int n) {
    const int pisano_period = 60; // Pisano period mod 10 is always 60
    int r = n % pisano_period;

    if (r <= 1) return r;

    int prev = 0, curr = 1;
    for (int i = 2; i <= r; ++i) {
        int next = (prev + curr) % 10;
        prev = curr;
        curr = next;
    }
    return curr;
}

void test_solution() {
    assert(get_fibonacci_last_digit_fast(3) == 2);
    assert(get_fibonacci_last_digit_fast(139) == 1);
    assert(get_fibonacci_last_digit_fast(91239) == 6);
    std::cout << "Tests passed!" << std::endl;
}
int main() {
    // test_solution();

    int n;
    std::cin >> n;
    // int c = get_fibonacci_last_digit_naive(n);
    // std::cout << c << '\n';
    std::cout << get_fibonacci_last_digit_fast(n) << '\n';
    return 0;
    }
