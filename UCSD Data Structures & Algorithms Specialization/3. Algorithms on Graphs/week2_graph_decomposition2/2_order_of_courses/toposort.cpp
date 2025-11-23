#include <iostream>
#include <vector>

using namespace std;

void dfs(int u, const vector<vector<int>>& adj, vector<bool>& visited, vector<int>& order) {
    visited[u] = true;

    for (int v : adj[u]) {
        if (!visited[v]) dfs(v, adj, visited, order);
    }

    order.push_back(u);   // post-order
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        adj[x-1].push_back(y-1);
    }

    vector<bool> visited(n, false);
    vector<int> order;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) dfs(i, adj, visited, order);
    }

    // reverse post-order
    for (int i = order.size() - 1; i >= 0; i--) {
        cout << order[i] + 1 << " ";
    }

    return 0;
}
