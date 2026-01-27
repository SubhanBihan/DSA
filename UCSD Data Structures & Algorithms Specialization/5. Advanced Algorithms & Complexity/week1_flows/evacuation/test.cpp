#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <limits>

using namespace std;

using Node = int16_t;
using Capacity = uint32_t;

using Graph = vector<unordered_map<Node, Capacity>>;

struct Edge {
    Node u, v;
    Capacity c;
};

void AddEdge(Graph& G, const Edge& e) {
    // 1) Check reverse edge (v -> u)
    auto& rev_map = G[e.v];
    auto it_rev = rev_map.find(e.u);

    if (it_rev != rev_map.end()) {
        Capacity& x = it_rev->second;

        if (x >= e.c) {
            // x -= c
            x -= e.c;
            if (x == 0) {
                rev_map.erase(it_rev);  // optional cleanup
            }
        } else {
            // remove reverse edge, insert forward remainder
            Capacity rem = e.c - x;
            rev_map.erase(it_rev);
            G[e.u][e.v] += rem;   // safe: either inserts or adds
        }
        return;
    }

    // 2) No reverse edge, check forward edge (u -> v)
    auto res = G[e.u].emplace(e.v, e.c);
    if (!res.second) {
        res.first->second += e.c;
    }
}

void AddFlow(Graph& Gf, Node u, Node v, Capacity flow) {
    // Change capacity (remaining) of current edge (u -> v)
    auto& Map = Gf[u];
    auto it = Map.find(v);        // We know this exists
    auto& c = it->second;

    if (c > flow)
        c -= flow;
    else
        Map.erase(it);

    // Change capacity of reverse edge (v -> u)
    auto res = Gf[v].emplace(u, flow);
    if (!res.second) {
        res.first->second += flow;
    }
}

// Returns the minimum edge and corresponding (complete) path - if it exists
pair<Capacity, vector<Node>> BFS(const Graph& G, Node src) {
    Node n = G.size();

    vector<bool> visited(n, false);
    vector<Node> parent(n, -1);
	vector<Capacity> min_edge(n);		

    queue<Node> q;

    visited[src] = true;
	min_edge[src] = std::numeric_limits<Capacity>::max();
    q.push(src);

    while (!q.empty()) {
        Node u = q.front();
        q.pop();

        for (const auto& e : G[u]) {
            auto& v = e.first;
            auto& c = e.second;
            
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;

				min_edge[v] = std::min(min_edge[u], c);
                q.push(v);

                // cout << min_edge[v] << endl;

                if (v == n - 1)                                  // Found sink - path completed
                    return make_pair(min_edge[v], parent);
            }
        }
    }

    return make_pair(0, vector<Node>(0));   // No complete path
}

auto EdmondsKarp(Graph& Gf, Capacity max_flow) {
    Node n = Gf.size();
    Capacity f = 0;     // Actually the flow

    while (f < max_flow) {
        auto path = BFS(Gf, 0);

        auto g = path.first;
        if (g == 0) break;      // No path from source to sink

        // Re-computing Gf (changing only the necessary edges)
        auto parent = std::move(path.second);
        for (Node v = n - 1; parent[v] != -1; v = parent[v]) {
            AddFlow(Gf, parent[v], v, g);
        }

        // Update the max flow
        f += g;
    }

    return f;
}

Capacity solve(istream& in) {
    Node n, m;
    in >> n >> m;

    Graph Gf(n);
    Capacity total_in = 0, total_out = 0;

    for (int i = 0; i < m; i++) {
        Edge e;
        in >> e.u >> e.v >> e.c;
        e.u--, e.v--;

        if (e.u == e.v || e.u == n - 1 || e.v == 0) continue;   // Self-loops, inflows to source, outflows from sink are irrelevant

        if (e.u == 0)     total_in  += e.c;
        if (e.v == n - 1) total_out += e.c;

        // cout << e.u << " " << e.v << " " << e.c << endl;

        AddEdge(Gf, e);
    }

    Capacity max_flow = min(total_in, total_out);

    // cout << max_flow << endl;

    return EdmondsKarp(Gf, max_flow);
}

/* ====== TEST RUNNER ====== */

bool run_tests(const std::string& test_dir) {
    std::ifstream manifest(test_dir + "/tests.txt");
    if (!manifest) {
        std::cerr << "Could not open tests.txt\n";
        return false;
    }

    std::string fname;
    while (manifest >> fname) {
        std::ifstream test_file(test_dir + "/" + fname);
        std::ifstream ans_file (test_dir + "/" + fname + ".a");

        if (!test_file || !ans_file) {
            std::cerr << "Missing files for test " << fname << "\n";
            return false;
        }

        Capacity expected;
        ans_file >> expected;

        Capacity got = solve(test_file);

        if (got != expected) {
            std::cout << "\033[31m"
                      << "Test " << fname << " Failed!\n"
                      << "Expected: " << expected << "\n"
                      << "Got:      " << got << "\n"
                      << "\033[0m";
            return false;
        }
        else {
            std::cout << "\033[32m"
                      << "Test " << fname << " Passed!\033[0m\n";
        }
    }

    std::cout << "\033[32mAll Tests Passed!\033[0m\n";
    return true;
}

int main(int argc, char** argv) {
    if (argc == 2 && string(argv[1]) == "--test") {
        run_tests("tests");
        return EXIT_SUCCESS;
    }

    // Normal CLI mode
    cout << solve(cin) << "\n";
    return EXIT_SUCCESS;
}