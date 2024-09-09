#include "Server.hpp"

void Server::ServerCreateSocket()
{
    struct sockaddr_in serverAddr;
    struct pollfd poolFd;

    _socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (_socketFd < 0)
        throw std::runtime_error("Error creating socket");

    serverAddr.sin_family = AF_INET; // IPv4
    serverAddr.sin_port = htons(_port); // Port
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Any IP address

    ConfigureSocket(_socketFd, serverAddr);
   
    poolFd.fd = _socketFd;
    poolFd.events = POLLIN; // POLLIN: There is data to read
    poolFd.revents = 0; // Return events

    _pollFds.push_back(poolFd); // Add the server socket to the poll list
}

void Server::ConfigureSocket(int _socketFd, struct sockaddr_in serverAddr)
{
     int reuseAddrFlag = 1;
    if (setsockopt(_socketFd, 0xffff, SO_REUSEADDR, &reuseAddrFlag, sizeof(reuseAddrFlag)) < 0) // Reuse the port if the server crashes
        throw std::runtime_error("Error setting socket options");
    if (fcntl(_socketFd, F_SETFL, O_NONBLOCK) < 0) // Set the socket to non-blocking
        throw std::runtime_error("Error setting socket to non-blocking");
    if (bind(_socketFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) // Bind the socket to the address
        throw std::runtime_error("Error binding socket");
    if (listen(_socketFd, SOMAXCONN) < 0) // Listen for incoming connections
        throw std::runtime_error("Error listening on socket");
   
}
