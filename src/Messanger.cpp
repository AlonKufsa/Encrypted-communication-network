#include "Networking.hpp"
#include <Messanger.hpp>
#include <exception>
#include <iostream>
#include <thread>

Messanger::Messanger(const std::string& usernameValue, Networking& networkingValue): username(usernameValue), networking(networkingValue) {
    

    networking.connect();
    networking.listen();

    inputThread = std::thread(&Messanger::listenForInput, this);
}

void Messanger::displayText(const std::string& text) {
std::cout << text << std::endl;
}

void Messanger::displayMessage(const std::string& senderUsername, const std::string& message) {
    displayText(senderUsername + ": " + message);
}

void Messanger::sendMessage(const std::string& message) {
    networking.send(message);
}

void Messanger::listenForInput() {
    while (true) {
        try {
            std::string message;
            std::cin >> message;
            sendMessage(message);
        } catch(const std::exception e) {
            throw std::runtime_error(std::string("[Input error]: ") + e.what());
        }
    }
}