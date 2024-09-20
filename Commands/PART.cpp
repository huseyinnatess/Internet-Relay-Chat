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

    string channelName = channels[0];
    if ((channelName[0] != '#' && channelName[0] != '&') || channelName.size() == 1)
    {
        SendError(fd, ERR_INVCHANNAME);
        return;
    }
    if (!CheckClientRegistered(fd, channelName))
    {
        SendError(fd, ERR_NOTONCHANNEL(channelName));
        return;
    }
    if (CheckChannelIsCreated(channelName))
    {
        RemoveChannelFromClient(fd, channelName);
    }
    else   
    {
        SendError(fd, ERR_NOSUCHCHANNEL(channelName));
    }
}