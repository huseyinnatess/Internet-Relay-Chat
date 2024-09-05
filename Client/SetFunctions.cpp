#include "Client.hpp"

void Client::SetFd(int fd)
{
    _fd = fd;
}

void Client::SetIpAddress(string ipAddress)
{
    _ipAddress = ipAddress;
}

void Client::SetClientColor(string clientColor)
{
    _clientColor = clientColor;
}

void Client::SetBuffer(string buffer)
{
    _buffer += buffer;
}

void Client::SetLoggedIn(bool isLoggedIn)
{
    _isLoggedIn = isLoggedIn;
}

void Client::SetRegistered(bool isRegistered)
{
    _isRegistered = isRegistered;
}

void Client::SetUsername(string username)
{
    if (_username.length() > 11)
        _username = username.substr(1, 10);
    else
        _username = username;
}

void Client::SetNickname(string nickname)
{
    if (_nickname.length() > 9)
        _nickname = nickname.substr(0, 9);
    else
        _nickname = nickname;
}

void Client::SetOldNickname(string oldNickname)
{
    if (_oldNickname.length() > 9)
        _oldNickname = oldNickname.substr(0, 9);
    else
        _oldNickname = oldNickname;
}

void Client::SetInvitedChannel(string channelName)
{
    _invitedChannel = channelName;
}

void Client::SetConnectionType(bool connectionType)
{
    _connectionType = connectionType;
}