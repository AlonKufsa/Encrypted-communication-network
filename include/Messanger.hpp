#pragma once

#include "Networking.hpp"
#include <string>

class Messanger {
private:
    const std::string& username;
    Networking& networking;
public:
    Messanger(const std::string& username, Networking& networking);

    void displayText(const std::string& text);
    void displayMessage(const std::string& senderUsername, const std::string& message);

    void sendMessage(const std::string& message);
};