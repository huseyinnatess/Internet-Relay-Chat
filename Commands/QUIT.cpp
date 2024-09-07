#include "../Server/Server.hpp"

void Server::ClientQuit(int fd)
{
    Client& client = GetClient(fd);
    string nickname = client.GetUsername();
    string message = nickname + ": " + " QUIT";
    
    int size = client.RegisteredChannels.size();

    for (int i = size - 1; i > -1; i--)
    {
        Channel& channel = client.RegisteredChannels[i];
        RemoveChannelRegisteredUser(client, client.RegisteredChannels[i].GetChannelName());
    }
        
    client.RegisteredChannels.clear();

    SendMessage(fd, message);
    SetClosedClientDefaultValue(fd);
}