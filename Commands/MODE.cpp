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

void Server::ClientMode(int fd, std::vector<string> channelNames)
{
    if (channelNames.size() == 1)
        return;
    if (channelNames.size() < 1 || channelNames.size() > 4)
    {
        SendError(fd, ERR_NEEDMOREPARAMS(channelNames[0]));
        return;
    }
    channelNames.erase(channelNames.begin());
    std::vector<string> channels = SplitChannelNames(channelNames);
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
    if (channelNames[1] == "+l")
    {
        ModeChannelLimit(fd, channel, channelNames[2]);
        return;
    }
    SendError(fd, ERR_UNKNOWNMODE(channel.GetChannelName()));
}