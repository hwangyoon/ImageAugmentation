#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;

int main() {
    string command;
    // TODO: Узнать, что конкретно надо в интерфейсе, и написать это
    while (true) {
        cin >> command;
        if (command == "exit")
            break;
        if (command == "Hi") {
            cout << "Hello!!!! \nI'm really glad to meet you!\n";
            continue;
        }
    }
    return 0;
}