#include "Channel.hpp"

void Channel::SetChannelName(string channelName)
{
    _channelName = channelName;
}

void Channel::SetKey(string password)
{
    _key = password;
    if (password != "")
        SetIsPasswordProtected(true);
    else
        SetIsPasswordProtected(false);
}

void Channel::SetTopic(string topic)
{
    _topic = topic;
}

void Channel::SetMode(string mode)
{
    _mode = mode;
}

void Channel::SetIsPasswordProtected(bool isPasswordProtected)
{
    _isPasswordProtected = isPasswordProtected;
}

void Channel::SetInviteOnly(bool inviteOnly)
{
    _inviteOnly = inviteOnly;
}

void Channel::SetUserCount(int userCount)
{
    _userCount = userCount;
}

void Channel::SetUserLimit(int userLimit)
{
    _userLimit = userLimit;
}

void Channel::SetOperator(string op)
{
    _operator = op;
}