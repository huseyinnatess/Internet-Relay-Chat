#include "../Print/Print.hpp"
#include "../Server/Server.hpp"

/* ----------------- Main Argument Check Functions ----------------- */
bool CheckPort(int port)
{
    if (port < 1024 || port > 65535)
    {
        print("Error: Invalid port number", RED);
        print("Port number must be between 1024 and 65535", RED);
        return false;
    }
    return true;
}
/* ------------------------------------------------------------------ */

/* ----------------- PASSWORD CHECK FUNCTIONS ----------------- */
bool CheckPassword(string password)
{
    if (password.length() < 8 || password.length() > 20)
    {
        print("Error: Password length must be between 8 and 20", RED);
        return false;
    }
    return true;
}
/* ----------------------------------------------------------- */

/* ----------------- NICKNAME CHECK FUNCTIONS ----------------- */
bool CheckIsValidNickname(string nickname)
{
   const char invalidChars[] = {
    '@', '!', '#', '$', '%', '^', '&', '*', '(', ')', '+', '=', 
    '{', '}', '[', ']', '|', '\\', ':', ';', '"', '\'', '<', '>', 
    ',', '.', '?', '/'
};

    for (size_t i = 0; i < nickname.size(); i++)
    {
        for (size_t j = 0; j < sizeof(invalidChars); j++)
        {
            if (nickname[i] == invalidChars[j])
            {
                return false;
            }
        }
    }
    return true;
}
/* ----------------------------------------------------------- */

/* ----------------- CHANNEL CHECK FUNCTIONS ----------------- */
bool CheckChannelName(string channelName)
{
    if (channelName.empty() || channelName.size() == 1)
    {
        return true;
    }

    if (channelName[0] != '#' && channelName[0] != '&')
    {
        return true;
    }

    for (size_t i = 0; i < channelName.length(); i++)
    {
        if (channelName[i] == 7)
        {
            return true;
        }
    }
    return false;
}

int Server::CheckClientRegistered(int fd, string channelName)
{
    Client &client = GetClient(fd);
    int index = GetCreatedChannelIndex(channelName);
    if (index == -1)
    {
        return 0;
    }
    Channel &channel = CreatedChannels[index];

    for (size_t i = 0; i < channel.RegisteredUsersFd.size(); i++)
    {
        if (channel.RegisteredUsersFd[i] == fd)
        {
            return 1;
        }
    }
    return 0;
}

int Server::CheckChannelIsCreated(string channelName)
{
    for (size_t i = 0; i < CreatedChannels.size(); i++)
    {
        if (CreatedChannels[i].GetChannelName() == channelName)
        {
            return 1;
        }
    }
    return 0;
}
/* ----------------------------------------------------------- */