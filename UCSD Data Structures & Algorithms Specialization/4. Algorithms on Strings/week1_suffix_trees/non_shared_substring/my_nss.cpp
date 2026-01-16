#include <algorithm>
#include <cstdint>
// #include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
#include <tuple>
// #include <cstddef>

using std::unordered_map;
using std::vector;
using std::string;
// using std::pair;
using std::tuple;
using std::get;
using std::cin;
using std::cout;

using Node = int16_t;
using Label = uint8_t;
using Value = tuple<Node, string, Label>;
using Map = unordered_map<char, Value>;

struct Frame {
  Node node;
  Map::iterator it;
};

auto ShortestNonSharedSubstring(const string& A, const string& B) {
  /// Constructing the suffix tree
  string Text = A + '#' + B + '$';
  vector<Map> sfxtree(Text.size());

  Node new_node = 1;

  for (Node i = 0; i < Text.size(); i++) {
    auto suffix = Text.substr(i);

    Node current_node = 0;
    bool inserted = false;

    do {
      Label current_label = (i < A.size()) ? 1 : 2;
      auto result = sfxtree[current_node].emplace(suffix.front(), std::make_tuple(-1, suffix, current_label));
      auto it = result.first;
      inserted = result.second;


      if (!inserted) {    // First letter match found -> new node will be added somewhere down the line
        auto value = &it->second;
        auto& node_text = get<1>(*value);
        // auto [it1, it2] = std::mismatch(*node_text, suffix);
        auto mm = std::mismatch(node_text.begin(), node_text.end(), suffix.begin(), suffix.end());
        auto it2 = mm.second;

        // auto i = it1 - node_text.begin();
        auto j = it2 - suffix.begin();
        auto nt_tail = node_text.substr(j);
        suffix = suffix.substr(j);
        
        if (j < node_text.size()) {                              // Break current edge and insert new node
          node_text = node_text.substr(0, j);         // Truncating string of current node

          sfxtree[new_node].insert({nt_tail.front(), std::make_tuple(get<0>(*value), nt_tail, get<2>(*value))});   // NOTE: Preserve the tail branches
          sfxtree[new_node].insert({suffix.front(), std::make_tuple(-1, suffix, current_label)});

          get<0>(*value) = new_node++;                         // Setting next-node value of current node
          get<2>(*value) |= current_label;                     // Setting label value of current node
          inserted = true;
        }
        else {
          current_node = get<0>(*value);
        }
      }
    } while (!inserted);
  }


  // Finding the shortest non-shared substring
  string answer = "";
  // vector<Node> path;

  vector<Frame> stack;

  Node root = 0;
  stack.push_back({root, sfxtree[root].begin()});

  while (!stack.empty()) {
    auto& top = stack.back();
    Node u = top.node;


    if (top.it != sfxtree[u].end()) {   // TODO: Process in a way to not take edges exclusive to B
      // Take next edge
      auto& edge = top.it->second;
      Node v = get<0>(edge);

      top.it++;

      // Go down
      if (get<2>(edge) == 3) {
        stack.push_back({v, sfxtree[v].begin()});
      }

    }
    else {
      // All children done -> backtrack
      stack.pop_back();
    }
  }


  return answer;
}

int main() {
  string A, B;
  std::getline(cin, A);
  std::getline(cin, B);

  cout << ShortestNonSharedSubstring(A, B) << "\n";

  return EXIT_SUCCESS;
}