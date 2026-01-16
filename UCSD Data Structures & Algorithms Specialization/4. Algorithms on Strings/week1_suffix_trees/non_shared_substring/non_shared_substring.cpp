#include <algorithm>
#include <climits>
#include <string>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
#include <functional>

using std::unordered_map;
using std::vector;
using std::string;
using std::pair;
using std::cin;
using std::cout;

using Node = int;
using Value = pair<Node, string>;
using Map = unordered_map<char, Value>;

struct STree {
    vector<Map> edges;
    int root = 0;
    int node_count;
};

STree SuffixTree(const string& Text) {
    int n = Text.size();
    vector<Map> sfxtree(2*n + 5);   // enough for all internal nodes

    int new_node = 1;

    for (int i = 0; i < n; i++) {
        string suffix = Text.substr(i);

        int current = 0;
        bool inserted = false;

        do {
            auto it = sfxtree[current].find(suffix.front());
            if (it == sfxtree[current].end()) {
                auto res = sfxtree[current].emplace(suffix.front(), make_pair(-1, suffix));
                it = res.first;
                inserted = true;
            } else {
                inserted = false;
            }

            if (!inserted) {
                // auto& [child, label] = it->second;
                auto& value = it->second;
				auto child = value.first;
				auto label = value.second;

                auto p = std::mismatch(label.begin(), label.end(), suffix.begin(), suffix.end());
				auto p2 = p.second;
                int j = p2 - suffix.begin();

                string old_tail = label.substr(j);
                string new_tail = suffix.substr(j);

                if (j < (int)label.size()) {     // split
                    label = label.substr(0, j);

                    int split = new_node++;

                    sfxtree[split][old_tail.front()] = { child, old_tail };
                    sfxtree[split][new_tail.front()] = { -1, new_tail };

                    child = split;
                    inserted = true;
                }
                else {
                    if (child == -1) {
                        child = new_node++;
                        sfxtree[child][new_tail.front()] = { -1, new_tail };
                        inserted = true;
                    }
                    else {
                        current = child;
                        suffix = new_tail;
                    }
                }
            }
        } while (!inserted);
    }

    return {sfxtree, 0, new_node };
}

string shortestNonShared(const string& A, const string& B)
{
    string S = A + "#" + B + "$";
    int split = A.size();
    
    STree T = SuffixTree(S);
    
    vector<unsigned char> color(T.node_count, 0);
    
    int best = INT_MAX;
    string answer;
    
    std::function<void(int)> dfs = [&](int u) {
        for (auto it = T.edges[u].begin(); it != T.edges[u].end(); ++it) {
            int v = it->second.first;
            
            if (v != -1) {
                dfs(v);
                color[u] |= color[v];
            }
        }
        
        for (auto it = T.edges[u].begin(); it != T.edges[u].end(); ++it) {
            int v = it->second.first;
            const string& lab = it->second.second;
            
            if (v == -1) {
                int start = (int)S.size() - (int)lab.size();
                if (start < split) color[u] |= 1;
                else if (start > split) color[u] |= 2;
            }
        }
        
        if (color[u] == 1) {
            for (auto it = T.edges[u].begin(); it != T.edges[u].end(); ++it) {
                int v = it->second.first;
                const string& lab = it->second.second;
                
                if (lab.empty() || lab[0] == '#' || lab[0] == '$') continue;
                
                for (size_t k = 1; k <= lab.size() && (int)k < best; ++k) {
                    string candidate = lab.substr(0, k);
                    if (B.find(candidate) == string::npos) {
                        best = k;
                        answer = candidate;
                        break;
                    }
                }
            }
        }
    };
    
    dfs(T.root);
    
    return answer;
}

int main() {
    string A, B;
    std::getline(cin, A);
    std::getline(cin, B);
    cout << shortestNonShared(A, B) << "\n";
}

