#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
// #include <ostream>
#include <string>
#include <vector>

using std::cin;
// using std::cout;
// using std::endl;
using std::string;
using std::vector;
using std::max;

int main () {
    string bwt;
    cin >> bwt;

    string firstcol = bwt;
    std::sort(firstcol.begin(), firstcol.end());

    for (size_t i = 0; i < bwt.size(); i++) printf("%c%c\n", firstcol[i], bwt[i]);

    return 0;
}