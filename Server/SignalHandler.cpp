#include "Server.hpp"

bool Server::_signal = false;

void Server::SignalHandler(int signal)
{
    (void) signal;
    _signal = true;
    print("Signal received", YELLOW);
}