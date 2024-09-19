#include "../Server/Server.hpp"
#include <sstream> //-> for std::istringstream

vector<string> SplitCommand(string command) // Split the command
{
    vector<string> commandList;
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

void Server::RouterCommands(int fd, int commandIndex, vector<string> command)
{
    switch (commandIndex)
    {
        case JOIN:
            ClientJoin(fd, command);
            break;
        case PART:
            ClientPart(fd, command);
            break;
        case TOPIC:
            ClientTopic(fd, command);
            break;
        case MODE:
            ClientMode(fd, command);
            break;
        case INVITE:
            ClientInvite(fd, command);
            break;
        case KICK:
            ClientKick(fd, command);
            break;
        case PRIVMSG:
            ClientPrivmsg(fd, command);
            break;
    }
}

void Server::RouterLoginCommands(int fd, int commandIndex, vector<string> command)
{
    Client &client = GetClient(fd);

    switch (commandIndex)
    {
        case CAP:
            ClientCap(fd, command);
            break;
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
            if (!client.GetRegistered() || client.GetNickname() == "Client" || client.GetUsername() == "Client")
            {
                SendError(fd, ERR_NOTREGISTERED(client.GetNickname()));
            }
            else
            RouterCommands(fd, commandIndex, command);
        break;
    }
}

void Server::ParseClientCommands(int fd, string command)
{
    if (command.empty())
        return;
    vector<string> commandList = SplitCommand(command);

    int commandIndex = FindCommandInMap(commandList[0]);

    if (commandList.size() && commandIndex < 0)
        return;
    
    CheckDoubleCommands(commandList);

    RouterLoginCommands(fd, commandIndex, commandList);
}