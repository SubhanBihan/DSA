#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string T, P;

    std::cin >> P;
    std::cin >> T;

    std::vector<size_t> positions;
    size_t pos = T.find(P); // first match
    while (pos != std::string::npos) {
        positions.push_back(pos);
        pos = T.find(P, pos + 1); // search from next character
    }

    for (size_t p : positions) {
        std::cout << p << " ";
    }
}
