#include "Server.hpp"

void Server::RemoveChannel(int fd, int channelIndex, string clientNickname)
{
    SendMessage(fd, RPL_PART(clientNickname, CreatedChannels[channelIndex].GetChannelName()));
    print("Channel " + CreatedChannels[channelIndex].GetChannelName() + " is removed\n");
    CreatedChannels.erase(CreatedChannels.begin() + channelIndex);
}

// Remove channel from client
void Server::RemoveChannelFromClient(int fd, string channelName)
{
    Client &client = GetClient(fd);
    for (size_t i = 0; i < client.RegisteredChannels.size(); i++)
    {
        if (client.RegisteredChannels[i].GetChannelName() == channelName)
        {
            client.RegisteredChannels.erase(client.RegisteredChannels.begin() + i);
            break;
        }
    }
    RemoveChannelRegisteredUser(client, channelName);
}

// Remove channel from registered users
void Server::RemoveChannelRegisteredUser(Client& client, string channelName)
{
    int index = GetCreatedChannelIndex(channelName);
    Channel &channel = CreatedChannels[index];
    int fd = client.GetFd();

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
