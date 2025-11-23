#include <cstdint>
#include <iostream>
#include <vector>

using std::vector;
using std::pair;
using std::swap;

struct DSU {
    vector<uint16_t> parent, rank;

    DSU(uint16_t n) : parent(n), rank(n, 0) {
        for (uint16_t i = 0; i < n; i++) parent[i] = i;
    }

    uint16_t find(uint16_t x) {
        while (parent[x] != x)
            x = parent[x];
        return x;
    }

    bool unionSet(uint16_t a, uint16_t b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;          // same root -> cycle

        // union by rank
        if (rank[a] < rank[b]) swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b]) rank[a]++;

        return true;
    }
};


int main() {
  size_t n, m;
  std::cin >> n >> m;

  DSU dsu(n);

  // vector<vector<uint16_t>> adj(n, vector<uint16_t>());
  vector<pair<uint16_t, uint16_t>> edge(m);

  for (auto& e : edge) {
    std::cin >> e.first >> e.second;
  }
  
  for (auto& e : edge) {
    if (!dsu.unionSet(e.first - 1, e.second - 1)) {
      std::cout << 1 << "\n";
      return 0;
    }
  }

  std::cout << 0 << "\n";
  return 0;
}
