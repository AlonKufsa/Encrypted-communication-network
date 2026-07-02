#pragma once

#include <kissnet/kissnet.hpp>
#include <string>
#include <cstddef>
#include <thread>

class Networking
{
private:
    // Local Constants - 
    static constexpr std::size_t bufferSize = 4096;
    static constexpr uint16_t defaultPort = 8080;

    // Attributes - 
    kissnet::tcp_socket _socket;
    kissnet::buffer<bufferSize> _buffer;
    uint16_t _port;
    std::thread _receiveThread;

    // Support Methods - 
    bool isValidIP(const std::string& endpoint) const;
    bool isValidPort(const uint16_t port) const;
    void receiveLoop(kissnet::tcp_socket& activeSocket);

public:
    // Constructor & Destructor - 
    Networking(const std::string& endpoint, const uint16_t port = defaultPort);
    ~Networking();

    // Communication Methods - 
    void listen();
    void connect();
    void send(const std::string& message);
};