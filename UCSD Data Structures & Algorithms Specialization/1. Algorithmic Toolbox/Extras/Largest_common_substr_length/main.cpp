#include "claude.hpp"
#include "chatgpt.hpp"

string MyLongestCommonSubstr(string s, string l) {
    if (s.empty() || l.empty()) return "";

    if (s.size() > l.size()) swap(s, l);

    string substr, max_substr = "";
    // size_t max_len;

    for (size_t i = 0; s.size() - i > max_substr.size(); i++) {
        for (size_t substr_len = max_substr.size() + 1; i + substr_len <= s.size(); substr_len++) {
            substr = s.substr(i, substr_len);

            if (l.find(substr) == string::npos) break;

            max_substr = substr;
        }
    }

    return max_substr;
}

// Generates a random string of random length (1 to maxLen)
string randomString(mt19937& rng, int maxLen = 100) {
    static const string charset = "abcdefghijklmnopqrstuvwxyz"
                                  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                  "0123456789";

    uniform_int_distribution<int> lenDist(1, maxLen);
    uniform_int_distribution<int> charDist(0, charset.size() - 1);

    int len = lenDist(rng);
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s += charset[charDist(rng)];
    }
    return s;
}

void test(string (*func)(string, string), vector<string>& test_strings, vector<size_t>& max_lens) {
    string longest_substr;
    const auto t1 = chrono::high_resolution_clock::now();

    for (size_t i = 0; i < test_strings.size() - 1; i++) {
        for (size_t j = i + 1; j < test_strings.size(); j++) {
            longest_substr = func(test_strings[i], test_strings[j]);
            max_lens.push_back(longest_substr.size());
        }
    }

    const auto t2 = chrono::high_resolution_clock::now();
    cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << endl;
}


int main() {
    const int numStrings = 5;
    vector<string> test_strings;
    test_strings.reserve(numStrings);

    mt19937 rng(random_device{}());
    vector<size_t> max_lens1, max_lens2;

    for (int i = 0; i < numStrings; ++i) {
        test_strings.push_back(randomString(rng, 100000));
    }

    // TEST 1
    cout << "Testing my function:\n";
    test(MyLongestCommonSubstr, test_strings, max_lens1);

    // TEST 2
    cout << "Testing AI function:\n";
    test(GPTLongestCommonSubstring, test_strings, max_lens2);

    // Equivalence test
    // cout << ranges::equal(max_lens1, max_lens2) ? "Equivalent" : "NOT Equivalent!";
    if (max_lens1 == max_lens2) cout << "Equivalent";
    else {
        cout << "NOT Equivalent!\n\n\n";

        size_t k = 0;
        for (size_t i = 0; i < test_strings.size() - 1; i++) {
            for (size_t j = i + 1; j < test_strings.size(); j++, k++) {
                if (max_lens1[k] != max_lens2[k]) {
                    cout << test_strings[i] << " vs. " << test_strings[j] << "\n";
                    cout << "Test 1 Result: " << max_lens1[k] << "\n";
                    cout << "Test 2 Result: " << max_lens2[k] << "\n\n";
                }
            }
        }
        // ranges::for_each(max_lens1, [](const auto &elem) { cout << elem << " "; });
        // cout << "\n\n\n";
        // ranges::for_each(max_lens2, [](const auto &elem) { cout << elem << " "; });
        // cout << "\n\n\n";
    }

    return 0;
}