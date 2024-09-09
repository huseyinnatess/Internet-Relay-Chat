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
    static int i = 0;
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
        // if (i == 0 && Clients.size() == 1)
        // {
        //     ParseClientCommands(4, "join #ates");
        //     ParseClientCommands(4, "join #ates2");
        //     ParseClientCommands(4, "join #ates3");
        //     ParseClientCommands(4, "join #ates4");
        //     ParseClientCommands(4, "join #ates5");
        //     sleep(2);
        //     i++;
        // }
        // if (i == 1 && Clients.size() == 2)
        // {
        //     ParseClientCommands(5, "pass password");
        //     ParseClientCommands(5, "nick Ates");
        //     ParseClientCommands(5, "join #ates");
        //     ParseClientCommands(4, "join #ates2");
        //     ParseClientCommands(4, "join #ates3");
        //     ParseClientCommands(4, "join #ates4");
        //     ParseClientCommands(4, "join #ates5");
        //     sleep(3);
        //     i++;
        // }
        // if (i == 2)
        // {
        //     ParseClientCommands(4, "quit");
        //     i++;
        // }
        // if (i == 3)
        // {
        //     ParseClientCommands(5, "join #ates");
        //     i++;
        // }
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
}
