#include "../Server/Server.hpp"

void Server::ClientNotice(int fd, vector<string> commands)
{
    if (commands.size() < 3)
    {
        return;
    }
    commands.erase(commands.begin());

    if (CheckClient(commands[0]) == 0)
    {
        return;
    }
    Client& targetClient = GetClient(commands[0]);
    if (targetClient.GetFd() == fd)
    {
        return;
    }
    string message = commands[1];
    if (message[0] == ':')
        message.erase(message.begin());
    for (size_t i = 2; i < commands.size(); i++)
        message += " " + commands[i];
    SendMessage(targetClient.GetFd(), RPL_NOTICE(GetClient(fd).GetNickname(), targetClient.GetNickname(), message));
}