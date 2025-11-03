#include <iostream>
#include <cassert>

// The following code calls a naive algorithm for computing a Fibonacci number.
//
// What to do:
// 1. Compile the following code and run it on an input "40" to check that it is slow.
//    You may also want to submit it to the grader to ensure that it gets the "time limit exceeded" message.
// 2. Implement the fibonacci_fast procedure.
// 3. Remove the line that prints the result of the naive algorithm, comment the lines reading the input,
//    uncomment the line with a call to test_solution, compile the program, and run it.
//    This will ensure that your efficient algorithm returns the same as the naive one for small values of n.
// 4. If test_solution() reveals a bug in your implementation, debug it, fix it, and repeat step 3.
// 5. Remove the call to test_solution, uncomment the line with a call to fibonacci_fast (and the lines reading the input),
//    and submit it to the grader.

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

long long fibonacci_naive(long long n) {
    if (n <= 1)
        return n;

    return fibonacci_naive(n - 1) + fibonacci_naive(n - 2);
}

long long fibonacci_fast(long long n) {
    if (n <= 1)
        return n;
    
    long long previous = 0;
    long long current = 1;
    for (long long i = 2; i <= n; ++i) {
        long long new_current = previous + current;
        previous = current;
        current = new_current;
    }

    return current;
}

long long fibonacci_faster(long long n) {
    if (n <= 1) return n;

    Matrix2x2 fib = {1, 1, 1, 0};
    Matrix2x2 res = fib.power(n - 1);

    return res.a;
}

void test_solution() {
    assert(fibonacci_fast(3) == 2);
    assert(fibonacci_fast(10) == 55);
    for (long long n = 0; n < 20; ++n)
        assert(fibonacci_fast(n) == fibonacci_naive(n));

    std::cout << "Tests passed!" << std::endl;
}

int main() {
    long long n = 0;
    std::cin >> n;

    // std::cout << fibonacci_naive(n) << '\n';
    // test_solution();
    // std::cout << fibonacci_fast(n) << '\n';
    std::cout << fibonacci_faster(n) << '\n';
    return 0;
}
