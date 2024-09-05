#include "Client.hpp"

int Client::GetFd()
{
    return _fd;
}

bool Client::GetRegistered()
{
    return _isRegistered;
}

string Client::GetUsername()
{
    return _username;
}

string Client::GetNickname()
{
    return _nickname;
}

string Client::GetIpAddress()
{
    return _ipAddress;
}

string Client::GetBuffer()
{
    return _buffer;
}

string Client::GetInvitedChannel()
{
    return _invitedChannel;
}

string Client::GetClientColor()
{
    return _clientColor;
}

bool Client::GetConnectionType()
{
    return _connectionType;
}

