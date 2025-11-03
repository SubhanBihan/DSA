#include <iostream>
#include <string>
using namespace std;

struct Node {
    char ch;
    int size;
    Node* left;
    Node* right;
    Node* parent;
    
    Node(char c) : ch(c), size(1), left(nullptr), right(nullptr), parent(nullptr) {}
};

void update(Node* n) {
    if (!n) return;
    n->size = 1;
    if (n->left) n->size += n->left->size;
    if (n->right) n->size += n->right->size;
}

void setParent(Node* child, Node* par) {
    if (child) child->parent = par;
}

void keepParent(Node* n) {
    if (!n) return;
    setParent(n->left, n);
    setParent(n->right, n);
}

void rotate(Node* n) {
    Node* p = n->parent;
    Node* g = p->parent;
    
    if (p->left == n) {
        Node* m = n->right;
        n->right = p;
        p->left = m;
    } else {
        Node* m = n->left;
        n->left = p;
        p->right = m;
    }
    
    keepParent(p);
    keepParent(n);
    setParent(n, g);
    if (g) {
        if (g->left == p) g->left = n;
        else g->right = n;
    }
    
    update(p);
    update(n);
}

void splay(Node* n) {
    if (!n) return;
    while (n->parent) {
        Node* p = n->parent;
        Node* g = p->parent;
        if (!g) {
            rotate(n);
        } else if ((g->left == p) == (p->left == n)) {
            rotate(p);
            rotate(n);
        } else {
            rotate(n);
            rotate(n);
        }
    }
}

Node* find(Node* root, int k) {
    if (!root) return nullptr;
    int leftSize = root->left ? root->left->size : 0;
    if (k < leftSize) return find(root->left, k);
    if (k == leftSize) {
        splay(root);
        return root;
    }
    return find(root->right, k - leftSize - 1);
}

pair<Node*, Node*> split(Node* root, int k) {
    if (k == 0) return {nullptr, root};
    if (!root) return {nullptr, nullptr};
    if (k >= root->size) return {root, nullptr};
    
    Node* n = find(root, k);
    if (!n) return {root, nullptr};
    
    Node* right = n->left;
    n->left = nullptr;
    setParent(right, nullptr);
    update(n);
    return {right, n};
}

Node* merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;
    
    Node* curr = right;
    while (curr->left) curr = curr->left;
    splay(curr);
    curr->left = left;
    setParent(left, curr);
    update(curr);
    return curr;
}

void inorder(Node* n, string& result) {
    if (!n) return;
    inorder(n->left, result);
    result += n->ch;
    inorder(n->right, result);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    cin >> s;
    
    int q;
    cin >> q;
    
    Node* root = nullptr;
    for (char c : s) {
        Node* newNode = new Node(c);
        root = merge(root, newNode);
    }
    
    for (int idx = 0; idx < q; idx++) {
        int i, j, k;
        cin >> i >> j >> k;
        
        // Split to get [0..i-1], [i..n-1]
        auto p1 = split(root, i);
        Node* left = p1.first;
        Node* temp = p1.second;
        
        // Split [i..n-1] to get [i..j], [j+1..n-1]
        auto p2 = split(temp, j - i + 1);
        Node* mid = p2.first;
        Node* right = p2.second;
        
        // Merge left and right (without mid)
        Node* merged = merge(left, right);
        
        // Split at position k to insert mid
        auto p3 = split(merged, k);
        Node* left2 = p3.first;
        Node* right2 = p3.second;
        
        // Merge: left2 + mid + right2
        root = merge(merge(left2, mid), right2);
    }
    
    string result;
    inorder(root, result);
    cout << result << "\n";
    
    return 0;
}