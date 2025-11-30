#include <iostream>
#include <vector>
#include <queue>
#include <limits>
// #include <algorithm>

using std::vector;
using std::pair;
// using std::priority_queue;
// using std::greater;

using ll = long long; 
const ll PLUS_INF = std::numeric_limits<ll>::max();
const ll MINUS_INF = std::numeric_limits<ll>::min();

// Bellman-Ford using adjacency list: adj[u] = vector of (v, weight).
void bellford(int src, vector<vector<pair<int, ll>>>& adj, vector<ll>& dist) {
  int n = adj.size();
  vector<bool> in_negcyc(n, false);

  dist[src] = 0;

  for (int i = 0; i < n; i++) {
    for (int u = 0; u < n; u++) {                          // Go through all edges and try to relax them
      if (dist[u] == PLUS_INF) continue;                   // Prevents +ve overflow

      for (auto [v, w] : adj[u]) {
          if (dist[v] > dist[u] + w) {
              if (i == n - 1) in_negcyc[v] = true;         // Node inside a negative weight cycle - this does NOT find all such nodes
              dist[v] = dist[u] + w;
          }
      }
    }
  }

  // BFS/DFS propagation from negative-cycle nodes
  // std::vector<bool> visited(n, false);
  std::queue<int> q;

  for (int v = 0; v < n; v++) {
      if (in_negcyc[v]) {
          q.push(v);
          // visited[v] = true;
      }
  }

  while (!q.empty()) {
      int u = q.front();  
      q.pop();
      for (auto [v, w] : adj[u]) {
          if (!in_negcyc[v]) {
              in_negcyc[v] = true;
              q.push(v);
          }
      }
  }

  // Mark all reachable nodes as -∞
  for (int v = 0; v < n; v++) {
      if (in_negcyc[v]) dist[v] = MINUS_INF;
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<pair<int, ll>>> adj(n, vector<pair<int, ll>>());
  vector<ll> dist(n, PLUS_INF);

  // vector<vector<int>> cost(n, vector<int>());

  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back({y - 1, w});
    // cost[x - 1].push_back(w);
  }
  int s;
  std::cin >> s;
  s--;

  bellford(s, adj, dist);

  for (auto d : dist)
    // std::cout << ((d == MINUS_INF) ? "-\n" : (d == PLUS_INF) ? "*\n" : d);
    if (d == MINUS_INF) std::cout << "-\n";
    else if (d == PLUS_INF) std::cout << "*\n";
    else std::cout << d << "\n";

  return EXIT_SUCCESS;
}