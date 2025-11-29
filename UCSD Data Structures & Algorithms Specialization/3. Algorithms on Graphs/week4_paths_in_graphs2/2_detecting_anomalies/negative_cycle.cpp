#include <iostream>
#include <vector>
// #include <queue>
#include <limits>

using std::vector;
using std::pair;
// using std::priority_queue;
// using std::greater;

using ll = long long; 
const ll INF = std::numeric_limits<ll>::max();

// Bellman-Ford using adjacency list: adj[u] = vector of (v, weight).
bool bellford(const vector<vector<pair<int, ll>>>& adj) {
  int n = adj.size();
  // vector<ll> dist(n + 1, INF);      // (n + 1)th node is super-source - has weight 0 edge with every other node
  // adj.push_back(vector<pair<int, ll>>());
  // for (int i = 0; i < n; i++)
  //   adj[n].push_back({i, 0});

  // dist[n] = 0;

  vector<ll> dist(n, 0);                      // Same effect as adding a super source

  // for (int i = 0; i <= n; i++) {
  //   for (int u = n; u >= 0; u--) {          // Go through all edges and try to relax them
  for (int i = 0; i < n; i++) {
    for (int u = 0; u < n; u++) {                        // Go through all edges and try to relax them
      // if (dist[u] == INF) continue;                   // Prevents +ve overflow - not needed here since initial dist are all 0

      for (auto [v, w] : adj[u]) {
          if (dist[v] > dist[u] + w) {
              // if (i == n) return true;          // Negative weight cycle exists
              if (i == n - 1) return true;          // Negative weight cycle exists
              dist[v] = dist[u] + w;
          }
      }
    }
  }

  return false;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<pair<int, ll>>> adj(n, vector<pair<int, ll>>());
  // vector<vector<int>> cost(n, vector<int>());

  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back({y - 1, w});
    // cost[x - 1].push_back(w);
  }

  std::cout << bellford(adj);

  return EXIT_SUCCESS;
}