#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Node {
    long long key;
    int left;
    int right;
};

vector<Node> tree;

bool isBST(int idx, long long minVal, long long maxVal) {
    if (idx == -1) return true;
    
    if (tree[idx].key <= minVal || tree[idx].key >= maxVal) {
        return false;
    }
    
    return isBST(tree[idx].left, minVal, tree[idx].key) &&
           isBST(tree[idx].right, tree[idx].key, maxVal);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    if (n == 0) {
        cout << "CORRECT\n";
        return 0;
    }
    
    tree.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> tree[i].key >> tree[i].left >> tree[i].right;
    }
    
    if (isBST(0, LLONG_MIN, LLONG_MAX)) {
        cout << "CORRECT\n";
    } else {
        cout << "INCORRECT\n";
    }
    
    return 0;
}