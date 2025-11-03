#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>

using namespace std;


int reach(vector<vector<int>> &adj, int x, int y) {
  //write your code here
  return 0;
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
  
}
