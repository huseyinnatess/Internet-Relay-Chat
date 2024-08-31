#include <sys/socket.h> //-> for send()
#include "../Server/Server.hpp"

void Server::SendError(int fd, string errorMesssage, int clientCloseFlag)
{
    if (send(fd, errorMesssage.c_str(), errorMesssage.size(), 0) == -1)
        std::cerr << "Error: send() failed" << std::endl;
    if (clientCloseFlag)
    {
        SetClosedClientDefaultValue(fd);
    }
}

void Server::SendMessage(int fd, string message)
{
    if (send(fd, message.c_str(), message.size(), 0) == -1)
        std::cerr << "Error: send() failed" << std::endl;
    print("\n");
}

void Server::SendAllClientsMessage(vector<int> fds, string message)
{
    for (size_t i = 0; i < fds.size(); i++)
    {
        if (send(fds[i], message.c_str(), message.size(), 0) == -1)
            std::cerr << "Error: send() failed" << std::endl;
    }
}

void Server::ShowChannelInformations(int fd, string channelName)
{
    int index = GetCreatedChannelIndex(channelName);
    string messages = "";
    Channel &channel = CreatedChannels[index];
    vector<int> fds;
    for (size_t i = 0; i < channel.RegisteredUsersFd.size(); i++)
    {
        Client &client = GetClient(channel.RegisteredUsersFd[i]);
        if (client.GetNickname() == channel.GetOperator())
            messages += "@";
        fds.push_back(client.GetFd());
        messages += client.GetNickname() + " ";
    }
    Client &requestingClient = GetClient(fd);
    SendAllClientsMessage(fds, RPL_NAMREPLY(requestingClient.GetNickname(), channelName, messages));
    SendAllClientsMessage(fds, RPL_ENDOFNAMES(requestingClient.GetNickname(), channelName));
}