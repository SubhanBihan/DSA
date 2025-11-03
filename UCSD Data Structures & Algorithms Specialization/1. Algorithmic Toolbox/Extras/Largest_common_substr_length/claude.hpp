#pragma once

#include "helpers.hpp"

class LongestCommonSubstring {
private:
    static const int BASE = 31;
    static const int MOD = 1e9 + 7;
    
    // Precompute powers of BASE
    static vector<long long> computePowers(int maxLen) {
        vector<long long> powers(maxLen + 1);
        powers[0] = 1;
        for (int i = 1; i <= maxLen; i++) {
            powers[i] = (powers[i-1] * BASE) % MOD;
        }
        return powers;
    }
    
    // Get all substrings of given length using rolling hash
    static unordered_set<long long> getHashes(const string& s, int len, const vector<long long>& powers) {
        unordered_set<long long> hashes;
        if (len > s.length()) return hashes;
        
        long long hash = 0;
        // Calculate initial hash
        for (int i = 0; i < len; i++) {
            hash = (hash + (s[i] - 'a' + 1) * powers[len - 1 - i]) % MOD;
        }
        hashes.insert(hash);
        
        // Rolling hash for remaining positions
        for (int i = len; i < s.length(); i++) {
            // Remove leftmost character
            hash = (hash - (s[i - len] - 'a' + 1) * powers[len - 1]) % MOD;
            if (hash < 0) hash += MOD;
            
            // Shift and add new character
            hash = (hash * BASE + (s[i] - 'a' + 1)) % MOD;
            hashes.insert(hash);
        }
        
        return hashes;
    }
    
    // Check if there's a common substring of given length and return it
    static string hasCommonSubstring(const string& s1, const string& s2, int len) {
        if (len == 0) return "";
        
        vector<long long> powers = computePowers(len);
        unordered_set<long long> hashes1 = getHashes(s1, len, powers);
        
        if (hashes1.empty()) return "";
        
        // Check s2 for matching hashes
        if (len > s2.length()) return "";
        
        long long hash = 0;
        // Calculate initial hash for s2
        for (int i = 0; i < len; i++) {
            hash = (hash + (s2[i] - 'a' + 1) * powers[len - 1 - i]) % MOD;
        }
        
        if (hashes1.count(hash)) {
            return s2.substr(0, len);
        }
        
        // Rolling hash for remaining positions in s2
        for (int i = len; i < s2.length(); i++) {
            // Remove leftmost character
            hash = (hash - (s2[i - len] - 'a' + 1) * powers[len - 1]) % MOD;
            if (hash < 0) hash += MOD;
            
            // Shift and add new character
            hash = (hash * BASE + (s2[i] - 'a' + 1)) % MOD;
            
            if (hashes1.count(hash)) {
                return s2.substr(i - len + 1, len);
            }
        }
        
        return "";
    }
    
public:
    static string longestCommonSubstring(string s1, string s2) {
        int n1 = s1.length(), n2 = s2.length();
        int left = 0, right = min(n1, n2);
        string result = "";
        
        while (left <= right) {
            int mid = (left + right) / 2;
            string common = hasCommonSubstring(s1, s2, mid);
            
            if (!common.empty()) {
                result = common;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
};