#include <bitset>
#include <cstdint>
#include <iostream>
#include <vector>

#define MAX_VERTICES 1000

using namespace std;

using Node = uint16_t;
using AdjList = vector<vector<uint16_t>>;

bool reachable(const AdjList& adj, Node x, Node y) {
    bitset<MAX_VERTICES + 1> visited;
    vector<Node> stack;
    stack.push_back(x);
    visited[x] = true;

    while (!stack.empty()) {
        auto u = stack.back();
        stack.pop_back();

        for (auto v : adj[u]) {
            if (!visited[v]) {
                if (v == y) return true;
                visited[v] = true;
                stack.push_back(v);
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Node n, m;
    cin >> n >> m;
    AdjList adj(n + 1);
    for (Node i = 0; i < m; i++) {
        Node a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    Node x, y;
    cin >> x >> y;

    cout << reachable(adj, x, y);
}