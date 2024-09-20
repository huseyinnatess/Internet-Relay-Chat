#include "../Server/Server.hpp"
#include "../Channel/Channel.hpp"
#include <sstream> //-> for std::istringstream

void SplitChannelKeys(string channelKeys, vector<string>& keys)
{
    if (channelKeys.empty() || channelKeys.size() == 1 || channelKeys[0] == '#'
        || channelKeys[0] == '&')
    {
        return;
    }
    std::istringstream tokenStream(channelKeys);
    string token;

    while (std::getline(tokenStream, token, ','))
    {
        if (!token.empty())
        {
            int pos = token.find_first_of(' ');
            string channelName = token.substr(0, pos);
            keys.push_back(channelName);
        }
    }
}

void Server::ClientJoin(int fd, vector<string> channelNames)
{
    if (channelNames.size() <= 1)
    {
        SendError(fd, ERR_NEEDMOREPARAMS(channelNames[0]));
        return;
    }

    channelNames.erase(channelNames.begin()); // Removed JOIN command
    vector<string> keys;
    if (channelNames[1] != "")
    {
        SplitChannelKeys(channelNames[1], keys);
    }
    vector<string> channels = SplitChannelNames(channelNames);

    string channelName = channels[0];
    string key = "";
   
    if ((channelName[0] != '#' && channelName[0] != '&') || channelName.size() == 1)
    {
        SendError(fd, ERR_INVCHANNAME);
        return;
    }
    if (keys.size() > 0)
    {
        key = keys[0];
    }
    if (CheckClientRegistered(fd, channelName))
        return;

    if (CheckChannelIsCreated(channelName))
    {
        int index = GetCreatedChannelIndex(channelName);
        Channel &channel = CreatedChannels[index];

        // Check if channel is full
        if (channel.GetUserCount() == channel.GetUserLimit())
        {
            SendError(fd, ERR_CHANNELISFULL(channelName));
            return;
        }
        if (channel.GetInviteOnly() && GetClient(fd).GetInvitedChannel() != channelName)
        {
            SendError(fd, ERR_INVITEONLYCHAN(channelName));
            return;
        }

        // Check if channel is password protected
        if (channel.GetIsPasswordProtected())
        {
            if (channel.GetKey() == key)
            {
                JoinChannel(fd, channelName, index);
            }
            else
            {
                SendError(fd, ERR_BADCHANNELKEY(channelName));
                print("Channel key is not valid\n");
                return;
            }
        }

        // If channel is not password protected
        else if (!channel.GetIsPasswordProtected())
        {
            JoinChannel(fd, channelName, index);
        }
    }
    else
    {
        CreateAndJoinChannel(fd, channelName, key);
    }
}

void Server::JoinChannel(int fd, string channelName, int index)
{
    Client &client = GetClient(fd);
    Channel &channel = CreatedChannels[index];
    client.RegisteredChannels.push_back(channel);
    channel.SetUserCount(channel.GetUserCount() + 1);
    channel.RegisteredUsersFd.push_back(fd);
    print(client.GetNickname() + " joined channel: " + channelName);

    if (channel.GetTopic() != "")
    {
        SendMessage(client.GetFd(), RPL_TOPIC(client.GetNickname(), client.GetIpAddress(), channelName, channel.GetTopic()));
    }
    else
    {
        SendMessage(client.GetFd(), RPL_NOTOPIC(client.GetNickname(), channelName));
    }
    
    SendMessage(client.GetFd(), RPL_JOIN(client.GetNickname(), client.GetIpAddress(), channelName));
    ShowChannelInformations(fd, channelName);
}

void Server::CreateAndJoinChannel(int fd, string channelName, string key)
{
    Client &client = GetClient(fd);
    Channel newChannel(channelName, key);
    client.RegisteredChannels.push_back(newChannel);
    newChannel.RegisteredUsersFd.push_back(fd);
    newChannel.SetUserCount(1);
    newChannel.SetOperator(client.GetNickname());

    if (key != "" && key != "JOIN")
    {
        newChannel.SetIsPasswordProtected(true);
        newChannel.SetKey(key);
        print(client.GetNickname() + " create and joined channel: " + channelName + " with key: " + key);
    }
    else
    {
        print(client.GetNickname() + " create and joined channel: " + channelName);
    }
    CreatedChannels.push_back(newChannel);
    SendMessage(fd, RPL_JOIN(GetClient(fd).GetNickname(), GetClient(fd).GetIpAddress(), channelName));
    ShowChannelInformations(fd, channelName);
}

