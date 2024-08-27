#include <sys/socket.h> //-> for send()
#include "../Server/Server.hpp"

void Server::SendError(int fd, string errorMesssage, int clientCloseFlag)
{
    if (send(fd, errorMesssage.c_str(), errorMesssage.size(), 0) == -1)
        std::cerr << "Error: send() failed" << std::endl;
    if (clientCloseFlag)
    {
        SetClosedClientDefaultValue(fd);
    }
}

void Server::SendMessage(int fd, string message)
{
    if (send(fd, message.c_str(), message.size(), 0) == -1)
        std::cerr << "Error: send() failed" << std::endl;
}

void Server::SendAllClientsMessage(std::vector<int> fds, string message)
{
    for (size_t i = 0; i < fds.size(); i++)
    {
        if (send(fds[i], message.c_str(), message.size(), 0) == -1)
            std::cerr << "Error: send() failed" << std::endl;
    }
}