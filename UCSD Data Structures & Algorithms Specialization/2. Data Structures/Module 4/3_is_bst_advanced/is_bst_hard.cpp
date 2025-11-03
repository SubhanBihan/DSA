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

bool isBSTHard(int idx, long long minVal, long long maxVal) {
    if (idx == -1) return true;

    long long key = tree[idx].key;

    // For hard version:
    // keys in left subtree: strictly less than key
    // keys in right subtree: greater than or equal to key
    if (key < minVal || key >= maxVal)
        return false;

    return isBSTHard(tree[idx].left, minVal, key) &&
           isBSTHard(tree[idx].right, key, maxVal);
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
    for (int i = 0; i < n; i++)
        cin >> tree[i].key >> tree[i].left >> tree[i].right;

    if (isBSTHard(0, LLONG_MIN, LLONG_MAX))
        cout << "CORRECT\n";
    else
        cout << "INCORRECT\n";

    return 0;
}
