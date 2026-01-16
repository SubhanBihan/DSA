#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
#include <cstddef>
#include <limits>
// #include <chrono>

using std::unordered_map;
using std::vector;
using std::string;
using std::pair;
using std::cin;

using Node = uint32_t;
using Key = pair<Node, char>;		// (current_node, symbol)
using Value = pair<Node, bool>;		// (next_node, is_endnode)

struct KeyHash {
    std::size_t operator()(const Key& k) const noexcept {
        return (static_cast<std::size_t>(k.first) << 8)
             | static_cast<unsigned char>(k.second);
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

      auto entry = trie.find(key);
      if (entry == trie.end()) {
          trie[key] = std::make_pair(new_node, is_last);
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
//   bool is_endnode = false;
  Key key;

  for (Node start = 0; start < Text.size(); start++) {
	key.first = 0;
    for (Node end = start; end < Text.size(); end++) {
		key.second = Text[end];

		auto it= trie.find(key);

		if (it != trie.end()) {				// Matching next node found 	-> move to it
			if (it->second.second) {		// Next node is a trie end-node -> match found, move to next Text suffix (condition: p_i not a prefix of p_j)
				matches.push_back(start);
				break;
			}

			key.first = it->second.first;
		}
		else {								// Next nodes do not match 		-> move to next Text suffix
			break;
		}
    }
  }

  return matches;
}

int main() {
  string Text;
  getline(cin, Text);

  int n;
  cin >> n;
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  vector<string> patterns;  patterns.reserve(n);
  for (auto i = 0; i < n; i++) {
    string s;
    getline(cin, s);
    patterns.push_back(std::move(s));
  }

  auto matches = TrieMatch(Text, patterns);

  if (!matches.empty()) {
	for (auto i = 0; i < matches.size() - 1; i++) printf("%d ", matches[i]);

	printf("%d", matches.back());
  }

  return EXIT_SUCCESS;
}