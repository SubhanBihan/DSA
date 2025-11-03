#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    unordered_map<string, string> phonebook;

    for (int i = 0; i < N; i++) {
        string cmd;
        cin >> cmd;

        if (cmd == "add") {
            string number, name;
            cin >> number >> name;
            phonebook[number] = name; // add or overwrite
        } 
        else if (cmd == "del") {
            string number;
            cin >> number;
            phonebook.erase(number); // erase if exists
        } 
        else if (cmd == "find") {
            string number;
            cin >> number;
            if (phonebook.find(number) != phonebook.end())
                cout << phonebook[number] << "\n";
            else
                cout << "not found\n";
        }
    }
    return 0;
}
