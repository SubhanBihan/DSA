#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs1(int u, const vector<vector<int>>& adj, vector<bool>& visited, vector<int>& order) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) dfs1(v, adj, visited, order);
    }
    order.push_back(u);    // finish time
}

void dfs2(int u, const vector<vector<int>>& adj_rev, vector<bool>& visited) {
    visited[u] = true;
    for (int v : adj_rev[u]) {
        if (!visited[v]) dfs2(v, adj_rev, visited);
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n), adj_rev(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u; 
        --v;
        adj[u].push_back(v);
        adj_rev[v].push_back(u);  // reverse graph
    }

    // Step 1: run DFS on original graph to get finishing order
    vector<bool> visited(n, false);
    vector<int> order;
    order.reserve(n);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) dfs1(i, adj, visited, order);
    }

    // Step 2: process nodes in reverse finish order on the reversed graph
    fill(visited.begin(), visited.end(), false);

    int scc = 0;

    for (int i = n - 1; i >= 0; i--) {
        int v = order[i];
        if (!visited[v]) {
            dfs2(v, adj_rev, visited);
            scc++;     // each DFS call = one SCC
        }
    }

    cout << scc << "\n";
    return 0;
}
