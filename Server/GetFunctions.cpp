#include "Server.hpp"

Client& Server::GetClient(int fd)
{
	for (size_t i = 0; i < this->Clients.size(); i++)
    {
		if (this->Clients[i].GetFd() == fd)
			return this->Clients[i];
	}
	throw std::runtime_error("Client not found");
}