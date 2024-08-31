#include "../Server/Server.hpp"
#include <sstream> //-> for std::istringstream

bool Server::CheckIsUsing(string value, string checkValue)
{
    value = value.substr(1, value.size()); // Remove the first character :
    
    if (checkValue == "nickname")
    {
        for (size_t i = 0; i < Clients.size(); i++)
        {
            if (Clients[i].GetNickname() == value)
            {
                return true;
            }
        }
    }
    else if (checkValue == "username")
    {
        for (size_t i = 0; i < Clients.size(); i++)
        {
            print(Clients[i].GetUsername(), GREEN);
            if (Clients[i].GetUsername() == value)
            {
                return true;
            }
        }
    }
    return false;
}

vector<string> Server::SplitChannelNames(vector<string> channelNames)
{
    vector<string> channels;

    std::istringstream tokenStream(channelNames[0]);
    string token;
    while (std::getline(tokenStream, token, ','))
    {
        if (!token.empty())
        {
            int pos = token.find_first_of(' ');
            string channelName = token.substr(0, pos);
            channels.push_back(channelName);
        }
    }
    return channels;
}