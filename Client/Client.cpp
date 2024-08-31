#include "Client.hpp"

Client::Client()
{
    _nickname = "Client";
    _oldNickname = "";
    _username = "Client";
    _fd = -1;
    _isLoggedIn = false;
    _isOperator = false;
    _isRegistered = false;
    _buffer = "";
    _ipAddress = "";
    _clientColor = "";
    _hostName = "";
}

Client::Client(string nickname, string username, int fd)
{
    _nickname = nickname;
    _registeredChannelCount = 0;
    _oldNickname = "";
    _username = username;
    _fd = fd;
    _isLoggedIn = false;
    _isOperator = false;
    _isRegistered = false;
    _buffer = "";
    _ipAddress = "";
    _clientColor = "";
    _hostName = "";
}

Client::Client(Client const &client)
{
    if (this == &client)
        return;
    _nickname = client._nickname;
    _hostName = client._hostName;
    _oldNickname = client._oldNickname;
    _registeredChannelCount = client._registeredChannelCount;
    _username = client._username;
    _fd = client._fd;
    _isLoggedIn = client._isLoggedIn;
    _isOperator = client._isOperator;
    _isRegistered = client._isRegistered;
    _buffer = client._buffer;
    _ipAddress = client._ipAddress;
    _clientColor = client._clientColor;
}

Client &Client::operator=(Client const &client)
{
    if (this == &client)
        return *this;
    _nickname = client._nickname;
    _oldNickname = client._oldNickname;
    _registeredChannelCount = client._registeredChannelCount;
    _username = client._username;
    _fd = client._fd;
    _isLoggedIn = client._isLoggedIn;
    _isOperator = client._isOperator;
    _isRegistered = client._isRegistered;
    _buffer = client._buffer;
    _ipAddress = client._ipAddress;
    _clientColor = client._clientColor;
    return *this;
}

void Client::ClearBuffer()
{
    _buffer.clear();
}