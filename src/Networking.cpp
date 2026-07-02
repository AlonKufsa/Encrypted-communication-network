#include <Networking.hpp>

#include <regex>
#include <iostream>

// Constants - 
const std::regex ipv4Pattern(R"(^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$)");

// Public Methods Implementations - 
Networking::Networking(const std::string& endpoint, const uint16_t port) : _port(isValidPort(port) ? port : defaultPort)
{
    if (!isValidIP(endpoint))
    {
        throw std::runtime_error("[Fatal Error]: Invalid IPv4 Address specified.");
    }

    this->_socket = kissnet::tcp_socket(kissnet::endpoint(endpoint, _port));
    std::cout << "[Networking]: Socket initialized successfully on " << endpoint << ":" << _port << std::endl;
}

Networking::~Networking()
{
    if (this->_receiveThread.joinable())
    {
        this->_receiveThread.join(); 
    }
}

void Networking::listen()
{
    try 
    {
        this->_socket.bind();
        this->_socket.listen();
        std::cout << "[Networking]:  Listening on port " << _port << ". Waiting for peer..." << std::endl;

        auto clientSocket = this->_socket.accept();
        std::cout << "[Networking]: Peer connected successfully!" << std::endl;

        this->_socket = std::move(clientSocket);
        this->_receiveThread = std::thread(&Networking::receiveLoop, this, std::ref(this->_socket));
    }

    catch (const std::exception& e)
    {
        throw std::runtime_error(std::string("[Listening Error]: ") + e.what());
    }
}

void Networking::connect()
{
    try 
    {
        std::cout << "[Networking]: Attempting to connect to peer..." << std::endl;
        this->_socket.connect();
        std::cout << "[Networking]: Connected to peer successfully!" << std::endl;

        this->_receiveThread = std::thread(&Networking::receiveLoop, this, std::ref(_socket));
    }

    catch (const std::exception& e)
    {
        throw std::runtime_error(std::string("[Connection Error]: ") + e.what());
    }
}

void Networking::send(const std::string& message)
{
    if (message.empty()) return;

    // TODO: Encryption

    auto [bytes_sent, status] = _socket.send(reinterpret_cast<const std::byte*>(message.data()), message.size());

    if (status != kissnet::socket_status::valid)
    {
        std::cerr << "[Networking Error]: Failed to send message." << std::endl;
    }
}

// Support Methods Implementations - 
bool Networking::isValidIP(const std::string& endpoint) const
{
    return std::regex_match(endpoint, ipv4Pattern);
}

bool Networking::isValidPort(const uint16_t port) const
{
    const uint16_t MIN_PORT = 1024, MAX_PORT = 65535;
    return (port >= MIN_PORT && port <= MAX_PORT);
}

void Networking::receiveLoop(kissnet::tcp_socket& activeSocket)
{
    while (true)
    {
        auto [bytes_received, status] = activeSocket.recv(_buffer);

        if ((bytes_received == 0) || (status != kissnet::socket_status::valid))
        {
            std::cout << "\n[Networking]: Connection lost or peer disconnected." << std::endl;
            break;
        }

        std::string received_msg(reinterpret_cast<const char*>(_buffer.data()), bytes_received);
        
        std::cout << "\n[Peer]: " << received_msg << std::endl;
        std::cout << "> " << std::flush;
    }
}