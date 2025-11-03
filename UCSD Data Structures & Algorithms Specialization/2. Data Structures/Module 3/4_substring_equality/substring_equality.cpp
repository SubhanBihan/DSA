#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;
const int BASE = 31;

class RollingHash {
private:
    vector<long long> hash, power;
    int n;
    
public:
    RollingHash(const string& s) {
        n = s.length();
        hash.resize(n + 1, 0);
        power.resize(n + 1, 1);
        
        // Precompute powers of BASE
        for (int i = 1; i <= n; i++) {
            power[i] = (power[i-1] * BASE) % MOD;
        }
        
        // Compute prefix hashes
        for (int i = 0; i < n; i++) {
            hash[i+1] = (hash[i] * BASE + (s[i] - 'a' + 1)) % MOD;
        }
    }
    
    // Get hash of substring s[l:r] (0-indexed, r exclusive)
    long long getHash(int l, int r) {
        long long result = (hash[r] - (hash[l] * power[r-l]) % MOD + MOD) % MOD;
        return result;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    cin >> s;
    
    int q;
    cin >> q;
    
    RollingHash rh(s);
    
    while (q--) {
        int a, b, l;
        cin >> a >> b >> l;
        
        long long hash1 = rh.getHash(a, a + l);
        long long hash2 = rh.getHash(b, b + l);
        
        if (hash1 == hash2) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    
    return 0;
}