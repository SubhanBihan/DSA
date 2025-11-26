#include <limits>
#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

template <typename T>
int distance(vector<vector<T>> &adj, T s, T t) {
  T v;
  queue<T> v_queue;
  vector<T> v_dist(adj.size(), std::numeric_limits<T>::max());

  v_queue.push(s);
  v_dist[s] = 0;

  while (!v_queue.empty()) {
    v = v_queue.front();
    v_queue.pop();

    for (auto w : adj[v]) {
      if (w == t) return v_dist[v] + 1;

      if (v_dist[w] == std::numeric_limits<T>::max()) {
        v_queue.push(w);
        v_dist[w] = v_dist[v] + 1;
      }
    }
  }

  return -1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int>> adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
