#include "../Server/Server.hpp"

void Server::ModeOperator(int fd, Channel &channel, string clientName)
{
    int clientRegisterFlag = 0;
    int targetFd = GetClient(clientName).GetFd();

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
        SendError(fd, ERR_NOCHANNELREGISTER(channel.GetChannelName(), clientName));
        return;
    }

    channel.SetOperator(clientName);
    ShowChannelInformations(fd, channel.GetChannelName());
}

void Server::ModePassword(int fd, Channel &channel, string password)
{
    if (password == "")
    {
        SendError(fd, "Password is not set\r\n");
        return;
    }
    channel.SetKey(password);
    channel.SetIsPasswordProtected(true);
}

void Server::ModeChannelLimit(int fd, Channel &channel, string limit)
{
    int userLimit = ConvertToInt(limit);

    if (userLimit <= 0 || userLimit > 200 || channel.GetUserCount() > userLimit)
    {
        SendError(fd, "Limit is not changed\r\n");
        return;
    }
    channel.SetUserLimit(userLimit);
}

void Server::ClientMode(int fd, vector<string> commands)
{
    if (commands.size() == 1)
        return;
    if (commands.size() < 1 || commands.size() > 4)
    {
        SendError(fd, ERR_NEEDMOREPARAMS(commands[0]));
        return;
    }
    commands.erase(commands.begin());
    vector<string> channelName = SplitChannelNames(commands);
    int index = GetCreatedChannelIndex(channelName[0]);
    if (index == -1)
    {
        SendError(fd, ERR_NOSUCHCHANNEL(channelName[0]));
        return;
    }

    Channel &channel = CreatedChannels[index];
    Client &client = GetClient(fd);

    if (channel.GetOperator() != client.GetNickname())
    {
        SendError(fd, ERR_CHANOPRIVSNEEDED(channel.GetChannelName()));
        return;
    }

    if (commands[1] == "+o")
    {
        if (!CheckClient(commands[2]))
        {
            SendError(fd, "Client not found\r\n");
            return;
        }
        ModeOperator(fd, channel, commands[2]);
        return;
    }
    if (commands[1] == "+k")
    {
        ModePassword(fd, channel, commands[3]);
        return;
    }
    if (commands[1] == "-k")
    {
        channel.SetKey("");
        channel.SetIsPasswordProtected(false);
        return;
    }
    if (commands[1] == "+l")
    {
        ModeChannelLimit(fd, channel, commands[2]);
        return;
    }
    if (commands[1] == "+i")
    {
        channel.SetInviteOnly(true);
        SendMessage(fd, "Invite only channel: " + channel.GetChannelName() + "\r\n");
        return;
    }
    if (commands[1] == "-i")
    {
        channel.SetInviteOnly(false);
        SendMessage(fd, "Channel is not invite only: " + channel.GetChannelName() + "\r\n");
        return;
    }
    SendError(fd, ERR_UNKNOWNMODE(client.GetNickname(), channel.GetChannelName(), commands[1]));
}