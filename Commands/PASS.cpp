#include "../Server/Server.hpp"

void Server::ClientAutherization(int fd, std::vector<string> command)
{
    Client &client = GetClient(fd);
    string password = command[1];
    
    if (password == _password)
    {
        client.SetRegistered(true);
    }
    else
    {
        SendError(fd, ERR_PASSWDMISMATCH, 1);
    }

}