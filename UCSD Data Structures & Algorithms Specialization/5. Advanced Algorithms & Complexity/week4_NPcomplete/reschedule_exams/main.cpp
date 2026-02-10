// 3-recoloring -> 2-SAT
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>


using namespace std;

/**
 * 2-SAT solver using Tarjan's Algorithm.
 * Handles clauses with 1 or 2 literals.
 */
struct TwoSAT {
  int n;
  vector<vector<int>> adj;
  vector<int> disc, low, scc;
  vector<bool> onStack;
  stack<int> st;
  int timer, sccCount;

  TwoSAT(int variables) : n(variables) {
    // 2*n to accommodate bitwise negation trick
    adj.resize(2 * n);
    disc.assign(2 * n, -1);
    low.assign(2 * n, -1);
    scc.assign(2 * n, -1);
    onStack.assign(2 * n, false);
    timer = 0;
    sccCount = 0;
  }

  // Maps literal i to node index: i > 0 -> 2*i, i < 0 -> 2*|i| + 1
  inline int get_idx(int i) { return (i > 0) ? (2 * i) : (2 * (-i) + 1); }

  // Returns the index of the negated literal using bitwise XOR
  inline int neg(int idx) { return idx ^ 1; }

  // Adds a clause (i OR j). If i == j, it represents a 1-literal clause.
  void add_clause(int i, int j) {
    int u = get_idx(i);
    int v = get_idx(j);
    // Implication: !u -> v AND !v -> u
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
        if (u == v)
          break;
      }
      sccCount++;
    }
  }

  void solve() {
    for (int i = 0; i < 2 * n; ++i) {
      if (disc[i] == -1)
        tarjan(i);
    }

    for (int i = 0; i < n; ++i) {
      if (scc[2 * i] == scc[2 * i + 1]) {
        cout << "Impossible" << endl;
        return;
      }

      auto color = [](int cnum) -> char {
        return (cnum == 0) ? 'R' : (cnum == 1) ? 'G' : 'B';
      };

      // Tarjan's finds SCCs in reverse topological order.
      // Assigning the literal with the smaller SCC index results in a valid SAT
      // assignment.
      if (scc[2 * i] < scc[2 * i + 1])
        cout << color(i % 3);
    }

    cout << endl;
  }
};

int main() {
  // Fast I/O for large constraints
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  if (!(cin >> n >> m))
    return 0;

  TwoSAT solver(3 * n);

  auto cnum = [](char color) -> int {
    return color == 'R' ? 0 : color == 'G' ? 1 : 2; // R = 0, G = 1, B = 2
  };

  auto id = [](int ind, int cnum) -> int { return 3 * ind + cnum; };

  string assignment;
  cin >> assignment;

  bool impossible = false;

  for (int i = 0; i < m; i++) { // Reading in edges and making clauses
    int u, v;
    cin >> u >> v;

    if (u == v) { // Self-loop immediately makes the problem impossible
      impossible = true;
    } else {
      u--, v--;
      for (int cnum = 0; cnum < 3; cnum++) {
        solver.add_clause(
            -id(u, cnum),
            -id(v, cnum)); // The two nodes can't have the same color
      }
    }
  }

  if (impossible) {
    cout << "Impossible" << endl;
    return 0;
  }

  for (int ind = 0; ind < n; ind++) {
    int Cnum = cnum(assignment[ind]);
    int Id0 = id(ind, Cnum);
    int Id1 = id(ind, (Cnum + 1) % 3), Id2 = id(ind, (Cnum + 2) % 3);

    solver.add_clause(-Id0, -Id0); // Node can't take the pre-assigned color

    solver.add_clause(Id1,
                      Id2); // Node must take exactly one of the other 2 colors
    solver.add_clause(-Id1, -Id2);
  }

  solver.solve();

  return 0;
}