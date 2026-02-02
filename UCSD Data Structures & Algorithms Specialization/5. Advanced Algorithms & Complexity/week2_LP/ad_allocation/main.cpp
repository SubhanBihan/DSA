#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cstdio>

using namespace std;

const double EPS = 1e-9;

struct SimplexSolver {
    int n, m;
    vector<vector<double>> d;
    vector<int> basis;

    SimplexSolver(int n, int m) : n(n), m(m), d(n + 2, vector<double>(n + m + 2)), basis(n) {}

    void pivot(int r, int s) {
        for (int i = 0; i <= n + 1; ++i) {
            if (i != r && abs(d[i][s]) > EPS) {
                double factor = d[i][s] / d[r][s];
                for (int j = 0; j <= n + m + 1; ++j) d[i][j] -= d[r][j] * factor;
            }
        }
        double div = d[r][s];
        for (int j = 0; j <= n + m + 1; ++j) d[r][j] /= div;
        basis[r] = s;
    }

    int solve() {
        // Phase I: Find a feasible basis
        for (int i = 0; i < n; ++i) {
            basis[i] = m + i;
            if (d[i][n + m] < 0) {
                for (int j = 0; j <= n + m; ++j) d[i][j] *= -1;
                // Add artificial variable logic here for full robustness
            }
        }

        // Simplex iterations for Phase I and Phase II
        for (int phase = 1; phase <= 2; ++phase) {
            int target_row = (phase == 1) ? n + 1 : n;
            while (true) {
                int s = -1;
                for (int j = 0; j < m + n; ++j) {
                    if (d[target_row][j] < -EPS && (s == -1 || d[target_row][j] < d[target_row][s])) s = j;
                }
                if (s == -1) break;
                int r = -1;
                for (int i = 0; i < n; ++i) {
                    if (d[i][s] > EPS) {
                        if (r == -1 || d[i][n + m] / d[i][s] < d[r][n + m] / d[r][s]) r = i;
                    }
                }
                if (r == -1) return 2; // Infinity
                pivot(r, s);
            }
            if (phase == 1 && d[n + 1][n + m] > EPS) return 0; // No solution
        }
        return 1; // Bounded
    }
};

int main() {
    // For Testing
    string testfile;
    cin >> testfile;
    testfile = "tests/" + testfile;
    std::freopen(testfile.c_str(), "r", stdin);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    SimplexSolver solver(n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cin >> solver.d[i][j]; // A matrix [cite: 28]
    }
    for (int i = 0; i < n; ++i) {
        cin >> solver.d[i][n + m]; // b vector [cite: 52]
        solver.d[i][m + i] = 1.0; // Slack variables
    }
    for (int j = 0; j < m; ++j) {
        double c; cin >> c; // objective pleasure [cite: 28]
        solver.d[n][j] = -c; 
    }

    int result = solver.solve();
    if (result == 0) cout << "No solution" << endl; //[cite: 31]
    else if (result == 2) cout << "Infinity" << endl; //[cite: 1]
    else {
        cout << "Bounded solution" << endl;
        vector<double> x(m, 0);
        for (int i = 0; i < n; ++i) if (solver.basis[i] < m) x[solver.basis[i]] = solver.d[i][n + m];
        for (int i = 0; i < m; ++i) cout << fixed << setprecision(18) << x[i] << (i == m - 1 ? "" : " "); //[cite: 54]
        cout << endl;
    }
    return 0;
}