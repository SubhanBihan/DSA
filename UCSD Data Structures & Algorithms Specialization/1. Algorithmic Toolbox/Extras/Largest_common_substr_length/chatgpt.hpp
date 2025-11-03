#pragma once

#include "helpers.hpp"
// #include <bits/stdc++.h>

typedef uint64_t ull;

const ull BASE = 131;  // A good large base
const ull MOD = (1ULL << 61) - 1;

vector<ull> computeHashes(const string& s, vector<ull>& power) {
    int n = s.size();
    vector<ull> hash(n + 1, 0);
    power.resize(n + 1);
    power[0] = 1;

    for (int i = 0; i < n; ++i) {
        power[i + 1] = power[i] * BASE;
        hash[i + 1] = hash[i] * BASE + s[i];
    }
    return hash;
}

ull getHash(const vector<ull>& hash, const vector<ull>& power, int l, int r) {
    return hash[r] - hash[l] * power[r - l];
}

string GPTLongestCommonSubstring(string A, string B) {
    int n = A.size(), m = B.size();
    vector<ull> powerA, powerB;
    auto hashA = computeHashes(A, powerA);
    auto hashB = computeHashes(B, powerB);

    int low = 0, high = min(n, m);
    int bestLen = 0;
    int posA = 0;

    while (low <= high) {
        int len = (low + high) / 2;
        unordered_set<ull> seen;

        for (int i = 0; i + len <= n; ++i)
            seen.insert(getHash(hashA, powerA, i, i + len));

        bool found = false;
        for (int j = 0; j + len <= m; ++j) {
            ull h = getHash(hashB, powerB, j, j + len);
            if (seen.count(h)) {
                found = true;
                posA = j;
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

    return B.substr(posA, bestLen);
}

// SUFFIX AUTOMATON
struct State {
    int len, link;
    unordered_map<char, int> next;
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
        st.push_back({st[last].len + 1, 0});
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
                st.push_back({st[p].len + 1, st[q].link, st[q].next});
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

/*
    USAGE: 
        SuffixAutomaton sa(s1);
        string lcs = sa.longest_common_substring(s2);
    Time complexity: O(n + m) - fastest possible in theory
    Space complexity: O(n)
*/