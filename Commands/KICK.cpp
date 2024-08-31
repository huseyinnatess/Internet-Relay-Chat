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
    string channelName = commands[0];

    if (CheckChannelIsCreated(channelName) == 0)
    {
        SendError(fd, ERR_NOSUCHCHANNEL(channelName));
        return;
    }
    if (CheckClient(commands[1]) == 0)
    {
        SendError(fd, ERR_NOSUCHNICK(commands[1]));
        return;
    }
    Client &client = GetClient(fd);
    Client &targetClient = GetClient(commands[1]);
    Channel &channel = CreatedChannels[GetCreatedChannelIndex(channelName)];
    
    if (client.GetNickname() != channel.GetOperator())
    {
        SendError(fd, ERR_CHANOPRIVSNEEDED(channelName));
        return;
    }

    if (client.GetNickname() == targetClient.GetNickname())
    {
        SendError(fd, ERR_CHANOPKICK(targetClient.GetNickname()));
        return;
    }

    RemoveChannelFromClient(targetClient.GetFd(), channelName);
    SendAllClientsMessage(channel.RegisteredUsersFd, RPL_KICK(client.GetNickname(), targetClient.GetNickname(), channelName));
    SendMessage(targetClient.GetFd(), RPL_KICK(targetClient.GetNickname(), targetClient.GetNickname(), channelName));
    ShowChannelInformations(fd, channelName);
}