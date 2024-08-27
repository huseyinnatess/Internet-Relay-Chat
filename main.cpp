#include "Server/Server.hpp"
#include "Check.hpp"

int main(int argc, char *argv[])
{
    argv[2] = "password";
    argv[1] = "8888";
    argc = 3;
    if (argc != 3 || !CheckPort(std::atoi(argv[1])) || !CheckPassword(argv[2]))
    {
        if (argc != 3)
        {
            print("Error: Invalid arguments", RED);
            print("Usage: <port number> <password>", RED);
        }
        return 1;
    }
    Server server;

    print("----------- Server -----------", GREEN);

    try
    { 
        signal(SIGINT, Server::SignalHandler); // catch the signal (ctrl + c)
        signal(SIGTSTP, Server::SignalHandler); // catch the signal (ctrl + z)
        signal(SIGQUIT, Server::SignalHandler); // catch the signal (ctrl + \)
        server.ServerInit(std::atoi(argv[1]), argv[2]);
    }
    catch (const std::exception& e)
    {
        server.CloseFds();
        print(e.what(), RED);
    }
    print("------- The Server Closed ----", YELLOW);
    return 0;
}



