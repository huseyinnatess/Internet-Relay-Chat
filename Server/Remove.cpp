#include "Server.hpp"

void Server::RemoveChannel(int fd, int channelIndex, string clientNickname)
{
    SendMessage(fd, RPL_PART(clientNickname, CreatedChannels[channelIndex].GetChannelName()));
    CreatedChannels.erase(CreatedChannels.begin() + channelIndex);
}

// Remove channel from client
void Server::RemoveChannelFromClient(int fd, string channelName)
{
    Client &client = GetClient(fd);
    for (size_t j = 0; j < client.RegisteredChannels.size(); j++)
    {
        if (client.RegisteredChannels[j].GetChannelName() == channelName)
        {
            client.RegisteredChannels.erase(client.RegisteredChannels.begin() + j);
            break;
        }
    }
    RemoveChannelRegisteredUser(fd, channelName);
}

// Remove channel from registered users
void Server::RemoveChannelRegisteredUser(int fd, string channelName)
{
    int index = GetCreatedChannelIndex(channelName);
    Channel &channel = CreatedChannels[index];
    Client &client = GetClient(fd);

    for (size_t i = 0; i < channel.RegisteredUsersFd.size(); i++)
    {
        if (channel.RegisteredUsersFd[i] == fd)
        {
            channel.RegisteredUsersFd.erase(channel.RegisteredUsersFd.begin() + i);
            channel.SetUserCount(channel.GetUserCount() - 1);
            break;
        }
    }

    if (channel.GetOperator() == client.GetNickname())
                channel.SetOperator("");
        
    if (channel.GetUserCount() == 0)
    {
        RemoveChannel(fd, index, client.GetNickname());
    }
    else
    {
        ShowChannelInformations(fd, channelName);
        SendAllClientsMessage(channel.RegisteredUsersFd, RPL_PART(client.GetNickname(), channelName));
    }
}
