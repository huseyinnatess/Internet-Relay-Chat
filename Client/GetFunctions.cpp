#include "Client.hpp"

int Client::GetFd()
{
    return _fd;
}

bool Client::GetRegistered()
{
    return _isRegistered;
}

bool Client::GetLoggedIn()
{
    return _isLoggedIn;
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

string Client::GetHostName()
{
    return _hostName;
}

string Client::GetClientColor()
{
    return _clientColor;
}
