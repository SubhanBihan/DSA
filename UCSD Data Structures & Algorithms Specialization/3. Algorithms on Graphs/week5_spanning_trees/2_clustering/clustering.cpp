#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

using num_t = uint16_t;
using cord_t = int16_t;

struct Point {cord_t x, y;};

struct Edge {num_t a, b; double w;};

double euclid_dist(const Point& P1, const Point& P2) {
  return sqrt((P1.x - P2.x) * (P1.x - P2.x) + (P1.y - P2.y) * (P1.y - P2.y));
}

// Disjoint Set Union (DSU) with Path Compression + Rank
struct DSU {
  vector<num_t> parent, rankv;
  num_t trees;

  DSU(num_t n) {
    trees = n;
    parent.resize(n);
    rankv.resize(n, 0);
    for (num_t i = 0; i < n; i++)
        parent[i] = i;      // each node is its own parent initially
  }

  num_t find(num_t x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);   // path compression
    return parent[x];
  }

  bool unite(num_t a, num_t b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;          // already in same set
    
    // union by rank
    if (rankv[a] < rankv[b]) {
        parent[a] = b;
    } else if (rankv[a] > rankv[b]) {
        parent[b] = a;
    } else {
        parent[b] = a;
        rankv[a]++;
    }

    trees--;
    return true;
  }
};


int main() {
  num_t n;
  cin >> n;
  vector<Point> P(n);
  vector<Edge> E;
  E.reserve(n * (n - 1) / 2);

  for (auto &p : P)
    cin >> p.x >> p.y;

  num_t k;
  cin >> k;

  // Find and store all edges and their distances
  for (num_t i = 0; i < n - 1; i++)
    for (num_t j = i + 1; j < n; j++)
      E.push_back({i, j, euclid_dist(P[i], P[j])});

  sort(E.begin(), E.end(), [](const Edge& e1, const Edge& e2) { return e1.w < e2.w; });

  DSU dsu(n);

  for (const auto &e : E) {
    if (dsu.unite(e.a, e.b)) {
      if (dsu.trees + 1 == k) {
        // cout << fixed << setprecision(10) << e.w;
        printf("%.010f", e.w);
        break;
      }
    }
  }

  return EXIT_SUCCESS;
}

