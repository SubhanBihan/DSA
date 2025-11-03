#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>

using namespace std;


void reach(const unordered_map<uint16_t, unordered_set<uint16_t>> &adj, vector<bool> &visited, const uint16_t &x, const uint16_t &y) {
  visited[x - 1] = true;

  if (adj.at(x).contains(y)) {
    visited[y - 1] = true;
    return;
  }
  else {
    for (const auto &v : adj.at(x)) {
      if (visited[v - 1]) continue;

      reach(adj, visited, v, y);

      if (visited[y - 1]) break;
    }
  }
}

int main() {
  uint16_t n, m;
  cin >> n >> m;
  unordered_map<uint16_t, unordered_set<uint16_t>> adj;
  vector<bool> visited(n, false);
  for (uint16_t i = 0; i < m; i++) {
    uint16_t x, y;
    cin >> x >> y;
    adj[x].insert(y);
    adj[y].insert(x);
  }
  uint16_t x, y;
  cin >> x >> y;
  
  reach(adj, visited, x, y);

  cout << visited[y-1];

  return 0;
}
