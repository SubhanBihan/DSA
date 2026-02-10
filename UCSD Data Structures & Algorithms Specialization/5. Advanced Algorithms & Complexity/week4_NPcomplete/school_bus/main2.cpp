#include <algorithm>
#include <cstdio>
#include <vector>
#include <iostream>
// #include <limits>

using namespace std;

const int INF = 1e9;
const int MAXN = 17;

int n, m;
int dist[MAXN][MAXN];
int dp[1 << MAXN][MAXN];
int parent[1 << MAXN][MAXN];

int main() {
    cin >> n >> m;
    
    // Initialize distance matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = (i == j) ? 0 : INF;
        }
    }
    
    // Read edges
    for (int i = 0; i < m; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        u--; v--;
        dist[u][v] = dist[v][u] = t;
    }
    
    // Check if solution exists (for n > 2, each node needs degree >= 2)
    if (n > 2) {
        for (int i = 0; i < n; i++) {
            int degree = 0;
            for (int j = 0; j < n; j++) {
                if (dist[i][j] != INF) degree++;
            }
            if (degree < 2) {
                printf("-1\n");
                return 0;
            }
        }
    }
    
    // DP with bitmask: dp[mask][i] = minimum cost to visit all nodes in mask, ending at i
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            dp[mask][i] = INF;
            parent[mask][i] = -1;
        }
    }
    
    // Start from node 0
    dp[1][0] = 0;
    
    // Fill DP table
    for (int mask = 1; mask < (1 << n); mask++) {
        for (int u = 0; u < n; u++) {
            if (dp[mask][u] == INF) continue;
            if (!(mask & (1 << u))) continue;
            
            for (int v = 0; v < n; v++) {
                if (mask & (1 << v)) continue;
                if (dist[u][v] == INF) continue;
                
                int new_mask = mask | (1 << v);
                int new_cost = dp[mask][u] + dist[u][v];
                
                if (new_cost < dp[new_mask][v]) {
                    dp[new_mask][v] = new_cost;
                    parent[new_mask][v] = u;
                }
            }
        }
    }
    
    // Find minimum cost to return to starting node
    int full_mask = (1 << n) - 1;
    int min_cost = INF;
    int last_node = -1;
    
    for (int i = 0; i < n; i++) {
        if (dist[i][0] != INF && dp[full_mask][i] + dist[i][0] < min_cost) {
            min_cost = dp[full_mask][i] + dist[i][0];
            last_node = i;
        }
    }
    
    if (min_cost == INF) {
        printf("-1\n");
        return 0;
    }
    
    // Reconstruct path
    vector<int> path;
    int mask = full_mask;
    int curr = last_node;
    
    while (curr != -1) {
        path.push_back(curr);
        int prev = parent[mask][curr];
        if (prev != -1) {
            mask ^= (1 << curr);
        }
        curr = prev;
    }
    
    reverse(path.begin(), path.end());
    
    printf("%d\n", min_cost);
    for (int node : path) {
        printf("%d ", node + 1);
    }
    printf("\n");
    
    return 0;
}