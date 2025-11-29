// #include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <utility>
#include <vector>
#include <cmath>
// #include <limits>
#include <queue>
#include <bitset>

#define MAX_POINTS 200

using namespace std;
// const auto INF = numeric_limits<double>::max();

struct Point {int x, y;};

double euclid_dist(const Point& P1, const Point& P2) {
  return sqrt((P1.x - P2.x) * (P1.x - P2.x) + (P1.y - P2.y) * (P1.y - P2.y));
}

double Prim(const vector<vector<pair<double, uint8_t>>>& adj) {
  uint8_t n = adj.size();
  double d = 0, mst_cost = 0;
  uint8_t v = 0;      // Starting vertex
  bitset<MAX_POINTS> InTree(0);
  // InTree.set(u);
  
  // Min-heap priority queue storing (distance, node)
  priority_queue<pair<double, uint8_t>,
                  vector<pair<double, uint8_t>>,
                  greater<pair<double, uint8_t>>> pq;

  // for (auto p :  adj[u])
  //   if (!InTree[p.second])
  //     pq.push(p);

  while (InTree.count() < n) {
    if (!pq.empty()) {
      tie(d, v) = pq.top();
      pq.pop();
    }

    if (!InTree[v]) {
      InTree.set(v);
      mst_cost += d;

      for (auto p :  adj[v])
        if (!InTree[p.second])
          pq.push(p);
    }
  }
  return mst_cost;
} 

int main() {
  size_t n;
  cin >> n;
  vector<Point> P(n);
  vector<vector<pair<double, uint8_t>>> adj(
    n,
    vector<pair<double, uint8_t>>(n)
  );

  for (size_t i = 0; i < n; i++) {
    cin >> P[i].x >> P[i].y;
  }

  for (uint8_t i = 0; i < n; i++)
    for (uint8_t j = 0; j < i; j++) {
      adj[i][j].first = adj[j][i].first = euclid_dist(P[i], P[j]);
      adj[i][j].second = j;
      adj[j][i].second = i;
    }

  cout << setprecision(10) << Prim(adj) << endl;

  return EXIT_SUCCESS;
}
