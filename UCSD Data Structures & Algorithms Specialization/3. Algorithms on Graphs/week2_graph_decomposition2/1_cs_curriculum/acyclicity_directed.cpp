#include <iostream>
#include <vector>

using std::vector;

bool dfs(int u, const vector<vector<int>>& adj, vector<int>& state) {
    state[u] = 1;   // GRAY: in recursion stack

    for (int v : adj[u]) {
        if (state[v] == 1) {
            // Found back edge → cycle
            return true;
        }
        if (state[v] == 0) {
            // WHITE → recurse
            if (dfs(v, adj, state)) return true;
        }
    }

    state[u] = 2;   // BLACK: done
    return false;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    vector<vector<int>> adj(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        // Convert 1-indexed to 0-indexed
        adj[u - 1].push_back(v - 1);
    }

    vector<int> state(n, 0);  // all WHITE

    for (int i = 0; i < n; i++) {
        if (state[i] == 0) {
            if (dfs(i, adj, state)) {
                std::cout << 1 << "\n";   // cycle exists
                return 0;
            }
        }
    }

    std::cout << 0 << "\n";   // no cycle
    return 0;
}
