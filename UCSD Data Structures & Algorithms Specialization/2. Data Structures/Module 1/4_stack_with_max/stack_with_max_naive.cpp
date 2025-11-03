#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

class StackWithMax {
private:
    std::stack<int> main_stack;
    std::stack<int> max_stack;

public:
    void push(int value) {
        main_stack.push(value);
        
        if (max_stack.empty() || value >= max_stack.top()) {
            max_stack.push(value);
        }
    }
    
    void pop() {
        if (!main_stack.empty()) {
            if (main_stack.top() == max_stack.top()) {
                max_stack.pop();
            }
            main_stack.pop();
        }
    }
    
    int max() {
        return max_stack.top();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int q;
    std::cin >> q;
    
    StackWithMax stack;
    
    for (int i = 0; i < q; i++) {
        std::string operation;
        std::cin >> operation;
        
        if (operation == "push") {
            int value;
            std::cin >> value;
            stack.push(value);
        } else if (operation == "pop") {
            stack.pop();
        } else if (operation == "max") {
            std::cout << stack.max() << "\n";
        }
    }
    
    return 0;
}