#include <iostream>
#include <cassert>

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

int gcd_fast(int a, int b) {
  assert(a >= 0 && b >= 0);     // Ensure non-negative inputs

  if (a == 0 || b == 0) {
    return a + b; // If one number is zero, return the other number
  }

  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

long long lcm_fast(int a, int b) {
  assert(a >= 0 && b >= 0); // Ensure non-negative inputs
  if (a == 0 || b == 0) {
    return 0; // LCM of zero with any number is zero
  }
  return (long long) a * b / gcd_fast(a, b);
}

int main() {
  int a, b;
  std::cin >> a >> b;
  // std::cout << lcm_naive(a, b) << std::endl;
  std::cout << lcm_fast(a, b) << std::endl;
  return 0;
}
