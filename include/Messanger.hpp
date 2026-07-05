#pragma once

#include "Networking.hpp"
#include <string>

class Messanger {
private:
    const std::string username; 
    Networking& networking;

public:
    Messanger(const std::string& username, Networking& networking, const bool isServer);

    void startChatLoop();
    void displayText(const std::string& text);
    void displayMessage(const std::string& senderUsername, const std::string& message);
};