#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <cstdio>

using namespace std;

const double EPS = 1e-8;
const double INF = 1e100;

void pivot(vector<vector<double>>& tab, int p, int enterCol, int leaveRow) {
    int cols = tab[0].size();
    double pivotVal = tab[leaveRow][enterCol];
    
    // Normalize pivot row
    for (int j = 0; j < cols; j++) {
        tab[leaveRow][j] /= pivotVal;
    }
    
    // Eliminate pivot column in other rows
    for (int i = 0; i < p + 1; i++) {
        if (i != leaveRow && abs(tab[i][enterCol]) > EPS) {
            double factor = tab[i][enterCol];
            for (int j = 0; j < cols; j++) {
                tab[i][j] -= factor * tab[leaveRow][j];
            }
        }
    }
}

int main() {
    // For Testing
    string testfile;
    cin >> testfile;
    testfile = "tests/" + testfile;
    std::freopen(testfile.c_str(), "r", stdin);
    
    // ios_base::sync_with_stdio(false);
    // cin.tie(nullptr);
    
    int p, q;
    cin >> p >> q;
    
    vector<vector<double>> A(p, vector<double>(q));
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < q; j++) {
            cin >> A[i][j];
        }
    }
    
    vector<double> b(p);
    for (int i = 0; i < p; i++) {
        cin >> b[i];
    }
    
    vector<double> c(q);
    for (int i = 0; i < q; i++) {
        cin >> c[i];
    }
    
    // Count negative RHS (need artificial variables)
    int numArt = 0;
    for (int i = 0; i < p; i++) {
        if (b[i] < -EPS) numArt++;
    }
    
    // Tableau dimensions: (p+1) rows x (q + p + numArt + 1) cols
    // Columns: [original vars | slack vars | artificial vars | RHS]
    vector<vector<double>> tab(p + 1, vector<double>(q + p + numArt + 1, 0));
    vector<int> basis(p);
    
    // Fill tableau
    int artIdx = 0;
    for (int i = 0; i < p; i++) {
        // Copy A matrix
        for (int j = 0; j < q; j++) {
            tab[i][j] = A[i][j];
        }
        
        if (b[i] < -EPS) {
            // Negative RHS: multiply row by -1 and add artificial
            for (int j = 0; j <= q + p + numArt; j++) {
                tab[i][j] *= -1;
            }
            tab[i][q + p + artIdx] = 1; // artificial variable
            tab[i][q + p + numArt] = -b[i]; // RHS
            basis[i] = q + p + artIdx;
            artIdx++;
        } else {
            tab[i][q + i] = 1; // slack variable
            tab[i][q + p + numArt] = b[i]; // RHS
            basis[i] = q + i;
        }
    }
    
    int rhsCol = q + p + numArt;
    
    if (numArt > 0) {
        // PHASE 1: Minimize sum of artificial variables
        // Set objective coefficients: we want min Σ(artificial vars)
        // For simplex in standard form (looking for negative reduced costs), 
        // we set coefficients to +1 for artificial variables
        for (int j = q + p; j < q + p + numArt; j++) {
            tab[p][j] = 1;
        }
        
        // Make objective row canonical (eliminate basic variables)
        for (int i = 0; i < p; i++) {
            if (basis[i] >= q + p) { // basic artificial variable
                for (int j = 0; j <= rhsCol; j++) {
                    tab[p][j] -= tab[i][j];
                }
            }
        }
        
        // Phase 1 simplex iterations
        while (true) {
            // Find entering column (most negative reduced cost)
            // Exclude artificial columns - they shouldn't re-enter
            int enterCol = -1;
            double minCoeff = -EPS;
            for (int j = 0; j < q + p; j++) { // only original + slack vars
                if (tab[p][j] < minCoeff) {
                    minCoeff = tab[p][j];
                    enterCol = j;
                }
            }
            
            if (enterCol == -1) break; // Phase 1 optimal
            
            // Find leaving row (minimum ratio test)
            int leaveRow = -1;
            double minRatio = INF;
            for (int i = 0; i < p; i++) {
                if (tab[i][enterCol] > EPS) {
                    double ratio = tab[i][rhsCol] / tab[i][enterCol];
                    if (ratio < minRatio) {
                        minRatio = ratio;
                        leaveRow = i;
                    }
                }
            }
            
            if (leaveRow == -1) {
                cout << "Infinity" << endl;
                return 0;
            }
            
            pivot(tab, p, enterCol, leaveRow);
            basis[leaveRow] = enterCol;
        }
        
        // Check feasibility: objective value should be 0
        // The objective value is -tab[p][rhsCol] (negative because of how we set it up)
        if (tab[p][rhsCol] < -EPS) {
            cout << "No solution" << endl;
            return 0;
        }
        
        // Remove artificial variables from tableau
        vector<vector<double>> newTab(p + 1, vector<double>(q + p + 1, 0));
        for (int i = 0; i < p + 1; i++) {
            for (int j = 0; j < q + p; j++) {
                newTab[i][j] = tab[i][j];
            }
            newTab[i][q + p] = tab[i][rhsCol];
        }
        tab = newTab;
        rhsCol = q + p;
    }
    
    // PHASE 2: Maximize c'x
    // Set objective row
    for (int j = 0; j < q; j++) {
        tab[p][j] = -c[j]; // negative for maximization
    }
    for (int j = q; j < rhsCol; j++) {
        tab[p][j] = 0;
    }
    tab[p][rhsCol] = 0;
    
    // Make objective canonical
    for (int i = 0; i < p; i++) {
        if (basis[i] < q && abs(tab[p][basis[i]]) > EPS) {
            double coeff = tab[p][basis[i]];
            for (int j = 0; j <= rhsCol; j++) {
                tab[p][j] -= coeff * tab[i][j];
            }
        }
    }
    
    // Phase 2 simplex iterations
    while (true) {
        // Find entering column (most negative reduced cost)
        int enterCol = -1;
        double minCoeff = -EPS;
        for (int j = 0; j < rhsCol; j++) {
            if (tab[p][j] < minCoeff) {
                minCoeff = tab[p][j];
                enterCol = j;
            }
        }
        
        if (enterCol == -1) {
            // Optimal solution found
            vector<double> solution(q, 0);
            for (int i = 0; i < p; i++) {
                if (basis[i] < q) {
                    solution[basis[i]] = tab[i][rhsCol];
                }
            }
            
            cout << fixed << setprecision(15);
            cout << "Bounded solution" << endl;
            for (int i = 0; i < q; i++) {
                cout << solution[i];
                if (i < q - 1) cout << " ";
            }
            cout << endl;
            return 0;
        }
        
        // Find leaving row
        int leaveRow = -1;
        double minRatio = INF;
        for (int i = 0; i < p; i++) {
            if (tab[i][enterCol] > EPS) {
                double ratio = tab[i][rhsCol] / tab[i][enterCol];
                if (ratio < minRatio) {
                    minRatio = ratio;
                    leaveRow = i;
                }
            }
        }
        
        if (leaveRow == -1) {
            cout << "Infinity" << endl;
            return 0;
        }
        
        pivot(tab, p, enterCol, leaveRow);
        basis[leaveRow] = enterCol;
    }
    
    return 0;
}