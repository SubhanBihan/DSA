#include <iostream>
#include <cassert>

struct Matrix2x2 {
    long long a, b, c, d;

    Matrix2x2 multiply(const Matrix2x2& other, long long mod) const {
        return {
            (a * other.a + b * other.c) % mod,
            (a * other.b + b * other.d) % mod,
            (c * other.a + d * other.c) % mod,
            (c * other.b + d * other.d) % mod
        };
    }

    Matrix2x2 power(long long n, long long mod) const {
        Matrix2x2 result = {1, 0, 0, 1}; // identity
        Matrix2x2 base = *this;

        while (n > 0) {
            if (n % 2 == 1)
                result = result.multiply(base, mod);
            base = base.multiply(base, mod);
            n /= 2;
        }
        return result;
    }
};

// long long get_fibonacci_huge_naive(long long n, long long m) {
//     if (n <= 1)
//         return n;

//     long long previous = 0;
//     long long current  = 1;

//     for (long long i = 0; i < n - 1; ++i) {
//         long long tmp_previous = previous;
//         previous = current;
//         current = (tmp_previous + current) % m;
//     }

//     return current;
// }

// long long get_pisano_period(long long m) {
//     long long previous = 0;
//     long long current  = 1;

//     for (long long i = 0; i < 6 * m; ++i) {
//         long long tmp_previous = previous;
//         previous = current;
//         current = (tmp_previous + current) % m;

//         // A Pisano period starts with 0, 1
//         if (previous == 0 && current == 1) {
//             return i + 1;
//         }
//     }
//     return -1; // Should never reach here
// }

long long get_fibonacci_huge_fast(long long n, long long m) {
    if (n <= 1) return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 2; ; ++i) {
        long long next = (previous + current) % m;
        previous = current;
        current = next;

        if (previous == 0 && current == 1) {
            n %= (i - 1);

            if (n <= 1)
                return n;

            // previous = 0;
            // current = 1;
            // for (long long j = 2; j <= n; ++j) {
            //     next = (previous + current) % m;
            //     previous = current;
            //     current = next;
            // }
            // return current;

            Matrix2x2 fib = {1, 1, 1, 0};
            Matrix2x2 res = fib.power(n, m);

            return res.c;
        }

        if (i == n)
            return current;
    }
}

int main() {
    long long n, m;
    std::cin >> n >> m;
    std::cout << get_fibonacci_huge_fast(n, m) << '\n';
}
