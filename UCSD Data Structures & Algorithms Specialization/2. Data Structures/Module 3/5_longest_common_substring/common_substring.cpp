#include <string>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <iostream>

using namespace std;

typedef uint64_t ull;

const ull BASE = 131;  // A good large base
const ull MOD = (1ULL << 61) - 1;

inline ull modmul(ull a, ull b) {
    __uint128_t res = (__uint128_t)a * b;
    ull low = (ull)res & MOD;
    ull high = (ull)(res >> 61);
    ull sum = low + high;
    if (sum >= MOD) sum -= MOD;
    return sum;
}

inline ull modadd(ull a, ull b) {
    ull res = a + b;
    if (res >= MOD) res -= MOD;
    return res;
}

vector<ull> computeHashes(const string& s, vector<ull>& power) {
    int n = s.size();
    vector<ull> hash(n + 1, 0);
    power.resize(n + 1);
    power[0] = 1;

    for (int i = 0; i < n; ++i) {
        power[i + 1] = modmul(power[i], BASE);
        hash[i + 1] = modadd(modmul(hash[i], BASE), s[i]);
    }
    return hash;
}

ull getHash(const vector<ull>& hash, const vector<ull>& power, int l, int r) {
    ull res = hash[r] + MOD - modmul(hash[l], power[r - l]);
    if (res >= MOD) res -= MOD;
    return res;
}


void LongestCommonSubstring(string A, string B) {
    int n = A.size(), m = B.size();
    vector<ull> powerA, powerB;
    auto hashA = computeHashes(A, powerA);
    auto hashB = computeHashes(B, powerB);

    int low = 0, high = min(n, m);
    int bestLen = 0;
    int posA = 0, posB = 0;

    while (low <= high) {
        int len = (low + high) / 2;
        unordered_map<ull, int> seen;

        for (int i = 0; i + len <= n; ++i)
            seen[getHash(hashA, powerA, i, i + len)] = i;

        bool found = false;
        for (int j = 0; j + len <= m; ++j) {
            ull h = getHash(hashB, powerB, j, j + len);
            if (seen.count(h)) {
                found = true;
                posA = seen[h];
                posB = j;
                break;
            }
        }

        if (found) {
            bestLen = len;
            low = len + 1;
        } else {
            high = len - 1;
        }
    }

    cout << posA << " " << posB << " " << bestLen << "\n";
}

// SUFFIX AUTOMATON
struct State {
    int len, link;
    unordered_map<char, int> next;
    int first_pos;   // NEW
};


struct LCSResult {
    int posA, posB, length;
};


struct SuffixAutomaton {
    vector<State> st;
    int last;

    SuffixAutomaton(const string &s) {
        st.reserve(2 * s.size());
        st.push_back({0, -1});  // initial state
        last = 0;

        for (char c : s)
            extend(c);
    }

    void extend(char c) {
        int cur = st.size();
        st.push_back({st[last].len + 1, 0, {}, st[last].len});
        int p = last;

        while (p != -1 && !st[p].next.count(c)) {
            st[p].next[c] = cur;
            p = st[p].link;
        }

        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = st.size();
                st.push_back({st[p].len + 1, st[q].link, st[q].next, st[q].first_pos});
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }

        last = cur;
    }


    // Find longest common substring with string t
    string longest_common_substring(const string &t) {
        int v = 0, l = 0, best = 0, bestPos = 0;
        for (int i = 0; i < (int)t.size(); ++i) {
            char c = t[i];
            while (v && !st[v].next.count(c)) {
                v = st[v].link;
                l = st[v].len;
            }
            if (st[v].next.count(c)) {
                v = st[v].next[c];
                ++l;
            }
            if (l > best) {
                best = l;
                bestPos = i;
            }
        }
        return t.substr(bestPos - best + 1, best);
    }

    
};

LCSResult LCS(const SuffixAutomaton &sa, const string &t) {
    int v = 0, l = 0;
    int best = 0, bestPos = -1, bestState = 0;

    for (int i = 0; i < (int)t.size(); ++i) {
        char c = t[i];
        while (v && !sa.st[v].next.count(c)) {
            v = sa.st[v].link;
            l = sa.st[v].len;
        }
        if (sa.st[v].next.count(c)) {
            v = sa.st[v].next.at(c);
            ++l;
        }
        if (l > best) {
            best = l;
            bestPos = i;
            bestState = v;
        }
    }

    if (best == 0) return {0, 0, 0};

    int posB = bestPos - best + 1;
    int posA = sa.st[bestState].first_pos - best + 1;

    return {posA, posB, best};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Approach 1: Read until EOF and store pairs
    vector<pair<string, string>> inputs;
    string s, t;
    
    // Read all input pairs until EOF
    while (cin >> s >> t) {
        inputs.push_back({s, t});
    }
    
    // Process all inputs and store results
    for (const auto& p : inputs) {
        // LongestCommonSubstring(p.first, p.second);
        SuffixAutomaton sa(p.first);
        auto res = LCS(sa, p.second);
        cout << res.posA << " " << res.posB << " " << res.length << "\n";
    }

    // while (cin >> s >> t) {
    //     SuffixAutomaton sa(s);
    //     auto res = LCS(sa, t);
    //     cout << res.posA << " " << res.posB << " " << res.length << "\n";
    // }

    return 0;
}
