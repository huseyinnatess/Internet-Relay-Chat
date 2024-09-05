#include "../Server/Server.hpp"

void Server::ClientCap(int fd, vector<string> command)
{
    Client &client = GetClient(fd);

    if (command[1] == "LS")
        client.SetConnectionType(HEXCHAT);
    else
        client.SetConnectionType(NC);
}