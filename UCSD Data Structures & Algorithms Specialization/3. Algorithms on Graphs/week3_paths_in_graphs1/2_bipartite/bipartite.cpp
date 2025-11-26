#include <iostream>
#include <vector>

using std::vector;

typedef enum {RED = -1, GRAY, BLUE} side_t;

template <typename T>
void dfs(vector<vector<T>>& adj, vector<side_t>& v_sides, T u, bool& is_bipartite) {
  // v_sides[u] = RED;

  for (auto nxt : adj[u]) {
    if (!is_bipartite) return; 

    if (v_sides[nxt] == GRAY) {
      v_sides[nxt] = static_cast<side_t>(-v_sides[u]);
      dfs(adj, v_sides, nxt, is_bipartite);
    }
    else if (v_sides[nxt] == v_sides[u]) {
      is_bipartite = false;
      return;
    }
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;

  vector<vector<int>> adj(n, vector<int>());
  vector<side_t> v_sides(n, GRAY);
  bool is_bipartite = true;

  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }

  for (int u = 0; u < n; u++) {
    if (v_sides[u] == GRAY) {
      v_sides[u] = RED;
      dfs(adj, v_sides, u, is_bipartite);
    }

    if (!is_bipartite) break;
  }

  std::cout << is_bipartite;

  return 0;
}
