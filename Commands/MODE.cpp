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

void Server::ClientMode(int fd, vector<string> channelNames)
{
    if (channelNames.size() == 1)
        return;
    if (channelNames.size() < 1 || channelNames.size() > 4)
    {
        SendError(fd, ERR_NEEDMOREPARAMS(channelNames[0]));
        return;
    }
    channelNames.erase(channelNames.begin());
    vector<string> channels = SplitChannelNames(channelNames);
    int index = GetCreatedChannelIndex(channels[0]);
    if (index == -1)
    {
        SendError(fd, ERR_NOSUCHCHANNEL(channels[0]));
        return;
    }

    Channel &channel = CreatedChannels[index];
    Client &client = GetClient(fd);

    if (channel.GetOperator() != client.GetNickname())
    {
        SendError(fd, ERR_CHANOPRIVSNEEDED(channel.GetChannelName()));
        return;
    }

    if (channelNames[1] == "+o")
    {
        ModeOperator(fd, channel, channelNames[2]);
        ShowChannelInformations(fd, channel.GetChannelName());
        return;
    }
    if (channelNames[1] == "+k")
    {
        ModePassword(fd, channel, channelNames[2]);
        return;
    }
    if (channelNames[1] == "-k")
    {
        channel.SetKey("");
        channel.SetIsPasswordProtected(false);
        SendMessage(fd, "Channel key is removed: " + channel.GetChannelName());
        return;
    }
    if (channelNames[1] == "+l")
    {
        ModeChannelLimit(fd, channel, channelNames[2]);
        return;
    }
    if (channelNames[1] == "+i")
    {
        channel.SetInviteOnly(true);
        SendMessage(fd, "Invite only channel: " + channel.GetChannelName());
        return;
    }
    if (channelNames[1] == "-i")
    {
        channel.SetInviteOnly(false);
        SendMessage(fd, "Channel is not invite only: " + channel.GetChannelName());
        return;
    }
    SendError(fd, ERR_UNKNOWNMODE(channel.GetChannelName()));
}