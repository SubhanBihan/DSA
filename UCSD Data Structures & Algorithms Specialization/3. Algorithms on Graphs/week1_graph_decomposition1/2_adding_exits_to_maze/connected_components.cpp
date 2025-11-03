#include <bitset>
#include <cstdint>
#include <iostream>
#include <vector>

#define MAX_VERTICES 1000

using namespace std;

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

    bitset<MAX_VERTICES + 1> visited;
    uint16_t components = 0;
    vector<uint16_t> stack;

    for (uint16_t i = 1; i <= n; i++) {
        if (visited[i]) continue;

        // New component found
        components++;
        stack.clear();
        stack.push_back(i);
        visited[i] = true;

        // Iterative DFS
        while (!stack.empty()) {
            uint16_t u = stack.back();
            stack.pop_back();

            for (uint16_t v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    stack.push_back(v);
                }
            }
        }
    }

    cout << components;
    return 0;
}
