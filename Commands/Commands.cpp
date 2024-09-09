#include "../Server/Server.hpp"
#include <sstream> //-> for std::istringstream

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