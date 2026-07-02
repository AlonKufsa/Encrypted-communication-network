#include "Messanger.hpp"
#include "Networking.hpp"
#include <iostream>
int main() {
    std::cout << "Please input the destination ip:" << std::endl;

    std::string destIPText;
    std::cin >> destIPText;

    Networking networking(destIPText);

    std::cout << "Please input your username:" << std::endl;

    std::string username;
    std::cin >> username;

    Messanger Messanger(username, networking);

    bool shouldQuit = false;

    while (!shouldQuit) {
        
    }

    return 0;
}