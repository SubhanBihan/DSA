#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

// We use 2*V nodes: 
// Variable x_i is mapped to 2*i
// Variable ~x_i is mapped to 2*i + 1
struct TwoSAT {
    int n;
    vector<vector<int>> adj;
    vector<int> disc, low, scc;
    vector<bool> onStack;
    stack<int> st;
    int timer, sccCount;

    TwoSAT(int variables) : n(variables) {
        adj.resize(2 * n + 2);
        disc.assign(2 * n + 2, -1);
        low.assign(2 * n + 2, -1);
        scc.assign(2 * n + 2, -1);
        onStack.assign(2 * n + 2, false);
        timer = 0;
        sccCount = 0;
    }

    // Helper to map literal to graph index
    // i > 0 -> 2*i, i < 0 -> 2*(-i) + 1
    int get_idx(int i) {
        if (i > 0) return 2 * i;
        return 2 * (-i) + 1;
    }

    int neg(int idx) {
        return idx ^ 1;
    }

    void add_clause(int i, int j) {
        int u = get_idx(i);
        int v = get_idx(j);
        // (u or v) is equivalent to (!u -> v) and (!v -> u)
        adj[neg(u)].push_back(v);
        adj[neg(v)].push_back(u);
    }

    void tarjan(int u) {
        disc[u] = low[u] = ++timer;
        st.push(u);
        onStack[u] = true;

        for (int v : adj[u]) {
            if (disc[v] == -1) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if (onStack[v]) {
                low[u] = min(low[u], disc[v]);
            }
        }

        if (low[u] == disc[u]) {
            while (true) {
                int v = st.top();
                st.pop();
                onStack[v] = false;
                scc[v] = sccCount;
                if (u == v) break;
            }
            sccCount++;
        }
    }

    bool solve() {
        for (int i = 2; i <= 2 * n + 1; ++i) {
            if (disc[i] == -1) tarjan(i);
        }

        vector<int> assignment(n + 1);
        for (int i = 1; i <= n; ++i) {
            if (scc[2 * i] == scc[2 * i + 1]) return false;
            // In Tarjan's, lower scc index means later in topological order
            // We assign true if scc[x] < scc[!x]
            assignment[i] = (scc[2 * i] < scc[2 * i + 1] ? i : -i);
        }

        cout << "SATISFIABLE" << endl;
        for (int i = 1; i <= n; ++i) {
            cout << assignment[i] << (i == n ? "" : " ");
        }
        cout << endl;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, C;
    if (!(cin >> V >> C)) return 0;

    TwoSAT solver(V);
    for (int k = 0; k < C; ++k) {
        int i, j;
        cin >> i >> j;
        solver.add_clause(i, j);
    }

    if (!solver.solve()) {
        cout << "UNSATISFIABLE" << endl;
    }

    return 0;
}