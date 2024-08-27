#include "../Server/Server.hpp"

void Server::ClientQuit(int fd)
{
    Client& client = GetClient(fd);
    string nickname = client.GetUsername();
    string message = nickname + ": " + " QUIT";
    
    SendError(fd, message, 1);
}