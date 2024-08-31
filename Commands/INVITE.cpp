#include "../Server/Server.hpp"

void Server::ClientInvite(int fd, vector<string> channelNames)
{
    if (channelNames.size() < 2)
    {
        SendMessage(fd, ERR_NEEDMOREPARAMS(channelNames[0]));
        return;
    }
    channelNames.erase(channelNames.begin());

    int index = GetCreatedChannelIndex(channelNames[0]);
    if (index == -1)
    {
        SendMessage(fd, ERR_NOSUCHCHANNEL(channelNames[0]));
        return;
    }

    Channel &channel = CreatedChannels[index];
    Client &client = GetClient(fd);

    if (channel.GetOperator() != client.GetNickname())
    {
        SendMessage(fd, ERR_CHANOPRIVSNEEDED(channel.GetChannelName()));
        return;
    }

    for (size_t i = 0; i < Clients.size(); i++)
    {
        if (Clients[i].GetNickname() == channelNames[1])
        {
            Clients[i].SetInvitedChannel(channelNames[0]);
            SendMessage(Clients[i].GetFd(), RPL_INVITE(client.GetNickname(), client.GetIpAddress(), channel.GetChannelName(), channelNames[1]));
            return;
        }
    }
    
    SendMessage(fd, ERR_NOSUCHNICK(channelNames[1]));
}