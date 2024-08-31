#include "../Server/Server.hpp"

void Server::ClientNick(int fd, vector<string> command)
{
    Client &client = GetClient(fd);

    if (command.size() != 2)
    {
        SendError(fd, ERR_NONICKNAMEGIVEN, 1);
        return;
    }
    if (!CheckIsValidNickname(command[1]))
    {
        SendError(fd, ERR_ERRONEUSNICKNAME(client.GetNickname()), 1);
        return;
    }
    if (CheckIsUsing(command[1], "nickname"))
    {
        SendError(fd, ERR_NICKNAMEINUSE(client.GetNickname()), 1);
        return;
    }
    client.SetOldNickname(client.GetNickname());
    client.SetNickname(command[1]);
    client.SetLoggedIn(true);
    print("Nickname: " + client.GetNickname(), client.GetClientColor());
}