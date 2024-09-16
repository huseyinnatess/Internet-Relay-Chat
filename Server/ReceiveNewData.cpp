#include "Server.hpp"
#include <sstream> //-> for std::istringstream

void SplitBuffer(string buffer, vector<string>& commandList);

void Server::ReceiveNewData(int fd)
{
    char buffer[1024];
    string message = "";
    Client &client = GetClient(fd);
    vector<string> commandList;

    memset(buffer, 0, sizeof(buffer));
    int bytesReceived = 0;

    while ((bytesReceived = recv(fd, buffer, sizeof(buffer), 0)) > 0)
    {
        message += buffer;
    }

    if (bytesReceived == 0) // Ctrl + d
    {
        ClientQuit(fd);
        return;
    }

    client.SetBuffer(message);
    if (client.GetBuffer().find_first_of("\r\n") == string::npos) // End of line
         return;

    SplitBuffer(message, commandList);

    for (size_t i = 0; i < commandList.size(); i++)
    {
        ParseClientCommands(fd, commandList[i]);
        break;
    }
    if (client.GetBuffer() != "")
    {
        client.ClearBuffer();
    }
}

void SplitBuffer(string buffer, vector<string>& commandList)
{
    std::istringstream stm(buffer); // reading string first space character
    string token;

    while (std::getline(stm, token))
    {
        size_t pos = token.find_first_of("\r\n");
        if (pos != string::npos)
            token = token.substr(0, pos);
        commandList.push_back(token);
    }
}