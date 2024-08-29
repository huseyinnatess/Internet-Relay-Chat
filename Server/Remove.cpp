#include "Server.hpp"

void Server::RemoveChannel(int channelIndex)
{
    CreatedChannels.erase(CreatedChannels.begin() + channelIndex);
}

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

void Server::RemoveChannelRegisteredUser(int fd, string channelName)
{
    int index = GetCreatedChannelIndex(channelName);
    Channel &channel = CreatedChannels[index];
    for (size_t i = 0; i < channel.RegisteredUsersFd.size(); i++)
    {
        if (channel.RegisteredUsersFd[i] == fd)
        {
            channel.RegisteredUsersFd.erase(channel.RegisteredUsersFd.begin() + i);
            break;
        }
    }
}
