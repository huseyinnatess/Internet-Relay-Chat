#include "Server.hpp"

void Server::SetClosedClientDefaultValue(int fd)
{
    Client &client = GetClient(fd);

    client.RegisteredChannels.clear();
    ClearClients(fd);
    close(fd);
}

void Server::CloseFds()
{
    for (size_t i = 0; i < Clients.size(); i++)
    {
        if (Clients[i].GetFd() != _socketFd)
        {
            print(Clients[i].GetNickname() + " disconnected", RED);
            close(Clients[i].GetFd());
        }
    }
    if (_socketFd != -1)
    {
        print("Server socket closed", YELLOW);
        close(_socketFd);
    }
}

void Server::ClearClients(int fd)
{
    for (size_t i = 0; i < _pollFds.size(); i++)
    {
        if (_pollFds[i].fd == fd)
        {
            _pollFds.erase(_pollFds.begin() + i);
            break;
        }
    }
    for (size_t i = 0; i < Clients.size(); i++)
    {
        if (Clients[i].GetFd() == fd)
        {
            Clients.erase(Clients.begin() + i);
            break;
        }
    }
}