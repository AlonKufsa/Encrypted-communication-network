#pragma once
#include <kissnet/kissnet.hpp>
#include <string>

class Networking {
private:
    kissnet::tcp_socket socket;
    kissnet::buffer<4096> buffer;
public:
    Networking(const std::string& endpoint);
    void listen();
    void send(const std::string& message);
};