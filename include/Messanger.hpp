#pragma once

#include <string>

class Messanger {
public:
    Messanger();

    void displayText(const std::string text);
    void displayMessage(const std::string senderUsername, const std::string message);

    void sendMessage(const std::string message);
};