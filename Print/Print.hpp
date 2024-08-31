#ifndef PRINT
#define PRINT

/* ------------- COLOR CODES ------------- */
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define PURPLE      "\033[35m"
#define TURQUISE    "\033[36m"
#define DEFAULT     "\033[0m"
#define BOLD        "\033[1m"

/* ------------- INCLUDES ------------- */
#include <iostream>
#include <string>
#include <vector>

/* ------------- TYPEDEF ------------- */
#define     string std::string
#define     vector std::vector

/* ------------- TEMPLATE OUTPUT FUNCTIONS ------------- */
template <class T>
void print(T message, string colorCode = DEFAULT)
{
    std::cout << colorCode << message << std::endl;
}

template <class T>
void printError(T message, string colorCode = DEFAULT)
{
    std::cerr << colorCode << message << std::endl;
}

template <class T>
void write(T message, string colorCode = DEFAULT)
{
    std::cout << colorCode << message;
}


/* ------------- OUTPUT FUNCTIONS ------------- */
void        print(string, string);
void        printError(string, string);
void        write(string, string);

/* ------------- CONVERT FUNCTIONS ------------- */
string      ConvertToString(const int variable);
string      ConvertToString(const unsigned int variable);
string      ConvertToString(size_t variable);
int         ConvertToInt(const string variable);
string      ConvertToUpperCase(string variable);
string      ConvertToLowerCase(string variable);

#endif