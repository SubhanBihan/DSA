#include <iostream>
#include <cassert>

struct Matrix2x2 {
    long long a, b, c, d;

    Matrix2x2 multiply(const Matrix2x2& other) const {
        return {
            (a * other.a + b * other.c),
            (a * other.b + b * other.d),
            (c * other.a + d * other.c),
            (c * other.b + d * other.d)
        };
    }

    Matrix2x2 power(long long n) const {
        Matrix2x2 result = {1, 0, 0, 1}; // identity
        Matrix2x2 base = *this;

        while (n > 0) {
            if (n % 2 == 1)
                result = result.multiply(base);
            base = base.multiply(base);
            n /= 2;
        }
        return result;
    }
};

long long fibonacci_sum_fast_ld(long long n) {
    if (n <= 1) return n;

    n = (n + 2) % 60;
    if (n <= 1) return (n + 9) % 10;

    Matrix2x2 fib = {1, 1, 1, 0};
    Matrix2x2 res = fib.power(n - 1);

    return (res.a - 1) % 10;
}


int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_fast_ld(n);
}
