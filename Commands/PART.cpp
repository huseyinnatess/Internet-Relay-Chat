#include "../Server/Server.hpp"

void Server::ClientPart(int fd, vector<string> channelNames)
{    
    if (channelNames.size() < 2)
    {
        SendError(fd, ERR_NEEDMOREPARAMS(channelNames[0]));
        return;
    }
    channelNames.erase(channelNames.begin()); // Removed PART command
    vector<string> channels = SplitChannelNames(channelNames);

    for (size_t i = 0; i < channels.size(); i++)
    {
        string channelName = channels[i];
        if ((channelName[0] != '#' && channelName[0] != '&') || channelName.size() == 1)
        {
            SendError(fd, ERR_INVCHANNAME);
            continue;
        }
        if (!CheckClientRegistered(fd, channelName))
        {
            SendError(fd, ERR_NOTONCHANNEL(channelName));
            continue;
        }
        if (CheckChannelIsCreated(channelName))
        {
            int index = GetCreatedChannelIndex(channelName);
            Client &client = GetClient(fd);
            Channel &channel = CreatedChannels[index];
            if (channel.GetUserCount() == 1)
            {
                RemoveChannelFromClient(fd, channelName);
                channel.SetOperator("");
                RemoveChannel(index);
                SendMessage(fd, RPL_PART(client.GetNickname(), channelName));
            }
            else
            {
                RemoveChannelFromClient(fd, channelName);
                if (channel.GetOperator() == client.GetNickname())
                    channel.SetOperator("");
                ShowChannelInformations(fd, channelName);
                SendAllClientsMessage(channel.RegisteredUsersFd, RPL_PART(client.GetNickname(), channelName));
            }
        }
        else
        {
            SendError(fd, ERR_NOSUCHCHANNEL(channelName));
        }
    }
}