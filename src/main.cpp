#include "Networking.hpp"
#include <iostream>
int main() {
    std::cout << "Please input the destination ip:" << std::endl;

    std::string destIPText;
    std::cin >> destIPText;

    Networking networking(destIPText);

    return 0;
}