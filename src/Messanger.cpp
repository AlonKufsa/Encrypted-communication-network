#include <Messanger.hpp>
#include <iostream>

Messanger::Messanger() {

}

void Messanger::displayText(const std::string message) {
    std::cout << message << std::endl;
}