#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct Node {
    int key;
    int left;
    int right;
};

vector<Node> tree;
vector<int> result;

void inOrder(int idx) {
    if (idx == -1) return;
    inOrder(tree[idx].left);
    result.push_back(tree[idx].key);
    inOrder(tree[idx].right);
}

void preOrder(int idx) {
    if (idx == -1) return;
    result.push_back(tree[idx].key);
    preOrder(tree[idx].left);
    preOrder(tree[idx].right);
}

void postOrder(int idx) {
    if (idx == -1) return;
    postOrder(tree[idx].left);
    postOrder(tree[idx].right);
    result.push_back(tree[idx].key);
}

// Iterative versions to avoid stack overflow for deep trees
void inOrderIterative(int root) {
    stack<int> st;
    int curr = root;
    
    while (curr != -1 || !st.empty()) {
        while (curr != -1) {
            st.push(curr);
            curr = tree[curr].left;
        }
        curr = st.top();
        st.pop();
        result.push_back(tree[curr].key);
        curr = tree[curr].right;
    }
}

void preOrderIterative(int root) {
    if (root == -1) return;
    stack<int> st;
    st.push(root);
    
    while (!st.empty()) {
        int curr = st.top();
        st.pop();
        result.push_back(tree[curr].key);
        
        if (tree[curr].right != -1) st.push(tree[curr].right);
        if (tree[curr].left != -1) st.push(tree[curr].left);
    }
}

void postOrderIterative(int root) {
    if (root == -1) return;
    stack<int> st1, st2;
    st1.push(root);
    
    while (!st1.empty()) {
        int curr = st1.top();
        st1.pop();
        st2.push(curr);
        
        if (tree[curr].left != -1) st1.push(tree[curr].left);
        if (tree[curr].right != -1) st1.push(tree[curr].right);
    }
    
    while (!st2.empty()) {
        result.push_back(tree[st2.top()].key);
        st2.pop();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    tree.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> tree[i].key >> tree[i].left >> tree[i].right;
    }
    
    if (n > 0) {
        // In-order
        result.clear();
        inOrderIterative(0);
        for (int i = 0; i < result.size(); i++) {
            if (i > 0) cout << " ";
            cout << result[i];
        }
        cout << "\n";
        
        // Pre-order
        result.clear();
        preOrderIterative(0);
        for (int i = 0; i < result.size(); i++) {
            if (i > 0) cout << " ";
            cout << result[i];
        }
        cout << "\n";
        
        // Post-order
        result.clear();
        postOrderIterative(0);
        for (int i = 0; i < result.size(); i++) {
            if (i > 0) cout << " ";
            cout << result[i];
        }
        cout << "\n";
    }
    
    return 0;
}