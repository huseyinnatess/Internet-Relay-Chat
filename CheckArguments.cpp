#include "Print/Print.hpp"


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

bool CheckPassword(string password)
{
    if (password.length() < 8 || password.length() > 20)
    {
        print("Error: Password length must be between 8 and 20", RED);
        return false;
    }
    return true;
}
