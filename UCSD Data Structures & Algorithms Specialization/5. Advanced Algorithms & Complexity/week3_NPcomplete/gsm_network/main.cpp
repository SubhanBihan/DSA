#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> edges(m);

    for (auto& e: edges) {
        cin >> e.first >> e.second;
    }

    // For each vertex i (1-based) and color j (from 1 to 3), the variable index is 3(i-1) + j
    auto ind = [](int i, int j) -> int {
        return 3 * (i - 1) + j;
    };

    // Numbers of clauses and variables
    int V = 3 * n, C = 4 * n + 3 * m;
    printf("%d %d\n", C, V);

    // Each vertex must have exactly 1 color
    for (int i = 1; i <= n; i++) {
        auto v1 = ind(i, 1), v2 = ind(i, 2), v3 = ind(i, 3);
        printf("%d %d %d 0\n", v1, v2, v3);
        printf("-%d -%d 0\n", v1, v2);
        printf("-%d -%d 0\n", v1, v3);
        printf("-%d -%d 0\n", v2, v3);
    }

    // Vertices/ends of each edge must have different colors
    for (const auto& e: edges) {
        for (int j = 1; j <= 3; j++) {
            printf("-%d -%d 0\n", ind(e.first, j), ind(e.second, j));
        }
    }
    
    return EXIT_SUCCESS;
}