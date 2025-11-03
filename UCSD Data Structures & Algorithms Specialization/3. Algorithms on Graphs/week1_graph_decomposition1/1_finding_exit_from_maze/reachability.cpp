#include <bitset>
#include <cstdint>
#include <iostream>
#include <vector>

#define MAX_VERTICES 1000

using namespace std;


bool reachable(const vector<vector<uint16_t>> &adj, uint16_t x, uint16_t y) {
    bitset<MAX_VERTICES + 1> visited;
    vector<uint16_t> stack;
    stack.push_back(x);
    visited[x] = true;

    while (!stack.empty()) {
        uint16_t u = stack.back();
        stack.pop_back();

        for (uint16_t v : adj[u]) {
            if (!visited[v]) {
                if (v == y) return true;
                visited[v] = true;
                stack.push_back(v);
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    uint16_t n, m;
    cin >> n >> m;
    vector<vector<uint16_t>> adj(n + 1);
    for (uint16_t i = 0; i < m; i++) {
        uint16_t a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    uint16_t x, y;
    cin >> x >> y;

    cout << reachable(adj, x, y);
}