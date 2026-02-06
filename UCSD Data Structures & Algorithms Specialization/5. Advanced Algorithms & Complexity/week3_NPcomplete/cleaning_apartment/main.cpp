#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    if (!(cin >> n >> m)) return 0;

    // Use an adjacency matrix to quickly check if an edge exists
    vector<vector<bool>> adj(n + 1, vector<bool>(n + 1, false));
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u][v] = adj[v][u] = true;
    }

    vector<vector<int>> clauses;

    // ID
    auto id = [&](int i, int j) -> int {return (i - 1) * n + j;};

    // 1. Each vertex appears at least once in the path
    for (int i = 1; i <= n; ++i) {
        vector<int> clause;
        for (int j = 1; j <= n; ++j) clause.push_back(id(i, j));
        clauses.push_back(clause);
    }

    // 2. Each vertex appears at most once in the path
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = j + 1; k <= n; ++k) {
                clauses.push_back({-id(i, j), -id(i, k)});
            }
        }
    }

    // 3. Each position is occupied by at least one vertex
    for (int j = 1; j <= n; ++j) {
        vector<int> clause;
        for (int i = 1; i <= n; ++i) clause.push_back(id(i, j));
        clauses.push_back(clause);
    }

    // 4. Each position is occupied by at most one vertex
    for (int j = 1; j <= n; ++j) {
        for (int i = 1; i <= n; ++i) {
            for (int k = i + 1; k <= n; ++k) {
                clauses.push_back({-id(i, j), -id(k, j)});
            }
        }
    }

    // 5. Non-adjacent vertices cannot be adjacent in the path
    for (int k = 1; k < n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (i != j && !adj[i][j]) {
                    clauses.push_back({-id(i, k), -id(j, k + 1)});
                }
            }
        }
    }

    // Output results: Number of clauses and total number of variables (n*n)
    cout << clauses.size() << " " << n * n << endl;
    for (const auto& clause : clauses) {
        for (int literal : clause) {
            cout << literal << " ";
        }
        cout << 0 << endl; // Every clause line must end with 0
    }

    return EXIT_SUCCESS;
}