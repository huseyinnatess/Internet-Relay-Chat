#include "../Server/Server.hpp"

void Server::ClientNick(int fd, vector<string> command)
{
    Client &client = GetClient(fd);

    if (!client.GetRegistered())
    {
        SendError(fd, ERR_NOTREGISTERED(client.GetNickname()));
        return;
    }

    if (command.size() != 2)
    {
        SendError(fd, ERR_NONICKNAMEGIVEN);
        return;
    }
    if (!CheckIsValidNickname(command[1]))
    {
        SendError(fd, ERR_ERRONEUSNICKNAME(client.GetNickname()));
        return;
    }
    if (CheckIsUsing(command[1], "nickname"))
    {
        SendError(fd, ERR_NICKNAMEINUSE(client.GetNickname()));
        return;
    }
    client.SetOldNickname(client.GetNickname());
    client.SetNickname(command[1]);
    print("Nickname: " + client.GetNickname(), client.GetClientColor());
}