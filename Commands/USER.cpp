#include "../Server/Server.hpp"

string MergeCommand(vector<string> command)
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

void Server::ClientUsername(int fd, vector<string> command)
{
    Client& client = GetClient(fd);
    
    string username = MergeCommand(command);

    if (command.size() < 2)
    {
        SendError(fd, ERR_NEEDMOREPARAMS(command[0]));
        return;
    }

    if (username[0] == ':')
        return;

    if (CheckIsUsing(username, "username") || client.GetUsername() != "Client")
    {
        SendError(fd, ERR_ALREADYREGISTRED);
        return;
    }

    if (client.GetUsername() == "Client")
    {
        if (username.find_first_of(" ") != string::npos)
        {
            username = username.substr(0, username.find_first_of(" "));
        }
        client.SetUsername(username);
        print("Username: " + client.GetUsername(), client.GetClientColor());
    }
}