#include "Server/Server.hpp"

int main(int argc, char *argv[])
{
    argv[1] = "8888";
    argv[2] = "password";
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
        server.ServerInit(ConvertToInt(argv[1]), argv[2]);
    }
    catch (const std::exception& e)
    {
        print(e.what(), RED);
        server.CloseFds();
    }
    print("------- The Server Closed ----", YELLOW);
    return 0;
}



