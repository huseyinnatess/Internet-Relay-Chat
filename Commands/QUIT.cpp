#include "../Server/Server.hpp"

void Server::ClientQuit(int fd)
{
    Client& client = GetClient(fd);
    string nickname = client.GetUsername();
    string message = nickname + ": " + " QUIT";
    
    for (size_t i = 0; i < client.RegisteredChannels.size(); i++)
    {
        RemoveChannelFromClient(fd, client.RegisteredChannels[i].GetChannelName());
    }
    SendMessage(fd, message);
    SetClosedClientDefaultValue(fd);
}