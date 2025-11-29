// NOTE: Might have to make distance uint32 or long long, since even though individually < 10^8, total could exceed int bound

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using std::vector;
using std::pair;
using std::priority_queue;
using std::greater;

using llu = long long unsigned; 
const llu INF = std::numeric_limits<llu>::max();

// Dijkstra using adjacency list: adj[u] = vector of (v, weight).
int dijkstra(int src, int dest, const vector<vector<pair<int, llu>>>& adj) {
    int n = adj.size();
    vector<llu> dist(n, INF);

    // Min-heap priority queue storing (distance, node)
    priority_queue<pair<llu,int>,
                   vector<pair<llu,int>>,
                   greater<pair<llu,int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        if (u == dest) break;
        pq.pop();

        // If we popped a stale pair, skip it
        if (d != dist[u]) continue;

        for (auto [v, w] : adj[u]) {
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist[dest];
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<pair<int, llu>>> adj(n, vector<pair<int, llu>>());
  // vector<vector<int>> cost(n, vector<int>());

  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back({y - 1, w});
    // cost[x - 1].push_back(w);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;

  int d = dijkstra(s, t, adj);

  std::cout << ((d == INF) ? -1 : d);

  return EXIT_SUCCESS;
}
