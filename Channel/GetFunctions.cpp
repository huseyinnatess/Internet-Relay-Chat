#include "Channel.hpp"

string Channel::GetChannelName()
{
    return _channelName;
}

string Channel::GetKey()
{
    return _key;
}

string Channel::GetTopic()
{
    return _topic;
}

string Channel::GetMode()
{
    return _mode;
}

bool Channel::GetIsPasswordProtected()
{
    return _isPasswordProtected;
}

bool Channel::GetInviteOnly()
{
    return _inviteOnly;
}

int Channel::GetUserCount()
{
    return _userCount;
}

int Channel::GetUserLimit()
{
    return _userLimit;
}

string Channel::GetOperator()
{
    return _operator;
}