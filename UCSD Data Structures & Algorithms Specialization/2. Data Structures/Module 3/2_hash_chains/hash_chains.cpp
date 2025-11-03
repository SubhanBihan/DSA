// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

struct HashTable {
    int m; // number of buckets
    const long long p = 1000000007;
    const long long x = 263;
    vector<list<string>> table; // chaining with linked lists

    HashTable(int m) : m(m) {
        table.resize(m);
    }

    long long hash_func(const string& s) const {
        long long hash = 0;
        long long power = 1;
        for (char c : s) {
            hash = (hash + (c * power) % p) % p;
            power = (power * x) % p;
        }
        return hash % m;
    }

    void add(const string& s) {
        long long idx = hash_func(s);
        for (const auto& str : table[idx]) {
            if (str == s) return; // already exists
        }
        table[idx].push_front(s); // insert at beginning
    }

    void del(const string& s) {
        long long idx = hash_func(s);
        for (auto it = table[idx].begin(); it != table[idx].end(); ++it) {
            if (*it == s) {
                table[idx].erase(it);
                return;
            }
        }
    }

    string find(const string& s) {
        long long idx = hash_func(s);
        for (const auto& str : table[idx]) {
            if (str == s) return "yes";
        }
        return "no";
    }

    string check(int i) {
        string result;
        for (const auto& str : table[i]) {
            result += str + " ";
        }
        if (!result.empty()) result.pop_back(); // remove trailing space
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    HashTable ht(m);

    for (int i = 0; i < n; i++) {
        string cmd;
        cin >> cmd;
        if (cmd == "add") {
            string s;
            cin >> s;
            ht.add(s);
        } else if (cmd == "del") {
            string s;
            cin >> s;
            ht.del(s);
        } else if (cmd == "find") {
            string s;
            cin >> s;
            cout << ht.find(s) << "\n";
        } else if (cmd == "check") {
            int idx;
            cin >> idx;
            string res = ht.check(idx);
            cout << res << "\n";
        }
    }

    return 0;
}
