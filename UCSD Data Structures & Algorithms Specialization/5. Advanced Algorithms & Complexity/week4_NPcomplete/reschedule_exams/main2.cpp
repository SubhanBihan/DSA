#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

struct TwoSAT {
    int n;
    vector<vector<int>> adj;
    vector<int> disc, low, scc;
    vector<bool> onStack;
    stack<int> st;
    int timer, sccCount;

    TwoSAT(int variables) : n(variables) {
        adj.resize(2 * n);
        disc.assign(2 * n, -1);
        low.assign(2 * n, -1);
        scc.assign(2 * n, -1);
        onStack.assign(2 * n, false);
        timer = 0;
        sccCount = 0;
    }

    // x_i is true -> 2*i, x_i is false -> 2*i+1
    int get_true(int i) { return 2 * i; }
    int get_false(int i) { return 2 * i + 1; }
    int neg(int lit) { return lit ^ 1; }

    // Adds clause (L1 OR L2)
    void add_clause(int lit1, int lit2) {
        adj[neg(lit1)].push_back(lit2);
        adj[neg(lit2)].push_back(lit1);
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

    vector<int> solve() {
        for (int i = 0; i < 2 * n; ++i) 
            if (disc[i] == -1) tarjan(i);

        vector<int> assignment(n);
        for (int i = 0; i < n; ++i) {
            if (scc[get_true(i)] == scc[get_false(i)]) return {}; 
            // In Tarjan's, smaller SCC index means topologically later.
            // We pick the literal that is topologically later.
            assignment[i] = (scc[get_true(i)] < scc[get_false(i)]);
        }
        return assignment;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    string s; cin >> s;

    auto c_to_i = [](char c) { return (c == 'R' ? 0 : (c == 'G' ? 1 : 2)); };
    auto i_to_c = [](int i) { return (i == 0 ? 'R' : (i == 1 ? 'G' : 'B')); };

    // options[student_id][option_index (0 or 1)]
    vector<vector<int>> options(n, vector<int>(2));
    for (int i = 0; i < n; i++) {
        int forbidden = c_to_i(s[i]);
        int idx = 0;
        for (int c = 0; c < 3; c++) {
            if (c != forbidden) options[i][idx++] = c;
        }
    }

    TwoSAT solver(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        if (u == v) { 
            // A student cannot be friends with themselves and have different dates
            cout << "Impossible" << endl; return 0; 
        }

        for (int ou = 0; ou < 2; ou++) {
            for (int ov = 0; ov < 2; ov++) {
                if (options[u][ou] == options[v][ov]) {
                    // Conflict: NOT (u picks ou AND v picks ov)
                    // Equivalent to: (NOT u_ou OR NOT v_ov)
                    int lit_u = (ou == 0) ? solver.get_true(u) : solver.get_false(u);
                    int lit_v = (ov == 0) ? solver.get_true(v) : solver.get_false(v);
                    solver.add_clause(solver.neg(lit_u), solver.neg(lit_v));
                }
            }
        }
    }

    vector<int> res = solver.solve();
    if (res.empty()) cout << "Impossible" << endl;
    else {
        for (int i = 0; i < n; i++) 
            cout << i_to_c(options[i][res[i] ? 0 : 1]);
        cout << endl;
    }

    return 0;
}