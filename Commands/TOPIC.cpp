#include "../Server/Server.hpp"

string ParseTopic(vector<string> commands)
{
    string topic = "";
    if (commands[1][0] == ':')
    {
        for (size_t i = 1; i < commands.size(); i++)
        {
            topic += commands[i] + " ";
        }
    }
    return topic;
}

void Server::ClientTopic(int fd, vector<string> commands)
{
    if (commands.size() < 2)
    {
        SendError(fd, ERR_NEEDMOREPARAMS(commands[0]));
        return;
    }
    commands.erase(commands.begin());
    vector<string> channels = SplitChannelNames(commands);

    int index = GetCreatedChannelIndex(channels[0]);
    if (index == -1)
    {
        SendError(fd, ERR_NOSUCHCHANNEL(channels[0]));
        return;
    }
    Channel &channel = CreatedChannels[index];
    Client &client = GetClient(fd);
    if (commands.size () < 2)
    {
        SendError(fd, RPL_TOPIC(client.GetNickname(), client.GetIpAddress(), channel.GetChannelName(), channel.GetTopic()));
        return;
    }
    if (channel.GetOperator() != client.GetNickname())
    {
        SendError(fd, ERR_CHANOPRIVSNEEDED(channel.GetChannelName()));
        return;
    }
    string topic = ParseTopic(commands);

    if (topic == "")
    {
        SendError(fd, RPL_NOTOPIC(client.GetNickname(), commands[0]));
        return;
    }
    else
    {
        if (topic[0] == ':')
            topic.substr(1, topic.size() - 1);
        channel.SetTopic(topic);
        SendAllClientsMessage(channel.RegisteredUsersFd, RPL_TOPIC(client.GetNickname(), client.GetIpAddress(), channel.GetChannelName(), channel.GetTopic()));
    }
}