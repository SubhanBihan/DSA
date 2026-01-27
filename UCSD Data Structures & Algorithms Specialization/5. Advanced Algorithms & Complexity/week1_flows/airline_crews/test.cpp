#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <bitset>

#define NUMNODES 202        // Highest possible number of nodes
using namespace std;

using Node = int16_t;

using Row   = bitset<NUMNODES>;
using Graph = vector<Row>;

void AddFlow(Graph& Gf, const Node u, const Node v) {
    Gf[u].reset(v);
    Gf[v].set(u);
}

auto BFS(const Graph& G, const Node total_nodes, const Node src) {
    const Node sink = total_nodes + 1;
    const Node n = G.size();

    vector<bool> visited(n, false);
    vector<Node> parent(n, -1);

    queue<Node> q;

    visited[src] = true;
    q.push(src);

    while (!q.empty()) {
        Node u = q.front();
        q.pop();

        // Node v;
        for (Node v = 0; v < n; v++) {
            if (G[u][v] && !visited[v]) {
                visited[v] = true;
                parent[v] = u;

                if (v == sink)                                  // Found sink - path completed
                    return parent;
                
                q.push(v);
            }
        }
    }

    return vector<Node>(0);
}

auto EdmondsKarp(Graph& Gf, const Node flights, const Node crews) {
    const Node max_flow = min(flights, crews);
    const Node total_nodes = flights + crews;
    const Node sink = total_nodes + 1;

    Node f;                             // Actually the flow

    for (f = 0; f < max_flow; f++) {
        auto parent = BFS(Gf, total_nodes, 0);

        if (parent.empty()) break;      // No path from source to sink, stop here

        // Re-computing Gf (changing only the necessary edges)
        for (Node v = sink; parent[v] != -1; v = parent[v]) {
            AddFlow(Gf, parent[v], v);
        }

        // printf("Flow = %d\n", f);
    }

    // printf("Flow = %d\n", f);


    vector<Node> pairings(flights, -1);
    Node pairs = f;

    for (Node crew = 1; crew <= crews && pairs != 0; crew++) {
        for (Node flight = 1; flight <= flights; flight++) {
            if (Gf[flights + crew].test(flight)) {      // Checking for reverse (occupied) paths
                pairings[flight - 1] = crew;
                pairs--;
                break;
            }
        }
    }

    return make_pair(f, pairings);
}

int main() {
    Node flights, crews;      // # of flights and crew resp.
    cin >> flights >> crews;

    const Node total_nodes = flights + crews;                         // First node is source, last node is sink
    Graph Gf(total_nodes + 2);

    const Node sink = total_nodes + 1;

    for (Node i = 1; i <= flights; i++)                             // All flights connected to source
        Gf[0].set(i);

    for (Node j = flights + 1; j <= total_nodes; j++)
        Gf[j].set(sink); 

    for (Node i = 1; i <= flights; i++) {
        for (Node j = flights + 1; j <= total_nodes; j++) {
            int c;
            cin >> c;
            
            if (c != 0)
                Gf[i].set(j);
        }
    }

    auto result = EdmondsKarp(Gf, flights, crews);

    auto& pairs = result.first;
    auto& pairings = result.second;

    // printf("Total pairs = %d\n", pairs);

    for (const auto& crew: pairings)
        printf("%d ", crew);
    printf("\n");

    return EXIT_SUCCESS;
}