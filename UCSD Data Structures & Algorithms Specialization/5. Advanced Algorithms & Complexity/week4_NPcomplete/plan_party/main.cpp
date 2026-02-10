#include <iostream>
#include <vector>

using namespace std;

struct Node {
    unsigned weight;
    unsigned D;
};

struct Frame {
    unsigned node, next_child;
};

using AdjList = vector<vector<unsigned>>;
using Tree = vector<Node>;

auto DFS(const AdjList& adj, Tree& tree) {
    const unsigned n = tree.size();

    vector<bool> visited(n, false);
    vector<Frame> stack;
    stack.reserve(n);

    const unsigned root = 0;
    stack.push_back({root, 0});
    visited[root] = true;

    while (!stack.empty()) {
        auto& top = stack.back();
        auto u = top.node;

        if (top.next_child < adj[u].size()) {
            auto v = adj[u][top.next_child++];

            if (!visited[v]) {
                visited[v] = true;
                stack.push_back({v, 0});
            }
        }
        else {
            unsigned m0 = tree[u].weight, m1 = 0;
            for (const auto& v: adj[u]) {
                if (tree[v].D != 0) {       // Exclude u's parent
                    m1 += tree[v].D;

                    for (const auto& w: adj[v])     // We could exclude u here, but tree[u].D = 0 at this point
                        m0 += tree[w].D;
                }
            }

            tree[u].D = max(m0, m1);
            stack.pop_back();
        }
    }

    return tree[root].D;
}

int main() {
    int n;
    cin >> n;

    AdjList adj(n);
    Tree tree(n);

    for (int i = 0; i < n; i++){
        cin >> tree[i].weight;
        tree[i].D = 0;
    }

    for (int i = 0; i < n - 1; i++) {
        unsigned u, v;
        cin >> u >> v;

        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    cout << DFS(adj, tree) << endl;

    return 0;
}
