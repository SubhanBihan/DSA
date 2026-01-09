#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
#include <ranges>
#include <cstddef>
// #include <chrono>

using std::unordered_map;
using std::vector;
using std::string;
using std::pair;
using std::cin;
using std::views::iota;

using Node = uint32_t;
using Key = pair<Node, char>;
using Value = pair<Node, bool>;

struct KeyHash {
    std::size_t operator()(const Key& k) const noexcept {
        return (static_cast<std::size_t>(k.first) << 8)
             ^ static_cast<unsigned char>(k.second);
    }
};

auto TrieConstruct(const vector<string>& patterns) {
  unordered_map<Key, Value, KeyHash> trie;
  Node new_node = 1;
  Key key;

  for (const auto& pattern: patterns) {
    key.first = 0;

    for (auto it = pattern.begin(); it != pattern.end(); ++it) {
      key.second = *it;
      bool is_last = (std::next(it) == pattern.end());

      auto [entry, inserted] = trie.try_emplace(key, std::make_pair(new_node, is_last));

      if (inserted) {
          key.first = new_node++;
      } else {
          key.first = entry->second.first;
      }
    }
  }

  return trie;
}

auto TrieMatch(const string& Text, const vector<string>& patterns) {
  vector<Node> matches;   matches.reserve(Text.size());

  const auto trie = TrieConstruct(patterns);

  for (Node start = 0; start < Text.size(); start++) {
    for (Node end = 0; end < Text.size(); end++) {

    }
  }

  return matches;
}

int main() {
  int n;
  cin >> n;
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  vector<string> patterns;  patterns.reserve(n);
  for (auto _ : iota(0, n)) {
    string s;
    getline(cin, s);
    patterns.push_back(std::move(s));
  }

  auto trie = TrieConstruct(patterns);
  for (const auto& [key, value]: trie) {
    printf("%d->%d:%c\n", key.first, value, key.second);
  }

  return EXIT_SUCCESS;
}