#include <iostream>
#include <vector>

using namespace std;

// Standard Bipartite Matching using DFS
bool dfs(int u, const vector<vector<int>>& adj, vector<int>& match, vector<bool>& vis) {
    for (int v : adj[u]) {
        if (!vis[v]) {
            vis[v] = true;
            if (match[v] < 0 || dfs(match[v], adj, match, vis)) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<vector<int>> prices(n, vector<int>(k));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            cin >> prices[i][j];
        }
    }

    // Build the adjacency list for the bipartite graph
    // Left side: stock i, Right side: stock j
    // Edge exists if stock i strictly dominates stock j
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            
            bool strictly_greater = true;
            for (int t = 0; t < k; ++t) {
                if (prices[i][t] <= prices[j][t]) {
                    strictly_greater = false;
                    break;
                }
            }
            
            if (strictly_greater) {
                adj[i].push_back(j);
            }
        }
    }

    // Solve for Maximum Bipartite Matching
    int matching_size = 0;
    vector<int> match(n, -1);
    for (int i = 0; i < n; ++i) {
        vector<bool> vis(n, false);
        if (dfs(i, adj, match, vis)) {
            matching_size++;
        }
    }

    // Result is total nodes - maximum matching
    cout << n - matching_size << endl;

    return 0;
}