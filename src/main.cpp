#include "Messanger.hpp"
#include "Networking.hpp"
#include <iostream>
#include <string>

enum class AppMode 
{
    Listen = 1,
    Connect = 2,
    Exit = 3,
    Invalid
};

const int EXECUTION_ERROR = -1, SUCCEESFULL_EXECUTION = 0;

int main() {
    std::cout << "Please input your username:" << std::endl;
    std::string username;
    std::cin >> username;

    std::cout << "\n--- Encrypted Messenger Menu ---" << std::endl;
    std::cout << "[1] Listen - Wait for your peer" << std::endl;
    std::cout << "[2] Connect - Connect to an active peer" << std::endl;
    std::cout << "[3] Exit" << std::endl;
    std::cout << "Enter your choice: ";
    
    int rawChoice;
    std::cin >> rawChoice;
    std::cin.ignore(); // Clean Buffer

    AppMode mode;
    switch (rawChoice) 
    {
        case 1:  mode = AppMode::Listen;  break;
        case 2:  mode = AppMode::Connect; break;
        case 3:  mode = AppMode::Exit;    break;
        default: mode = AppMode::Invalid; break;
    }

    switch (mode) 
    {
        case AppMode::Listen: {
            Networking networking("0.0.0.0");
            Messanger messanger(username, networking, true);

            std::cout << "[System]: Chat session started as Server. Type your message and press Enter..." << std::endl;
            
            std::string dummy;
            std::getline(std::cin, dummy);
            break;
        }

        case AppMode::Connect: {
            std::cout << "Please input the destination IP: ";
            std::string destIPText;
            std::getline(std::cin, destIPText);

            Networking networking(destIPText);
            Messanger messanger(username, networking, false);

            std::cout << "[System]: Chat session started as Client. Type your message and press Enter..." << std::endl;

            std::string dummy;
            std::getline(std::cin, dummy);
            break;
        }

        case AppMode::Exit:
            std::cout << "Exiting system..." << std::endl;
            return SUCCEESFULL_EXECUTION;

        case AppMode::Invalid:
        default:
            std::cout << "[Error]: Invalid choice selected. Exiting..." << std::endl;
            return EXECUTION_ERROR;
    }

    return SUCCEESFULL_EXECUTION;
}