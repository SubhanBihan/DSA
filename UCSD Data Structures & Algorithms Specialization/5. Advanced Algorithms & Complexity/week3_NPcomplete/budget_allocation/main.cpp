#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

#define MAX_VAR_PER_INEQ 3
using namespace std;

struct coeff {
    uint16_t ind;
    int16_t spend;
};

using clause = vector<int>;

int main() {
    uint16_t n, m;
    if (!(cin >> n >> m)) return 0;     // Here n = #inequalities (rows of A), m = #variables

    vector<vector<coeff>> A(n);
    vector<int> b(n);

    // Read only the non-zero coeffs of A
    for (auto& Row: A) {
        Row.reserve(MAX_VAR_PER_INEQ);

        for (uint16_t ind = 1; ind <= m; ind++) {
            int16_t spend;
            cin >> spend;
            if (spend != 0)
                Row.push_back({ind, spend});
        }
    }

    // Read b
    for (auto& el: b)
        cin >> el;


    // Clauses
    vector<clause> clauses;
    
    // Compute clauses
    for (uint16_t r = 0; r < n; r++) {
        auto& Row = A[r];

        if (Row.empty() && b[r] < 0) {     // Impossible to satisfy, immediately print an impossible SAT and exit
            printf("2 1\n");
            printf("1 0\n");
            printf("-1 0\n");

            return 0;
        }

        for (uint16_t p = 0; p < (1 << Row.size()); p++) {     // All possible combinations
            clause c;
            c.reserve(Row.size());
            int total_spend = 0;

            for (uint16_t i = 0; i < Row.size(); i++) {
                if ((p >> i) & 1) {     // This index is present in this combination
                    c.push_back(-Row[i].ind);
                    total_spend += Row[i].spend;
                }
                else {
                    c.push_back(Row[i].ind);
                }
            }

            if (total_spend > b[r])     // Not allowed, so becomes a constraint
                clauses.push_back(c);
        }
    }

    if (clauses.empty()) {          // No constraints, so output a satisfiable SAT and exit
        printf("1 1\n");
        printf("1 -1 0\n");

        return 0;
    }

    // Print number of clauses and variables
    printf("%zu %d\n", clauses.size(), m);

    // Print clauses
    for (const auto& c: clauses) {
        for (const auto& i: c) 
            printf("%d ", i);
        printf("0\n");
    }

    return EXIT_SUCCESS;
}