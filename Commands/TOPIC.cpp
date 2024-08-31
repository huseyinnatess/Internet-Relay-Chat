#include "../Server/Server.hpp"

string ParseTopic(vector<string> channelNames)
{
    string topic = "";
    if (channelNames[1][0] == ':')
    {
        for (size_t i = 1; i < channelNames.size(); i++)
        {
            topic += channelNames[i] + " ";
        }
    }
    return topic;
}

void Server::ClientTopic(int fd, vector<string> channelNames)
{
    if (channelNames.size() < 2)
    {
        SendError(fd, ERR_NEEDMOREPARAMS(channelNames[0]));
        return;
    }
    channelNames.erase(channelNames.begin()); // Removed TOPIC command
    vector<string> channels = SplitChannelNames(channelNames);

    int index = GetCreatedChannelIndex(channels[0]);
    if (index == -1)
    {
        SendError(fd, ERR_NOSUCHCHANNEL(channels[0]));
        return;
    }
    Channel &channel = CreatedChannels[index];
    Client &client = GetClient(fd);
    if (channelNames.size () < 2)
    {
        SendError(fd, RPL_TOPIC(client.GetNickname(), client.GetIpAddress(), channel.GetChannelName(), channel.GetTopic()));
        return;
    }

    string topic = ParseTopic(channelNames);

    if (topic == "")
    {
        SendError(fd, RPL_NOTOPIC(client.GetNickname(), channelNames[0]));
        return;
    }
    else
    {
        if (channel.GetOperator() == client.GetNickname())
        {
            channel.SetTopic(topic);
            SendError(fd, RPL_TOPIC(client.GetNickname(), client.GetIpAddress(), channel.GetChannelName(), channel.GetTopic()));
            print("Topic changed to: " + channel.GetTopic(), GREEN);
        }
        else
        {
            SendError(fd, ERR_CHANOPRIVSNEEDED(channel.GetChannelName()));
        }
    }
}