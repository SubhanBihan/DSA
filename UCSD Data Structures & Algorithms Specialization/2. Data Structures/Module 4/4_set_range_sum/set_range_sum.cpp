#include <iostream>
using namespace std;

const long long MOD = 1000000001LL;

struct Node {
    long long key;
    long long sum;
    Node* left;
    Node* right;
    Node* parent;
    Node(long long k) : key(k), sum(k), left(nullptr), right(nullptr), parent(nullptr) {}
};

class SplayTree {
private:
    Node* root = nullptr;

    void update(Node* v) {
        if (!v) return;
        v->sum = v->key;
        if (v->left)  v->sum += v->left->sum;
        if (v->right) v->sum += v->right->sum;
        if (v->left)  v->left->parent = v;
        if (v->right) v->right->parent = v;
    }

    void smallRotate(Node* v) {
        Node* p = v->parent;
        if (!p) return;
        Node* g = p->parent;
        if (p->left == v) {
            p->left = v->right;
            v->right = p;
        } else {
            p->right = v->left;
            v->left = p;
        }
        if (g) {
            if (g->left == p) g->left = v;
            else g->right = v;
        }
        v->parent = g;
        p->parent = v;
        if (p->left) p->left->parent = p;
        if (p->right) p->right->parent = p;
        update(p);
        update(v);
    }

    void bigRotate(Node* v) {
        if (!v->parent || !v->parent->parent) return;
        Node* p = v->parent;
        Node* g = p->parent;
        if ((p->left == v) == (g->left == p)) {
            // zig-zig
            smallRotate(p);
            smallRotate(v);
        } else {
            // zig-zag
            smallRotate(v);
            smallRotate(v);
        }
    }

    void splay(Node* v) {
        if (!v) return;
        while (v->parent) {
            if (!v->parent->parent) {
                smallRotate(v);
                break;
            }
            bigRotate(v);
        }
        root = v;
    }

    // findNode: search for key, track last visited node; splay(last)
    // returns pointer to node with key if found, otherwise nullptr
    Node* findNode(long long key) {
        Node* v = root;
        Node* last = nullptr;
        Node* next = nullptr; // candidate with key >= key (not used in this split scheme)
        while (v) {
            last = v;
            if (v->key == key) {
                break;
            }
            if (key < v->key) {
                v = v->left;
            } else {
                v = v->right;
            }
        }
        if (last) splay(last);
        if (root && root->key == key) return root;
        return nullptr;
    }

    // split by key: left contains keys < key, right contains keys >= key
    void split(Node* curRoot, long long key, Node*& left, Node*& right) {
        left = right = nullptr;
        root = curRoot;
        if (!root) {
            left = right = nullptr;
            return;
        }

        Node* found = findNode(key);
        // after findNode, root is last accessed node
        if (!root) {
            left = right = nullptr;
            return;
        }

        if (root->key >= key) {
            // root and its right subtree are >= key; left subtree of root are < key
            right = root;
            left = right->left;
            if (left) left->parent = nullptr;
            right->left = nullptr;
            update(left);
            update(right);
        } else {
            // root->key < key, so root and its left subtree are < key
            left = root;
            right = left->right;
            if (right) right->parent = nullptr;
            left->right = nullptr;
            update(left);
            update(right);
        }
    }

    Node* merge(Node* left, Node* right) {
        if (!left) return right;
        if (!right) return left;
        // find max in left
        Node* v = left;
        while (v->right) v = v->right;
        splay(v); // now v is root and has no right child
        v->right = right;
        if (right) right->parent = v;
        update(v);
        return v;
    }

public:
    void insert(long long key) {
        Node *left, *right;
        split(root, key, left, right);
        // If right's minimal key == key then key already present.
        if (right && right->key == key) {
            root = merge(left, right);
            return;
        }
        Node* newNode = new Node(key);
        root = merge(merge(left, newNode), right);
    }

    void erase(long long key) {
        if (!root) return;
        Node* node = findNode(key);
        if (!node || root->key != key) {
            // not found
            return;
        }
        // root is the node to delete
        Node* left = root->left;
        Node* right = root->right;
        if (left) left->parent = nullptr;
        if (right) right->parent = nullptr;
        delete root;
        root = merge(left, right);
    }

    bool find(long long key) {
        if (!root) return false;
        Node* node = findNode(key);
        if (node && root->key == key) {
            return true;
        }
        return false;
    }

    long long sum(long long l, long long r) {
        Node *left, *middle, *right;
        split(root, l, left, middle);          // middle has keys >= l
        split(middle, r + 1, middle, right);   // middle has keys in [l, r]
        long long ans = 0;
        if (middle) ans = middle->sum;
        root = merge(merge(left, middle), right);
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    SplayTree tree;
    long long lastSum = 0;

    for (int i = 0; i < n; ++i) {
        char op;
        cin >> op;
        if (op == '+') {
            long long x; cin >> x;
            tree.insert((x + lastSum) % MOD);
        } else if (op == '-') {
            long long x; cin >> x;
            tree.erase((x + lastSum) % MOD);
        } else if (op == '?') {
            long long x; cin >> x;
            cout << (tree.find((x + lastSum) % MOD) ? "Found\n" : "Not found\n");
        } else if (op == 's') {
            long long l, r; cin >> l >> r;
            lastSum = tree.sum((l + lastSum) % MOD, (r + lastSum) % MOD);
            cout << lastSum << "\n";
        }
    }
    return 0;
}
