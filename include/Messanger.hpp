#pragma once

#include "Networking.hpp"
#include <string>
#include <thread>

class Messanger {
private:
    const std::string& username;
    Networking& networking;

    std::thread inputThread;

    void displayText(const std::string& text);
    void displayMessage(const std::string& senderUsername, const std::string& message);

    void sendMessage(const std::string& message);

    void listenForInput();
public:
    Messanger(const std::string& username, Networking& networking);
};