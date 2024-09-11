#include "../Server/Server.hpp"

void Server::ClientInvite(int fd, vector<string> commands)
{
    if (commands.size() < 2)
    {
        SendMessage(fd, ERR_NEEDMOREPARAMS(commands[0]));
        return;
    }
    commands.erase(commands.begin());
    vector<string> channels = SplitChannelNames(commands);

    int index = GetCreatedChannelIndex(channels[0]);
    if (index == -1)
    {
        SendMessage(fd, ERR_NOSUCHCHANNEL(channels[0]));
        return;
    }

    if (CheckClient(commands[1]) == 0)
    {
        SendMessage(fd, ERR_NOSUCHNICK(commands[1]));
        return;
    }

    Channel &channel = CreatedChannels[index];
    Client &client = GetClient(fd);
    Client &targetClient = GetClient(commands[1]);

    if (channel.GetOperator() != client.GetNickname())
    {
        SendMessage(fd, ERR_CHANOPRIVSNEEDED(channel.GetChannelName()));
        return;
    }

    targetClient.SetInvitedChannel(channels[0]);
    SendMessage(targetClient.GetFd(), RPL_INVITE(client.GetNickname(), client.GetIpAddress(), channel.GetChannelName(), commands[1]));
}