#include "Messanger.hpp"
#include "Networking.hpp"
#include <iostream>
#include <string>

// Enums & Constants
enum class AppMode 
{
    Listen = 1,
    Connect = 2,
    Exit = 3,
    Invalid
};

const int EXECUTION_ERROR = -1;
const int SUCCESSFUL_EXECUTION = 0;

// Support Functions -
AppMode getUserChoice();
void runServerMode(const std::string& username);
void runClientMode(const std::string& username);

int main() 
{
    std::cout << "Please input your username: ";
    std::string username;
    std::cin >> username;
    std::cin.ignore(); // Cleans Buffer
    std::cout << "Welcome: " << username << std::endl;
    AppMode mode = getUserChoice();

    switch (mode) 
    {
        case AppMode::Listen:
            runServerMode(username);
            break;

        case AppMode::Connect:
            runClientMode(username);
            break;

        case AppMode::Exit:
            std::cout << "Exiting system..." << std::endl;
            return SUCCESSFUL_EXECUTION;

        case AppMode::Invalid:
        default:
            std::cout << "[Error]: Invalid choice selected. Exiting..." << std::endl;
            return EXECUTION_ERROR;
    }

    return SUCCESSFUL_EXECUTION;
}

AppMode getUserChoice() 
{
    std::cout << "\n--- Encrypted Messenger Menu ---" << std::endl;
    std::cout << "[1] Listen - Wait for your peer" << std::endl;
    std::cout << "[2] Connect - Connect to an active peer" << std::endl;
    std::cout << "[3] Exit" << std::endl;
    std::cout << "Enter your choice: ";
    
    int rawChoice;
    std::cin >> rawChoice;
    std::cin.ignore(); // Clean Buffer

    switch (rawChoice) 
    {
        case 1:  return AppMode::Listen;
        case 2:  return AppMode::Connect;
        case 3:  return AppMode::Exit;
        default: return AppMode::Invalid;
    }
}

void runServerMode(const std::string& username) 
{
    Networking networking("0.0.0.0");
    Messanger messanger(username, networking, true);

    std::cout << "[System]: Chat session started as Server. Type 'exit' to quit.\n" << std::endl;
    
    messanger.startChatLoop(); 
}

void runClientMode(const std::string& username) 
{
    std::cout << "Please input the destination IP: ";
    std::string destIPText;
    std::getline(std::cin, destIPText);

    Networking networking(destIPText);
    Messanger messanger(username, networking, false);

    std::cout << "[System]: Chat session started as Client. Type your message and press Enter..." << std::endl;

    messanger.startChatLoop();
}
