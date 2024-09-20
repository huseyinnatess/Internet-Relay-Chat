#include "Server.hpp"

void Server::ServerInit(int port, string password)
{
    _port = port;
    _password = password;

    ServerCreateSocket();
    InitializeCommandMap();

    print("Server Socket: " + ConvertToString(_socketFd), GREEN);
    print("Waiting for clients...", YELLOW);
    ServerLoop();
}

void Server::ServerLoop()
{
    while (!Server::_signal)
    {
        if ((poll(&_pollFds[0], _pollFds.size(), -1)) == -1 && !Server::_signal) // Wait indefinitely for events
            throw std::runtime_error("poll failed");
        for (size_t i = 0; i < _pollFds.size(); i++)
        {
            if (_pollFds[i].revents & POLLIN)
            {
                if (_pollFds[i].fd == _socketFd)
                    AcceptNewClient();
                else
                {
                    ReceiveNewData(_pollFds[i].fd);
                }
            }
        }
    }
    CloseFds();
}

void Server::InitializeCommandMap() 
{
    _commandsMap["CAP"] = CAP;
    _commandsMap["PASS"] = PASS;
    _commandsMap["NICK"] = NICK;
    _commandsMap["USER"] = USER;
    _commandsMap["QUIT"] = QUIT;
    _commandsMap["KICK"] = KICK;
    _commandsMap["JOIN"] = JOIN;
    _commandsMap["TOPIC"] = TOPIC;
    _commandsMap["MODE"] = MODE;
    _commandsMap["PART"] = PART;
    _commandsMap["PRIVMSG"] = PRIVMSG;
    _commandsMap["INVITE"] = INVITE;
    _commandsMap["NOTICE"] = NOTICE;
}

Server::Server(Server const& oth)
{
    if (this != &oth)
    {
        *this = oth;
    }
}

Server& Server::operator=(Server const& oth)
{
    if (this != &oth)
    {
        _port = oth._port;
        _socketFd = oth._socketFd;
        _signal = oth._signal;
        _pollFds = oth._pollFds;
        _password = oth._password;
        _commandsMap = oth._commandsMap;
        Clients = oth.Clients;
        CreatedChannels = oth.CreatedChannels;
    }
    return *this;
}