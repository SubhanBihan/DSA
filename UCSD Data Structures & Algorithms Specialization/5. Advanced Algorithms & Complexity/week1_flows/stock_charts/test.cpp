#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <algorithm>
#include <fstream>

using namespace std;

using Price = uint32_t;
using Node = int16_t;            // Each stock is treated as a node

using Stock = vector<Price>;
using Dataset = vector<Stock>;

#define MAXSTOCKS 100

void Debug() {
    static int i = 1;
    cout << "Reached " << i++ << endl;
}

bool IsAbove(const Stock& s2, const Stock& s1) {
    for (auto i = 0; i < s2.size(); i++) {
        if (s1[i] >= s2[i]) return false;
    }

    return true;
}

Node Solve(istream& in) {
    Node n, k;
    in >> n >> k;

    Dataset stocks(n, Stock(k));

    for (auto& stock: stocks) 
        for (auto& price: stock)
            in >> price;
    
    // Debug();  // 1

    sort(stocks.begin(), stocks.end(), [](const Stock& s1, const Stock& s2){return s1.front() < s2.front();});

    // Debug();  // 2

    vector<Node> leaf(n, -1);
    vector<Node> parent(n, -1);

    for (Node curr = 1; curr < n; curr++) {
        Node lf = -1;

        for (Node prev = curr - 1; prev >= 0; prev--) {
            if (IsAbove(stocks[curr], stocks[prev])) {
                if (parent[prev] == -1) {
                    leaf[curr] = lf = prev;
                    break;
                }

                if (leaf[curr] == -1)
                    leaf[curr] = lf = prev; 
            }
        }

        if (lf != -1) parent[lf] = curr;
    }

    // Debug();  // 3

    Node stock_count = 0, chart_count = 0;
    bitset<MAXSTOCKS> visited;

    // Debug();  // 4

    for (Node curr = n - 1; curr >= 0 && stock_count != n; curr--) {
        Node v = curr;
        
        for ( ; v != -1; v = leaf[v]) {
            if (!visited[v]) {
                visited.set(v);
                stock_count++;
            }
            else {
                if (v != curr) chart_count++;       // Only increment chart count if we were indeed on a unique branch
                break;
            }
        }

        if (v == -1) chart_count++;
    }

    // Debug();  // 5

    // cout << chart_count << endl;

    return chart_count;
}

/* ====== TEST RUNNER ====== */

bool run_tests(const string& test_dir) {
    ifstream manifest(test_dir + "/tests.txt");
    if (!manifest) {
        cerr << "Could not open tests.txt\n";
        return false;
    }

    string fname;
    while (manifest >> fname) {
        ifstream test_file(test_dir + "/" + fname);
        ifstream ans_file (test_dir + "/" + fname + ".a");

        if (!test_file || !ans_file) {
            cerr << "Missing files for test " << fname << "\n";
            return false;
        }

        Node expected;
        ans_file >> expected;

        Node got = Solve(test_file);

        if (got != expected) {
            cout << "\033[31m"
                      << "Test " << fname << " Failed!\n"
                      << "Expected: " << expected << "\n"
                      << "Got:      " << got << "\n"
                      << "\033[0m";
            // return false;
        }
        else {
            cout << "\033[32m"
                      << "Test " << fname << " Passed!\033[0m\n";
        }
    }

    // cout << "\033[32mAll Tests Passed!\033[0m\n";
    return true;
}

// int main(int argc, char** argv) {
//     if (argc == 2 && string(argv[1]) == "--test") {
//         run_tests("tests");
//         return EXIT_SUCCESS;
//     }

//     // Normal CLI mode
//     cout << Solve(cin) << "\n";
//     return EXIT_SUCCESS;
// }

int main() {
    run_tests("tests");
    return EXIT_SUCCESS;
}