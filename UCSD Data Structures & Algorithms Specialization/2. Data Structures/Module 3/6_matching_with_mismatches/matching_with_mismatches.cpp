#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <complex>
#include <cmath>

// Fast I/O for performance
void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
}

using cd = std::complex<double>;
const double PI = acos(-1.0);

// Optimized FFT implementation
void fft(std::vector<cd>& a, bool invert) {
    int n = a.size();
    if (n <= 1) return;

    // Bit-reversal permutation
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            std::swap(a[i], a[j]);
    }

    // Cooley-Tukey FFT algorithm
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j];
                cd v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd& x : a)
            x /= n;
    }
}

void solve() {
    int k;
    std::string t, p;

    while (std::cin >> k >> t >> p) {
        int n = t.length();
        int m = p.length();

        if (m > n) {
            std::cout << 0 << "\n";
            continue;
        }

        int limit = 1;
        while (limit < n + m) { // FFT size must be power of 2 >= n+m
             limit <<= 1;
        }

        std::vector<long long> match_counts(n - m + 1, 0);
        std::string p_rev = p;
        std::reverse(p_rev.begin(), p_rev.end());

        // Process characters in pairs to halve the number of FFTs
        for (int i = 0; i < 26; i += 2) {
            char ch1 = 'a' + i;
            char ch2 = 'a' + i + 1;

            std::vector<cd> ft(limit, {0, 0}), fp(limit, {0, 0});
            
            // Pack two characters into one complex polynomial using the trick
            // P(x) = P_ch1(x) + i * P_ch2(x)
            // T(x) = T_ch1(x) - i * T_ch2(x)
            for (int j = 0; j < n; ++j) {
                if (t[j] == ch1) ft[j].real(1);
                else if (j < n && t[j] == ch2) ft[j].imag(-1); // Note the negative sign
            }
            for (int j = 0; j < m; ++j) {
                if (p_rev[j] == ch1) fp[j].real(1);
                else if (j < m && p_rev[j] == ch2) fp[j].imag(1);
            }

            fft(ft, false);
            fft(fp, false);

            for (int j = 0; j < limit; ++j) {
                ft[j] *= fp[j];
            }
            fft(ft, true);

            // The real part of the convolution gives the sum of matches for ch1 and ch2
            for (int j = 0; j <= n - m; ++j) {
                match_counts[j] += round(ft[m - 1 + j].real());
            }
        }

        std::vector<int> result_indices;
        for (int i = 0; i <= n - m; ++i) {
            if (m - match_counts[i] <= k) {
                result_indices.push_back(i);
            }
        }
        
        std::cout << result_indices.size();
        for (int idx : result_indices) {
            std::cout << " " << idx;
        }
        std::cout << "\n";
    }
}

int main() {
    fast_io();
    solve();
    return 0;
}