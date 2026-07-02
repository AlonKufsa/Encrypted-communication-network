#include "Networking.hpp"
#include <Messanger.hpp>
#include <exception>
#include <iostream>
#include <thread>

Messanger::Messanger(const std::string& usernameValue, Networking& networkingValue, const bool isServer) : username(usernameValue), networking(networkingValue) 
{
    isServer ? networking.listen() : networking.connect();
    inputThread = std::thread(&Messanger::listenForInput, this);
}

Messanger::~Messanger() 
{
    if (inputThread.joinable()) 
    {
        inputThread.join();
    }
}

void Messanger::displayText(const std::string& text) {
    std::cout << text << std::endl;
}

void Messanger::displayMessage(const std::string& senderUsername, const std::string& message) {
    displayText(senderUsername + ": " + message);
}

void Messanger::sendMessage(const std::string& message) {
    networking.send(username + ": " + message);
}

void Messanger::listenForInput() {
    while (true) {
        try {
            std::string message;
            std::cout << "> " << std::flush;
            
            std::getline(std::cin, message); 
            
            if (message == "exit") break;

            if (!message.empty()) 
            {
                sendMessage(message);
            }
        } 

        catch(const std::exception& e) 
        {
            std::cerr << "[Input error]: " << e.what() << std::endl;
            break;
        }
    }
}