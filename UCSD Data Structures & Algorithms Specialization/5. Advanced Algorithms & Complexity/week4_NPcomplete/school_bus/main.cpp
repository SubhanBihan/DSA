#include <algorithm>
#include <bitset>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <vector>
#include <limits>
#include <utility>

using namespace std;

#define MAX_NODES 17
const unsigned MAX_LENGTH = numeric_limits<unsigned>::max();
using Edges = vector<unsigned>;
using Graph = vector<Edges>;     // Adjacency list with edge weights

struct Frame {
    uint16_t node, next_child;
};

auto DFS(const Graph& G, const unsigned& minedge_root) {
    const uint16_t n = G.size();

    unsigned cycleL = MAX_LENGTH, pathL = 0;
    bitset<MAX_NODES> visited(false);
    vector<Frame> stack;    stack.reserve(n);
    vector<uint16_t> path;  path.reserve(n);
    vector<uint16_t> opt_path;

    const unsigned root = 0;
    stack.push_back({root, root + 1});
    path.push_back(root);
    visited[root] = true;

    

    while (!stack.empty()) {
        auto& top = stack.back();
        const auto& u = top.node;
        auto& v = top.next_child;

        if (v < n) {
            const auto& w = G[u][v];

            if (!visited[v] && w > 0 && pathL + w < cycleL - minedge_root) {
                visited[v] = true;
                stack.push_back({v, root + 1});
                path.push_back(v);
                pathL += w;
            }

            v++;
        }
        else {
            if (path.size() == n && G[u][root] > 0 && pathL + G[u][root] < cycleL) {  // Covered all nodes, and more optimal return path exists
                cycleL =  pathL + G[u][root];
                opt_path = path;
            }

            if (path.size() > 1)
                pathL -= G[path[path.size() - 2]][path.back()];     // Remove length of previous edge
            
            visited[u] = false;
            stack.pop_back();
            path.pop_back();
        }
    }

    return make_pair(cycleL, opt_path);
}

int main () {
    uint16_t n, m;
    cin >> n >> m;

    Graph G(n, Edges(n, 0));
    vector<uint16_t> edge_count(n, 0);
    unsigned minedge_root = MAX_LENGTH;

    for (uint16_t i = 0; i < m; i++) {
        unsigned u, v, t;
        cin >> u >> v >> t;
        u--, v--;
        
        G[u][v] = G[v][u] = t;
        edge_count[u]++, edge_count[v]++;

        if (u * v == 0 && t < minedge_root)
            minedge_root = t;
    }

    if (n > 2 && *min_element(edge_count.begin(), edge_count.end()) <= 1) {
        printf("-1\n");
        return 0;
    }

    auto result = DFS(G, minedge_root);
    auto& cycleL = result.first;
    auto& opt_path = result.second;

    if (opt_path.empty()) {
        printf("-1\n");
    }
    else {
        printf("%d\n", cycleL);
        for (const auto& x: opt_path)
            printf("%d ", x + 1);
        printf("\n");
    }

    return 0;
}