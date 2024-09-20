#include "Print.hpp"

/* ------------- OUTPUT FUNCTIONS ------------- */
void print(string message, string colorCode = DEFAULT)
{
    std::cout << colorCode << message << std::endl;
}

void printError(string message, string colorCode = DEFAULT)
{
    std::cerr << colorCode << message << std::endl;
}

void write(string message, string colorCode = DEFAULT)
{
    std::cout << colorCode << message;
}

/* ------------- CONVERT STRING FUNCTIONS ------------- */
string ConvertToString(const int variable)
{
    string result;

    int temp = variable;

   try
    {
        if (temp < 0)
        {
            temp = -temp;
        }

        do 
        {
            char digit = '0' + temp % 10;
            result = digit + result;
            temp /= 10;
        } while (temp != 0);

        if (variable < 0)
        {
            result = '-' + result;
        }
    }
    catch (...)
    {
        print("ConvertToString: Error while converting int to string", RED);
        throw;
    }
    return result;
}

string ConvertToString(const unsigned int variable)
{
    string result;

    unsigned int temp = variable;

    try
    {
        do {
        char digit = '0' + temp % 10;
        result = digit + result;
        temp /= 10;
        }  while (temp != 0);
    }
    catch (...)
    {
        print("ConvertToString: Error while converting int to string", RED);
        throw;
    }
    return result;
}

string ConvertToString(size_t variable)
{
    string result;

    size_t temp = variable;

    try
    {
        do {
        char digit = '0' + temp % 10;
        result = digit + result;
        temp /= 10;
        }  while (temp != 0);
    }
    catch (...)
    {
        print("ConvertToString: Error while converting int to string", RED);
        throw;
    }
    return result;
}

string ConvertToUpperCase(string variable)
{
    string result;
    try
    {
        for (string::iterator it = variable.begin(); it != variable.end(); it++)
        {
            if (*it >= 'a' && *it <= 'z')
                result += *it - 32;
            else
                result += *it;
        }
    }
    catch (...)
    {
        print("ConvertToUpperCase: Error while converting string to uppercase", RED);
        throw;
    }
    return result;
}

string ConvertToLowerCase(string variable)
{
    string result;
    try
    {
        for (string::iterator it = variable.begin(); it != variable.end(); it++)
        {
            if (*it >= 'A' && *it <= 'Z')
                result += *it + 32;
            else
                result += *it;
        }
    }
    catch (...)
    {
        print("ConvertToLowerCase: Error while converting string to lowercase", RED);
        throw;
    }
    return result;
}

/* ------------- CONVERT INT FUNCTIONS ------------- */

int ConvertToInt(const string variable)
{
    int result = 0;
    int i = 0;
    bool isNegative = false;

    try {
        if (variable[0] == '-') {
            isNegative = true;
            i++;
        }

        while (variable[i] != '\0') {
            result = result * 10 + variable[i] - '0';
            i++;
        }

        if (isNegative) {
            result = -result;
        }
    }
    catch (...)
    {
        print("ConvertToInt: Error while converting string to int", RED);
        throw;
    }
    return result;
}

