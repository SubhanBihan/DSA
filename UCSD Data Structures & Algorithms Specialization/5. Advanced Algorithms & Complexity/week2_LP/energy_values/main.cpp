// NOTE: This program assumes a unique solution exists
// #include <cmath>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <utility>
#include <cstdio>

using namespace std;

#define N_MAX 20
const double EPS = 1e-6;
// const int PRECISION = 20;

#define gtzero(a) (((a) > EPS) || ((a) < -EPS))

using Column = vector<double>;
using Row = vector<double>;
using Matrix = vector<Row>;
// using tracker = bitset<N_MAX>;

struct Equation {
    Matrix a;
    Column b;

    Equation(const Matrix &a, const Column &b): a(a), b(b) {}

    void Swap(int row1, int row2) {
        swap(a[row1], a[row2]);
        swap(b[row1], b[row2]);
    }

    void ScaleDown(int row, const double k) {       // Scales down row - starting from pivot (column) position
        for (int col = row; col < a.size(); col++) {
            if (gtzero(a[row][col]))
                a[row][col] /= k;
        }

        if(gtzero(b[row]))
            b[row] /= k;
    }
};

Equation ReadEquation() {
    int size;
    cin >> size;
    Matrix a(size, vector<double> (size, 0.0));
    Column b(size, 0.0);
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column)
            cin >> a[row][column];
        cin >> b[row];
    }
    return Equation(a, b);
}

int main() {
    // // For Testing
    // std::freopen("data.txt", "r", stdin);

    int size;
    cin >> size;
    if (size == 0) return EXIT_SUCCESS;

    Matrix a(size, vector<double> (size, 0.0));
    Column b(size, 0.0);

    // Read in values
    int next_pivot = -1;
    for (int row = 0; row < size; row++) {
        for (int column = 0; column < size; column++)
            cin >> a[row][column];
        cin >> b[row];

        if (next_pivot == -1 && gtzero(a[row][0])) next_pivot = row;
    }
    
    Equation S(a, b);

    // Gaussian Elimination
    for (int pivot = 0; pivot < size; pivot++) {
        if (pivot != size - 1)
            S.Swap(pivot, next_pivot);
        S.ScaleDown(pivot, S.a[pivot][pivot]);
        next_pivot = -1;

        for (int row = 0; row < size; row++) {
            if (row != pivot && gtzero(S.a[row][pivot])) {
                const double factor = S.a[row][pivot];
                for (int col = pivot; col < size; col++)
                    S.a[row][col] -= factor * S.a[pivot][col];

                S.b[row] -= factor * S.b[pivot];
            }

            if (row > pivot && next_pivot == -1 && gtzero(S.a[row][pivot + 1]))
                next_pivot = row;
        }
    }

    // Print results
    for (const auto& x: S.b) {
        printf("%.06f ", x);
    }
    printf("\n");
    
    return EXIT_SUCCESS;
}
