#include "../Server/Server.hpp"

void Server::ClientUsername(int fd, vector<string> command)
{
    Client& client = GetClient(fd);

    if (!client.GetRegistered())
    {
        SendError(fd, ERR_NOTREGISTERED(client.GetNickname()));
        return;
    }
    
    if (command.size() < 2)
    {
        SendError(fd, ERR_NEEDMOREPARAMS(command[0]));
        return;
    }

    string username = command[1];

    if (CheckIsUsing(username, "username") || client.GetUsername() != "Client")
    {
        SendError(fd, ERR_ALREADYREGISTRED);
        return;
    }
    
    if (username[0] == ':')
        username = username.substr(1, username.size());
    if (username.size() > 10)
    {
        username = username.substr(0, 10);
    }
    if (client.GetUsername() == "Client")
    {
        client.SetUsername(username);
        print("Username: " + client.GetUsername(), client.GetClientColor());
    }
}