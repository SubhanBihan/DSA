// #include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
// #include <utility>
#include <numeric>
#include <climits>

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
auto BuildSuffixLCPArray(const string& S) {
  auto order = SortCharacters(S);
  auto Class = ComputeCharClasses(S, order);
  auto L = 1;

  while (L < S.size()) {
    order = SortDoubled(S, L, order, Class);
    Class = UpdateClasses(order, Class, L);
    L *= 2;
  }

  return make_pair(order, Class);
}


/* ===================== RMQ (Sparse Table) ===================== */

struct RMQ {
    int n;
    vector<Vec> st;
    Vec lg;

    RMQ(const Vec& v) {
        n = (int)v.size();
        lg.resize(n + 1);
        lg[1] = 0;
        for (int i = 2; i <= n; i++)
            lg[i] = lg[i / 2] + 1;

        int K = lg[n] + 1;
        st.assign(K, Vec(n));
        st[0] = v;

        for (int k = 1; k < K; k++) {
            for (int i = 0; i + (1 << k) <= n; i++) {
                st[k][i] = min(st[k - 1][i],
                               st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    // query min on [l, r], inclusive
    int query(int l, int r) const {
        if (l > r) return INT_MAX;
        int len = r - l + 1;
        int k = lg[len];
        return min(st[k][l], st[k][r - (1 << k) + 1]);
    }
};

/* ===================== LCP between suffixes ===================== */

int lcp_sa(int i, int j, const RMQ& rmq) {
    if (i == j) return INT_MAX;
    if (i > j) swap(i, j);
    // LCP[i+1 .. j]
    return rmq.query(i + 1, j);
}

/* ===================== Pattern vs suffix compare ===================== */

enum Cmp { LESS, GREATER, EQUAL_PREFIX };

Cmp compare_from(const string& P, const string& T,
                 int suffix_pos, int start) {
    int i = start;
    int n = T.size();
    int m = P.size();

    while (i < m && suffix_pos + i < n) {
        if (P[i] < T[suffix_pos + i]) return LESS;
        if (P[i] > T[suffix_pos + i]) return GREATER;
        i++;
    }
    if (i == m) return EQUAL_PREFIX;
    return GREATER;
}

/* ===================== LCP-optimized lower bound ===================== */

int lower_bound_lcp(const string& P,
                    const string& T,
                    const Vec& SA,
                    const RMQ& rmq) {
    int n = SA.size();
    int lo = 0, hi = n;
    int lcp_lo = 0;

    while (lo < hi) {
        int mid = (lo + hi) / 2;

        int common;
        if (mid == lo)
            common = lcp_lo;
        else
            common = min(lcp_lo, lcp_sa(lo, mid, rmq));

        Cmp res = compare_from(P, T, SA[mid], common);

        if (res == GREATER) {
            lo = mid + 1;
            lcp_lo = common;
        } else {
            hi = mid;
        }
    }
    return lo;
}

/* ===================== LCP-optimized upper bound ===================== */

int upper_bound_lcp(const string& P,
                    const string& T,
                    const Vec& SA,
                    const RMQ& rmq) {
    int n = SA.size();
    int lo = 0, hi = n;
    int lcp_lo = 0;

    while (lo < hi) {
        int mid = (lo + hi) / 2;

        int common;
        if (mid == lo)
            common = lcp_lo;
        else
            common = min(lcp_lo, lcp_sa(lo, mid, rmq));

        Cmp res = compare_from(P, T, SA[mid], common);

        if (res == LESS) {
            hi = mid;
        } else {
            lo = mid + 1;
            lcp_lo = common;
        }
    }
    return lo;
}

int main() {
  string S;
  int p;

  cin >> S;
  S.push_back('$');
  // S = "AAA$";

  auto sfx_lcp = BuildSuffixLCPArray(S);

  auto sfx_arr = std::move(sfx_lcp.first);
  auto lcp_arr = std::move(sfx_lcp.second);

  int n = S.size();
  vector<bool> seen(n, false);  // mark positions once
  RMQ rmq(lcp_arr);
  Vec result;
  result.reserve(n - 1);

  cin >> p;

  for (int i = 0; i < p; i++) {
    string P;
    cin >> P;

    if (P.size() > n - 1) continue;

    // Find occurences
    int l = lower_bound_lcp(P, S, sfx_arr, rmq);
    int r = upper_bound_lcp(P, S, sfx_arr, rmq);

    for (int i = l; i < r; i++) {
      auto ind = sfx_arr[i];
      if (!seen[ind]) {
        seen[ind] = true;
        result.push_back(ind);      // Any order allowed!
        printf("%d ", ind);
      }
    }
  }

  // for (int i = 0; i < n; i++) {
  //   if (seen[i]) {
  //     result.push_back(i);
  //     printf("%d ", i);
  //   }
  // }

  printf("\n");

  return 0;
}
