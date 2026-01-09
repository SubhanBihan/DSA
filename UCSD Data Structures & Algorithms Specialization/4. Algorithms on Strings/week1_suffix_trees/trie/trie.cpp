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

using Node = uint16_t;
using Key = pair<Node, char>;

struct KeyHash {
    std::size_t operator()(const Key& k) const noexcept {
        return (static_cast<std::size_t>(k.first) << 8)
             ^ static_cast<unsigned char>(k.second);
    }
};

auto TrieConstruct(const vector<string>& patterns) {
  unordered_map<Key, Node, KeyHash> trie;
  Node new_node = 1;
  Key key;

  for (const auto& pattern: patterns) {
    key.first = 0;

    for (const auto c: pattern) {
      key.second = c;

      auto [it, inserted] = trie.try_emplace(key, new_node);

      if (inserted) {
          key.first = new_node++;
      } else {
          key.first = it->second;
      }
    }
  }

  return trie;
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

  // constexpr int ITER = 1000;

  // auto start = std::chrono::high_resolution_clock::now();
  // for (int i = 0; i < ITER; ++i) {
  auto trie = TrieConstruct(patterns);
  for (const auto& [key, value]: trie) {
    printf("%d->%d:%c\n", key.first, value, key.second);
  }
  // }

  // auto end = std::chrono::high_resolution_clock::now();

  // std::chrono::duration<double> total = end - start;
  // printf("Average time: %f seconds\n", (total.count() / ITER));

  return EXIT_SUCCESS;
}