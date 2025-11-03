#include <algorithm>
#include <ranges>
#include <iostream>
#include <vector>
#include <queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = NULL;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};

int Find_Tree_Height_Iterative(Node* root) {
    if (!root) return 0;
    
    std::queue<Node*> q;
    q.push(root);
    int height = 0;
    
    while (!q.empty()) {
        int level_size = q.size();
        height++;
        
        // Process all nodes at current level
        for (int i = 0; i < level_size; i++) {
            Node* current = q.front();
            q.pop();
            
            // Add all children to queue for next level
            for (Node* child : current->children) {
                q.push(child);
            }
        }
    }
    
    return height;
}

int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;

  std::vector<Node> nodes;
  Node* root = nullptr;
  nodes.resize(n);
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    else
      root = &nodes[child_index];
    nodes[child_index].key = child_index;
  }

  std::cout << Find_Tree_Height_Iterative(root);
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}