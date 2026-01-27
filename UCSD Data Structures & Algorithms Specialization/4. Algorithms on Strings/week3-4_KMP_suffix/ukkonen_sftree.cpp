#include <unordered_map>
#include <iostream>
#include <string>
// #include <vector>

using namespace std;

/*
 Ukkonen's Suffix Tree construction (online, O(n))
 --------------------------------------------------
 This implementation builds a suffix tree for a single string S.
 It uses implicit/explicit nodes, suffix links, and a global end
 pointer for all leaf edges.

 Alphabet: generic char (ASCII-safe)
 Terminator: You should append a unique character (e.g. '$') that
 does not appear elsewhere in the string.
*/

struct Node {
    unordered_map<char, Node*> next; // outgoing edges
    Node* link;                       // suffix link
    int start;                        // edge start index
    int* end;                         // edge end index (inclusive)
    int suffixIndex;                  // for leaves only

    Node(int s, int* e) : link(nullptr), start(s), end(e), suffixIndex(-1) {}
};

class SuffixTree {
private:
    string text;
    Node* root;
    Node* lastNewNode;
    Node* activeNode;

    int activeEdge;   // index in text
    int activeLength; // length on edge

    int remainingSuffixCount;
    int leafEnd;
    int* rootEnd;
    int* splitEnd;

    int size; // length of text

    Node* newNode(int start, int* end) {
        Node* node = new Node(start, end);
        node->link = root;
        return node;
    }

    int edgeLength(Node* n) {
        return *(n->end) - n->start + 1;
    }

    bool walkDown(Node* currNode) {
        if (activeLength >= edgeLength(currNode)) {
            activeEdge += edgeLength(currNode);
            activeLength -= edgeLength(currNode);
            activeNode = currNode;
            return true;
        }
        return false;
    }

    void extendSuffixTree(int pos) {
        leafEnd = pos;
        remainingSuffixCount++;
        lastNewNode = nullptr;

        while (remainingSuffixCount > 0) {
            if (activeLength == 0)
                activeEdge = pos;

            char currentChar = text[activeEdge];

            // No outgoing edge starting with currentChar
            if (activeNode->next.find(currentChar) == activeNode->next.end()) {
                activeNode->next[currentChar] = newNode(pos, &leafEnd);

                if (lastNewNode != nullptr) {
                    lastNewNode->link = activeNode;
                    lastNewNode = nullptr;
                }
            }
            else {
                Node* next = activeNode->next[currentChar];
                if (walkDown(next))
                    continue;

                // Current character already on the edge
                if (text[next->start + activeLength] == text[pos]) {
                    if (lastNewNode != nullptr && activeNode != root) {
                        lastNewNode->link = activeNode;
                        lastNewNode = nullptr;
                    }
                    activeLength++;
                    break;
                }

                // Split edge
                splitEnd = new int(next->start + activeLength - 1);
                Node* split = newNode(next->start, splitEnd);
                activeNode->next[currentChar] = split;

                split->next[text[pos]] = newNode(pos, &leafEnd);
                next->start += activeLength;
                split->next[text[next->start]] = next;

                if (lastNewNode != nullptr)
                    lastNewNode->link = split;

                lastNewNode = split;
            }

            remainingSuffixCount--;

            if (activeNode == root && activeLength > 0) {
                activeLength--;
                activeEdge = pos - remainingSuffixCount + 1;
            }
            else if (activeNode != root) {
                activeNode = activeNode->link;
            }
        }
    }

    void setSuffixIndexByDFS(Node* n, int labelHeight) {
        if (!n) return;

        bool isLeaf = true;
        for (auto& kv : n->next) {
            isLeaf = false;
            setSuffixIndexByDFS(kv.second, labelHeight + edgeLength(kv.second));
        }
        if (isLeaf) {
            n->suffixIndex = size - labelHeight;
        }
    }

    void freeTree(Node* n) {
        if (!n) return;
        for (auto& kv : n->next)
            freeTree(kv.second);
        if (n->end != &leafEnd && n->end != rootEnd)
            delete n->end;
        delete n;
    }

public:
    SuffixTree(const string& s) : text(s) {
        size = text.size();

        rootEnd = new int(-1);
        root = new Node(-1, rootEnd);
        root->link = root;

        activeNode = root;
        activeEdge = -1;
        activeLength = 0;
        remainingSuffixCount = 0;
        leafEnd = -1;

        for (int i = 0; i < size; i++)
            extendSuffixTree(i);

        setSuffixIndexByDFS(root, 0);
    }

    ~SuffixTree() {
        freeTree(root);
        delete rootEnd;
    }

    void printDFS(Node* n, int height) {
        if (!n) return;
        if (n->start != -1) {
            for (int i = n->start; i <= *(n->end); i++)
                cout << text[i];
            cout << " [" << n->suffixIndex << "]";
        }
        cout << '\n';
        for (auto& kv : n->next) {
            printDFS(kv.second, height + edgeLength(kv.second));
        }
    }

    void printTree() {
        printDFS(root, 0);
    }
};

int main() {
    string s;
    cin >> s;
    s.push_back('$'); // unique terminator

    SuffixTree st(s);
    st.printTree();

    return 0;
}
