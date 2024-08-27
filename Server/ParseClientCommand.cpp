#include "../Server/Server.hpp"
#include <sstream> //-> for std::istringstream

std::vector<string> SplitCommand(string command) // Split the command
{
    std::vector<string> commandList;
    std::istringstream stm(command);
    string token;

    while (stm >> token)
    {
        commandList.push_back(token);
        token.clear();
    }
    
    return commandList;
}

int Server::FindCommandInMap(string command)
{
    command = ConvertToUpperCase(command);
    if (_commandsMap.find(command) == _commandsMap.end() || command.empty())
        return -1;
    return _commandsMap[command];
}

void Server::RouterCommands(int fd, int commandIndex, std::vector<string> command)
{
    switch (commandIndex)
    {
        case JOIN:
            ClientJoin(fd, command);
            break;
        case PART:
            ClientPart(fd, command);
            break;
    }
}

void Server::RouterLoginCommands(int fd, int commandIndex, std::vector<string> command)
{
    Client &client = GetClient(fd);
    switch (commandIndex)
    {
        case PASS:
            ClientAutherization(fd, command);
            break;
        case NICK:
            ClientNick(fd, command);
            break;
        case USER:
            ClientUsername(fd, command);
            break;
        case QUIT:
            ClientQuit(fd);
            break;
        default:
            // if (!client.GetLoggedIn())
            //     SendError(fd, ERR_NOTREGISTERED(client.GetNickname()));
            // else
            RouterCommands(fd, commandIndex, command);
        break;
    }
}

void Server::ParseClientCommands(int fd, string command)
{
    if (command.empty())
        return;
    std::vector<string> commandList = SplitCommand(command);
    int commandIndex = FindCommandInMap(commandList[0]);

    if (commandList.size() && commandIndex <= 0)
        return;
    
    RouterLoginCommands(fd, commandIndex, commandList);
}