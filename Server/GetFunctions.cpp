#include "Server.hpp"

Client& Server::GetClient(int fd)
{
	for (size_t i = 0; i < Clients.size(); i++)
    {
		if (Clients[i].GetFd() == fd)
			return Clients[i];
	}
	throw (std::runtime_error("Client not found"));
}

Client& Server::GetClient(string nickName)
{
	for (size_t i = 0; i < this->Clients.size(); i++)
    {
		if (this->Clients[i].GetNickname() == nickName)
			return this->Clients[i];
	}
	throw (std::runtime_error("Client not found"));
}

int Server::GetCreatedChannelIndex(string channelName)
{
    for (size_t i = 0; i < CreatedChannels.size(); i++)
    {
        if (CreatedChannels[i].GetChannelName() == channelName)
        {
            return i;
        }
    }
    return -1;
}