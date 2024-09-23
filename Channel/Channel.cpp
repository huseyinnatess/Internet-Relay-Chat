#include "Channel.hpp"
#include "../Server/Server.hpp"

Channel::Channel()
{
    _channelName = "";
    _topic = "";
    _mode = "";
    _key = "";
    _isPasswordProtected = false;
    _inviteOnly = false;
    _userCount = 0;
    _userLimit = 0;
    _operator = "";
}

Channel::Channel(string const channelName, string const key)
{
    if (key.empty())
    {
        _key = "";
        _isPasswordProtected = false;
    }
    else
    {
        _key = key;
        _isPasswordProtected = true;
    }
    _channelName = channelName;
    _topic = "";
    _mode = "";
    _inviteOnly = false;
    _userCount = 0;
    _userLimit = 0;
    _operator = "";
}
Channel &Channel::operator=(Channel const& channel)
{
    if (this != &channel)
    {
        _channelName = channel._channelName;
        _topic = channel._topic;
        _mode = channel._mode;
        _key = channel._key;
        _operator = channel._operator;
        _isPasswordProtected = channel._isPasswordProtected;
        _inviteOnly = channel._inviteOnly;
        _userCount = channel._userCount;
        _userLimit = channel._userLimit;
        RegisteredUsersFd = channel.RegisteredUsersFd;
    }
    return *this;
}

Channel::Channel(Channel const& channel)
{
    if (this != &channel)
        *this = channel;
}
