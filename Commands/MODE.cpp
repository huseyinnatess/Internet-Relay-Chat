#include "../Server/Server.hpp"

void Server::ModeOperator(int fd, Channel &channel, string clientName)
{
    for (size_t i = 0; i < Clients.size(); i++)
    {
        if (Clients[i].GetNickname() == clientName)
        {
            print("Client: " + GetClient(fd).GetNickname() + " is operator in channel: " + channel.GetChannelName());
            channel.SetOperator(Clients[i].GetNickname());
            return;
        }
    }
    SendError(fd, "Client not found\r\n");
}

void ModePassword(int fd, Channel &channel, string password)
{
    if (password == "")
    {
        return;
    }
    channel.SetKey(password);
    channel.SetIsPasswordProtected(true);
}

void ModeChannelLimit(int fd, Channel &channel, string limit)
{
    int userLimit = ConvertToInt(limit);

    if (userLimit <= 0 || userLimit > 50 || channel.GetUserCount() > userLimit)
    {
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
    int index = GetCreatedChannelIndex(commands[0]);
    if (index == -1)
    {
        SendError(fd, ERR_NOSUCHCHANNEL(commands[0]));
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
        ModeOperator(fd, channel, commands[2]);
        ShowChannelInformations(fd, channel.GetChannelName());
        return;
    }
    if (commands[1] == "+k")
    {
        ModePassword(fd, channel, commands[2]);
        return;
    }
    if (commands[1] == "-k")
    {
        channel.SetKey("");
        channel.SetIsPasswordProtected(false);
        SendMessage(fd, "Channel key is removed: " + channel.GetChannelName());
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
        SendMessage(fd, "Invite only channel: " + channel.GetChannelName());
        return;
    }
    if (commands[1] == "-i")
    {
        channel.SetInviteOnly(false);
        SendMessage(fd, "Channel is not invite only: " + channel.GetChannelName());
        return;
    }
    SendError(fd, ERR_UNKNOWNMODE(channel.GetChannelName()));
}