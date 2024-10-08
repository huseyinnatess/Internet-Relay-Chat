#include "../Server/Server.hpp"

void Server::ClientNotice(int fd, vector<string> commands)
{
    if (commands.size() < 3)
    {
        return;
    }
    commands.erase(commands.begin());

    if (commands[0][0] == '#' || commands[0][0] == '&')
    {
        if (CheckChannelIsCreated(commands[0]) == 0)
        {
            return;
        }
        int channelIndex = GetCreatedChannelIndex(commands[0]);
        Channel &channel = CreatedChannels[channelIndex];
        if (CheckClientRegistered(fd, channel.GetChannelName()) == 0)
        {
            return;
        }
        string message = commands[1];
        for (size_t i = 2; i < commands.size(); i++)
            message += " " + commands[i];
        message = ":" + GetClient(fd).GetNickname() + " NOTICE " + channel.GetChannelName() + " " + message + "\r\n";

        if (GetClient(fd).GetConnectionType() == HEXCHAT)
        {
            vector<int> Tempfds;
            for (size_t i = 0; i < channel.RegisteredUsersFd.size(); i++)
            {
                if (channel.RegisteredUsersFd[i] != fd)
                    Tempfds.push_back(channel.RegisteredUsersFd[i]);
            }
            SendAllClientsMessage(Tempfds, message);
        }
        else
            SendAllClientsMessage(channel.RegisteredUsersFd, message);
    }
    else
    {
        if (CheckClient(commands[0]) == 0)
        {
            return;
        }
        Client& targetClient = GetClient(commands[0]);
        if (targetClient.GetFd() == fd)
        {
            return;
        }
        string message = commands[1];
        if (message[0] == ':')
            message.erase(message.begin());
        for (size_t i = 2; i < commands.size(); i++)
            message += " " + commands[i];
        message = ":" + GetClient(fd).GetNickname() + " NOTICE " + targetClient.GetNickname() + " " + message + "\r\n";
        SendMessage(targetClient.GetFd(), message);
    }
}