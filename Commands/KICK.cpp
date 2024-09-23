#include "../Server/Server.hpp"

void Server::ClientKick(int fd, vector<string> commands)
{
    if (commands.size() < 2)
    {
        SendError(fd, ERR_NEEDMOREPARAMS(commands[0]));
        return;
    }
    commands.erase(commands.begin());

    if (commands[1][0] == ':')
    {
        commands[1].erase(commands[1].begin());
    }
    vector<string> channelName = SplitChannelNames(commands);

    if (CheckChannelIsCreated(channelName[0]) == 0)
    {
        SendError(fd, ERR_NOSUCHCHANNEL(channelName[0]));
        return;
    }
    if (CheckClient(commands[1]) == 0)
    {
        SendError(fd, ERR_NOSUCHNICK(commands[1]));
        return;
    }

    Channel &channel = CreatedChannels[GetCreatedChannelIndex(channelName[0])];

    int clientRegisterFlag = 0;
    Client &targetClient = GetClient(commands[1]);
    int targetFd = targetClient.GetFd();

    for (size_t i = 0; i < channel.RegisteredUsersFd.size(); i++)
    {
        if (targetFd == channel.RegisteredUsersFd[i])
        {
            clientRegisterFlag = 1;
            break;
        }
    }
    if (clientRegisterFlag == 0)
    {
        SendError(fd, ERR_NOCHANNELREGISTER(channel.GetChannelName(), commands[1]));
        return;
    }

    Client &client = GetClient(fd);
    
    if (client.GetNickname() != channel.GetOperator())
    {
        SendError(fd, ERR_CHANOPRIVSNEEDED(channelName[0]));
        return;
    }

    if (client.GetNickname() == targetClient.GetNickname())
    {
        SendError(fd, ERR_CHANOPKICK(targetClient.GetNickname()));
        return;
    }

    SendAllClientsMessage(channel.RegisteredUsersFd, RPL_KICK(client.GetNickname(), targetClient.GetNickname(), channelName[0]));
    SendMessage(targetClient.GetFd(), RPL_KICK(targetClient.GetNickname(), targetClient.GetNickname(), channelName[0]));
    RemoveChannelFromClient(targetClient.GetFd(), channelName[0]);
}