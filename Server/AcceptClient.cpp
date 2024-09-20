#include "Server.hpp"

void SetClientRandomColor(Client &client);

void Server::AcceptNewClient()
{
    Client client;
    struct sockaddr_in clientAddr;
    struct pollfd pollFd;
    socklen_t clientAddrSize = sizeof(clientAddr);

    int acceptedFd = accept(_socketFd, (struct sockaddr *)&clientAddr, &clientAddrSize);
    if (acceptedFd == -1)
    {
        print("accept failed", RED);
        return;
    }

    if (fcntl(acceptedFd, F_SETFL, O_NONBLOCK) == -1)
    {
        print("fcntl failed", RED);
        return;
    }
    
    client.SetFd(acceptedFd);
    client.SetIpAddress(inet_ntoa(clientAddr.sin_addr));
    SetClientRandomColor(client);
    Clients.push_back(client);
    
    pollFd.fd = acceptedFd;
    pollFd.events = POLLIN;
    pollFd.revents = 0;

    _pollFds.push_back(pollFd);
    print(client.GetNickname() + " connected", client.GetClientColor());
}

void SetClientRandomColor(Client &client)
{
    string clientColor = "\033[";
    clientColor += ConvertToString(31 + client.GetFd() % 6);
    clientColor += "m";
    client.SetClientColor(clientColor);
}