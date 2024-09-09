#include "../Server/Server.hpp"

void Server::ClientQuit(int fd)
{
    Client& client = GetClient(fd);
    string nickname = client.GetNickname();
    string message = nickname + ": " + " QUIT";
    
    for (int i = CreatedChannels.size() - 1; i > -1; i--)
    {
        if (CheckClientRegistered(fd, CreatedChannels[i].GetChannelName()) != 0)
        {
            Channel& channel = CreatedChannels[i];
            RemoveChannelRegisteredUser(client, channel.GetChannelName());
        }
    }
        
    SendMessage(fd, message);
    SetClosedClientDefaultValue(fd);
}