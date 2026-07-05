#include "Networking.hpp"
#include <Messanger.hpp>
#include <exception>
#include <iostream>
#include <thread>

Messanger::Messanger(const std::string& usernameValue, Networking& networkingValue, const bool isServer) : username(usernameValue), networking(networkingValue) 
{
    networking.setOnMessageReceived([this](const std::string& msg) {
        std::cout << "\n" << msg << std::endl;
        std::cout << "> " << std::flush;
    });

    isServer ? networking.listen() : networking.connect();
}

void Messanger::displayText(const std::string& text) {
    std::cout << text << std::endl;
}

void Messanger::displayMessage(const std::string& senderUsername, const std::string& message) {
    displayText(senderUsername + ": " + message);
}

void Messanger::startChatLoop() {
    const std::string STOP_CHATTING = "exit";

    while (true) {
        std::string message;
        std::cout << "> " << std::flush;
        std::getline(std::cin, message);
        
        if (message == STOP_CHATTING) {
            break;
        }

        if (!message.empty()) {
            std::string formattedMessage = username + ": " + message;
            networking.send(formattedMessage);
            displayText(formattedMessage);
        }
    }
}