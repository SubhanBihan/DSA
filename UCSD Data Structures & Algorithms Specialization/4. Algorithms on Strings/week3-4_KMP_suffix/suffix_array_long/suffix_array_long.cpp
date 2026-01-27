// #include <algorithm>
#include <iostream>
#include <string>
#include <vector>
// #include <utility>
#include <numeric>

using namespace std;
using Vec = vector<int>;

#define ALPHABET_SIZE 5    // $, A, C, G, T

inline int index(char c) {
  switch (c) {
    case '$': return 0;
    case 'A': return 1;
    case 'C': return 2;
    case 'G': return 3;
    case 'T': return 4;
    default:  return -1;
  }
}

auto SortCharacters(const string& S) {
  Vec order(S.size()), count(ALPHABET_SIZE, 0);

  for (const auto& c: S) {
    count[index(c)]++;
  }

  // for (auto j = 1; j < ALPHABET_SIZE; j++) {
  //   count[j] += count[j - 1];
  // }

  partial_sum(count.begin(), count.end(), count.begin());

  for (auto rit = S.rbegin(); rit != S.rend(); rit++) {
    auto ind = --count[index(*rit)];
    order[ind] = S.rend() - rit - 1;
  }

  return order;
}

auto ComputeCharClasses(const string& S, const Vec& order) {
  Vec Class(S.size());

  Class[order.front()] = 0;

  for (auto i = 1; i < S.size(); i++) {
    Class[order[i]] = Class[order[i - 1]] + (S[order[i]] != S[order[i - 1]]);
  }

  return Class;
}

auto SortDoubled(const string& S, int L, const Vec& order, const Vec& Class) {
  Vec newOrder(S.size()), count(S.size(), 0);

  for (auto i = 0; i < S.size(); i++) {
    count[Class[i]]++;
  }

  partial_sum(count.begin(), count.end(), count.begin());

  for (int i = S.size() - 1; i >= 0; i--) {
    auto start = (order[i] - L + S.size()) % S.size();
    auto cl = Class[start];
    auto ind = --count[cl];
    newOrder[ind] = start;
  }

  return newOrder;
}

auto UpdateClasses(const Vec& newOrder, const Vec& Class, int L) {
  auto n = newOrder.size();
  Vec newClass(n);

  newClass[newOrder.front()] = 0;

  for (auto i = 1; i < n; i++) {
    auto cur = newOrder[i], prev = newOrder[i - 1];
    auto mid = (cur + L) % n, midPrev = (prev + L) % n;

    newClass[cur] = newClass[prev] + ((Class[cur] != Class[prev]) || (Class[mid] != Class[midPrev]));
  }

  return newClass;
}

// Build suffix array of the string S and return a vector result of the same length as the S such that the value result[i] is the index (0-based)
// in S where the i-th lexicographically smallest suffix of S starts.
auto BuildSuffixArray(const string& S) {
  auto order = SortCharacters(S);
  auto Class = ComputeCharClasses(S, order);
  auto L = 1;

  while (L < S.size()) {
    order = SortDoubled(S, L, order, Class);
    Class = UpdateClasses(order, Class, L);
    L *= 2;
  }

  return order;
}

int main() {
  string S;

  cin >> S;
  // S = "AAA$";

  auto suffix_array = BuildSuffixArray(S);

  for (const auto& a: suffix_array) {
    cout << a << ' ';
  }

  cout << endl;
  return 0;
}
