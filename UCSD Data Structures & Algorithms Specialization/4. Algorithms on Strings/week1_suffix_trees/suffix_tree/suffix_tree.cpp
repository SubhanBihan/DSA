#include <algorithm>
#include <cstdint>
// #include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
// #include <ranges>
// #include <cstddef>
// #include <chrono>

using std::unordered_map;
using std::vector;
using std::string;
using std::pair;
using std::cin;
using std::cout;
// using std::views::iota;

using Node = int16_t;
using Value = pair<Node, string>;
using Map = unordered_map<char, Value>;

auto SuffixTree(const string& Text) {
  vector<Map> sfxtree(Text.size());
  Node new_node = 1;

  for (Node i = 0; i < Text.size(); i++) {
    auto suffix = Text.substr(i);

    Node current_node = 0;
    bool inserted = false;

    do {
      // auto [it, ins] = sfxtree[current_node].try_emplace(suffix.front(), std::make_pair(-1, suffix));
      // inserted = ins;

      auto result = sfxtree[current_node].emplace(suffix.front(), std::make_pair(-1, suffix));
      auto it = result.first;
      inserted = result.second;


      if (!inserted) {    // First letter match found -> new node will be added somewhere down the line
        auto value = &it->second;
        auto node_text = &it->second.second;
        // auto [it1, it2] = std::mismatch(*node_text, suffix);
        auto mm = std::mismatch(node_text->begin(), node_text->end(), suffix.begin(), suffix.end());
        auto it2 = mm.second;

        // auto i = it1 - node_text->begin();
        auto j = it2 - suffix.begin();
        auto nt_tail = node_text->substr(j);
        suffix = suffix.substr(j);
        
        if (j < node_text->size()) {                         // Break current edge and insert new node
          *node_text = node_text->substr(0, j);   // Truncating string of current node

          sfxtree[new_node].insert({nt_tail.front(), std::make_pair(value->first, nt_tail)});   // NOTE: Preserve the tail branches
          sfxtree[new_node].insert({suffix.front(), std::make_pair(-1, suffix)});
          value->first = new_node++;                         // Setting next-node value of current node

          inserted = true;
        }
        else {
          current_node = value->first;
        }
      }
    } while (!inserted);
  }

  return sfxtree;
}

int main() {
  string Text;
  getline(cin, Text);

  auto sfxtree = SuffixTree(Text);

  for (auto& nodes: sfxtree) {
    if (!nodes.empty())
      for (auto& el: nodes) {
        // printf("%s", value.second.c_str());
        cout << el.second.second << "\n";
      }
  }

  return EXIT_SUCCESS;
}