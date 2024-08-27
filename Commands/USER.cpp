#include "../Server/Server.hpp"

string MergeCommand(std::vector<string> command)
{
    string mergedCommand;
    for (size_t i = 1; i < command.size(); i++)
    {
        mergedCommand += command[i];
        if (i != command.size() - 1)
            mergedCommand += " ";
    }
    return mergedCommand;
}

bool CheckFormat(string username)
{
    return (username[0] == ':');
}

void Server::ClientUsername(int fd, std::vector<string> command)
{
    Client& client = GetClient(fd);
    
    string username = MergeCommand(command);

    if (command.size() < 2)
    {
        SendError(fd, ERR_NEEDMOREPARAMS(command[0]));
        return;
    }

    if (CheckFormat(username) == false)
        return;

    if (client.GetRegistered() || CheckIsUsing(username, "username") || client.GetUsername() != "Client")
    {
        SendError(fd, ERR_ALREADYREGISTRED);
        return;
    }

    if (client.GetUsername() == "Client")
    {
        client.SetUsername(username);
    }
}