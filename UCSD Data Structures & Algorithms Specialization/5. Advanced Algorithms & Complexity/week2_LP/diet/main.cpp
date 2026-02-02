#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

const double EPS = 1e-9;
const double INF_VAL = 1e9;

typedef vector<double> Column;
typedef vector<Column> Matrix;

// Gaussian elimination to solve Ax = b
int SolveLinearEquations(Matrix A, Column b, Column& x) {
    int n = A.size();
    for (int i = 0; i < n; ++i) {
        int pivot = i;
        for (int j = i + 1; j < n; ++j)
            if (abs(A[j][i]) > abs(A[pivot][i])) pivot = j;
        swap(A[i], A[pivot]);
        swap(b[i], b[pivot]);

        if (abs(A[i][i]) < EPS) return 0; // Singular matrix

        for (int j = i + 1; j < n; ++j) {
            double factor = A[j][i] / A[i][i];
            for (int k = i; k < n; ++k) A[j][k] -= A[i][k] * factor;
            b[j] -= b[i] * factor;
        }
    }

    x.assign(n, 0);
    for (int i = n - 1; i >= 0; --i) {
        double sum = 0;
        for (int j = i + 1; j < n; ++j) sum += A[i][j] * x[j];
        x[i] = (b[i] - sum) / A[i][i];
    }
    return 1;
}

struct Constraint {
    vector<double> a;
    double b;
};

int main() {
    // // For Testing
    // string testfile;
    // cin >> testfile;
    // testfile = "tests/" + testfile;
    // std::freopen(testfile.c_str(), "r", stdin);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    Matrix A_orig(n, Column(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) cin >> A_orig[i][j];

    Column b_orig(n);
    for (int i = 0; i < n; ++i) cin >> b_orig[i];

    Column pleasure(m);
    for (int i = 0; i < m; ++i) cin >> pleasure[i];

    // Build all constraints: Given + Non-negativity + Infinity bound
    vector<Constraint> all_constraints;
    for (int i = 0; i < n; ++i) all_constraints.push_back({A_orig[i], b_orig[i]});
    for (int i = 0; i < m; ++i) {
        vector<double> row(m, 0);
        row[i] = -1;
        all_constraints.push_back({row, 0.0}); // x_i >= 0  => -x_i <= 0
    }
    vector<double> big_m_row(m, 1);
    all_constraints.push_back({big_m_row, 1e9});

    double max_pleasure = -1e18;
    Column best_x;
    bool found = false;
    bool is_infinite = false;

    int total_c = all_constraints.size();
    vector<int> subset(m);
    
    // Generate all combinations of m constraints
    vector<int> p(total_c);
    fill(p.begin(), p.begin() + m, 1);
    sort(p.begin(), p.end());

    do {
        Matrix A_sub;
        Column b_sub;
        bool uses_big_m = false;
        
        for (int i = 0; i < total_c; ++i) {
            if (p[i]) {
                A_sub.push_back(all_constraints[i].a);
                b_sub.push_back(all_constraints[i].b);
                if (i == total_c - 1) uses_big_m = true;
            }
        }

        Column x;
        if (SolveLinearEquations(A_sub, b_sub, x)) {
            bool ok = true;
            for (const auto& c : all_constraints) {
                double lhs = 0;
                for (int j = 0; j < m; ++j) lhs += c.a[j] * x[j];
                if (lhs > c.b + EPS) { ok = false; break; }
            }

            if (ok) {
                double current_pleasure = 0;
                for (int j = 0; j < m; ++j) current_pleasure += x[j] * pleasure[j];
                if (!found || current_pleasure > max_pleasure) {
                    max_pleasure = current_pleasure;
                    best_x = x;
                    is_infinite = uses_big_m;
                    found = true;
                }
            }
        }
    } while (next_permutation(p.begin(), p.end()));

    if (!found) {
        cout << "No solution" << endl;
    } else if (is_infinite) {
        cout << "Infinity" << endl;
    } else {
        cout << "Bounded solution" << endl;
        for (int i = 0; i < m; ++i) {
            cout << fixed << setprecision(18) << best_x[i] << (i == m - 1 ? "" : " ");
        }
        cout << endl;
    }

    return 0;
}