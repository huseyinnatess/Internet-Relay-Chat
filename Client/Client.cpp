#include "Client.hpp"

Client::Client() : _nickname("Client"), _username("Client"), _fd(-1) 
{
    _oldNickname = "";
    _isOperator = false;
    _isRegistered = false;
    _buffer = "";
    _ipAddress = "";
    _clientColor = "";
    _registeredChannelCount = 0;
    _connectionType = NC;
}

Client::Client(Client const &client)
{
    if (this != &client)
        *this = client;
}

Client &Client::operator=(Client const& client)
{
    if (this != &client)
    {
        _nickname = client._nickname;
        _username = client._username;
        _fd = client._fd;
        _oldNickname = client._oldNickname;
        _registeredChannelCount = client._registeredChannelCount;
        _isOperator = client._isOperator;
        _isRegistered = client._isRegistered;
        _buffer = client._buffer;
        _ipAddress = client._ipAddress;
        _clientColor = client._clientColor;
        _connectionType = client._connectionType;
    }
    return *this;
}

void Client::ClearBuffer()
{
    _buffer.clear();
}