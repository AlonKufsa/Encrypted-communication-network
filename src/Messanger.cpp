#include <Messanger.hpp>
#include <iostream>

Messanger::Messanger() {

}

void Messanger::displayText(const std::string text) {
    std::cout << text << std::endl;
}

void Messanger::displayMessage(const std::string senderUsername, const std::string message) {
    displayText(senderUsername + ": " + message);
}

void Messanger::sendMessage(const std::string message) {
    
}